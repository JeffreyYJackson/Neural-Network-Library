#include "..\include/Network.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

Network::Network(std::vector<unsigned int> _nodesCount) : nodesCount(_nodesCount), depth(nodesCount.size()), gen((unsigned int) time(NULL)) {
    buildNodeLayers(*this);
    buildWeightLayers(*this);
}

Network::Network(std::string fileName){
    import(*this, fileName);
}

void Network::buildNodeLayers(Network &Network){
    //Ceate new layers.
    Network.layers = std::vector<std::vector<Node>>(Network.depth);
    for(unsigned int i = 0; i < Network.depth; i++) {
        //Build next layer
        Network.layers.at(i) = std::vector<Node>(Network.nodesCount.at(i));
    }
}

//Builds all of the weights between each layers of the Network.
void Network::buildWeightLayers(Network &Network) {
    Network.weights = std::vector<std::vector<std::vector<float>>>(Network.depth);
    for(unsigned int i = 0; i < Network.depth - 1; i++){
        Network::createWeightLayer(i, Network);
    }
}

void Network::save(Network &Network, std::string fileName){
    //Open File
    std::ofstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Save info
    networkFile << Network.depth << "\n";
    Network::saveNodesCount(Network, networkFile);
    Network::saveBias(Network, networkFile);
    Network::saveWeights(Network, networkFile);

    networkFile.close();
}

void Network::import(Network &Network, std::string fileName){
    //Open File
    std::ifstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Import info
    networkFile >> Network.depth; 
    importNodesCount(Network, networkFile);
    importBias(Network, networkFile);
    importWeights(Network, networkFile);

    networkFile.close();
}

int Network::input(Network &Network, std::vector<float> inputs){
    //Check for error
    if(inputs.size() != Network.nodesCount.at(0)) {
        std::cout << "Input values do not match the input layer of network.\n Input Layer Size: " << Network.nodesCount.at(0) << "\n";
        std::cout << "Passed Input Size: " << inputs.size() << "\n";
        return 0;
    }
    
    //Set input layer to _input.
    for (unsigned int i = 0; i < Network.nodesCount.at(0); i++){
        Network.layers.at(0).at(i).value = inputs.at(i);
    }
    return 1;
}

//Calculation is done using the weight layers as a reference(the spacing inbetween layers. i.e. index 0 is going from layer 1 to 2). 
void Network::pass(Network &Network){
    for(unsigned int i = 0; i < Network.depth - 1; i++){
        calculateLayerValue(Network.layers.at(i + 1), Network.layers.at(i), Network.weights.at(i));
    }
}

void Network::printWeight(){
    std::cout << "Weigths:\n";
    int sum = 0;
    for (std::vector<std::vector<float>> k: this->weights){
        for(std::vector<float> i: k){
            int count = 0;
            for(float j: i){
                std::cout << j << "\n";

                count++;
                sum++;
            }
            std::cout<<count<<"\n";
        }
    }
    std::cout<<sum<<"\n";
}

void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (Node i: this->layers.at(_i)){
        std::cout  << i.value << "\n";
    }
}

float Network::generateGaussian(double mean, double standardDev){
    std::normal_distribution<> dist(mean, standardDev);
    return (float)dist(this->gen);
}

void Network::saveNodesCount(Network &Network, std::ofstream &networkFile){
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile << Network.nodesCount.at(i) << ' ';
    }
    networkFile << "\n";
}

/****  Utility Functions  ****/

//Creates a group of weights which contains all the weights connecting all of the nodes in a layer to the nodes in the previous layer.
void Network::createWeightLayer(unsigned int targetConnect, Network &Network) {
    //Build weight vectors.
    Network.weights.at(targetConnect) = std::vector<std::vector<float>>(Network.nodesCount.at(targetConnect + 1));
    
    //Call function to generate random weights for all nodes.
    for (unsigned int i = 0; i < Network.nodesCount.at(targetConnect + 1); i++){
        //this->createWeights(targetConnect, i);
        Network::createWeights(targetConnect, i, Network);
    }
}

//Creates weights at random connecting a node to all of the nodes in the previous layer(nth connection between layers (layer n and n+1). n number of weights).
void Network::createWeights(unsigned int targetConnect, unsigned int targetNode, Network &Network) {
    //Build weights.
    Network.weights.at(targetConnect).at(targetNode) = std::vector<float>(Network.nodesCount.at(targetConnect));

    for(unsigned int i = 0; i < Network.nodesCount.at(targetConnect); i++){
        //A normal distribution with a mean of 0 and a variance of 2/inputNumber for He initialization.
        Network.weights.at(targetConnect).at(targetNode).at(i) = Network.generateGaussian(0, sqrt((double)2/Network.nodesCount.at(targetConnect)));
    }
}

//Save Biases(Excluding input layer as the biasses are 0)
void Network::saveBias(Network &Network, std::ofstream &networkFile){
    for(unsigned int i = 1; i < Network.depth; i++){
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile << Network.layers.at(i).at(j).bias << ' '; 
        }
        networkFile << "\n";
    }
}

void Network::saveWeights(Network &Network, std::ofstream &networkFile){
    for (unsigned int i = 0; i < Network.depth - 1; i++){//Weight Layer
        for (unsigned int j = 0; j < Network.nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            for (unsigned int k = 0; k < Network.nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile << Network.weights.at(i).at(j).at(k) << ' ';
            }
            networkFile << "\n";
        }
    }
}

void Network::importNodesCount(Network &Network, std::ifstream &networkFile){
    Network.nodesCount = std::vector<unsigned int>(Network.depth);
    
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile >> Network.nodesCount.at(i);
    }
}

//Import Biases(Excluding input layer as the biasses are 0)
void Network::importBias(Network &Network, std::ifstream &networkFile){
    Network.layers = std::vector<std::vector<Node>>(Network.depth); //Initialize layer vector
    Network.layers.at(0) = std::vector<Node>(Network.nodesCount.at(0)); //Initialize input layer

    for(unsigned int i = 1; i < Network.depth; i++){
        Network.layers.at(i) = std::vector<Node>(Network.nodesCount.at(i));//Initialize Node vector
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile >> Network.layers.at(i).at(j).bias; 
        }
    }
}

void Network::importWeights(Network &Network, std::ifstream &networkFile){
    Network.weights = std::vector<std::vector<std::vector<float>>>(Network.depth); //Initialize Weight Layer Vector
    for (unsigned int i = 0; i < Network.depth - 1; i++){//Weight Layer
        Network.weights.at(i) = std::vector<std::vector<float>>(Network.nodesCount.at(i + 1)); //Initialize Connected Node Vector

        for (unsigned int j = 0; j < Network.nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            Network.weights.at(i).at(j) = std::vector<float>(Network.nodesCount.at(i)); //Initialize  Connecting Node Vector

            for (unsigned int k = 0; k < Network.nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile >> Network.weights.at(i).at(j).at(k);
            }
        }
    }
}

void Network::calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer){
    for (unsigned int i = 0; i < layerNodes.size(); i++){
        Network::calculateNodeValue(layerNodes.at(i), inputLayerNodes, weightLayer.at(i));
    }
}

void Network::calculateNodeValue(Node &targetNode, std::vector<Node> inputNodes, std::vector<float> weights){
    float nodeVal = targetNode.bias;

    for (unsigned int i = 0; i < inputNodes.size(); i++){
        nodeVal += (inputNodes.at(i).value * weights.at(i));
    }
    targetNode.value = ActivationFunction::ReLU(nodeVal);
}