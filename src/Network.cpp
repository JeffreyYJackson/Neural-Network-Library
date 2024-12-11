#include "..\include/Network.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

Network::Network(std::vector<unsigned int> _nodesCount, ActivationType _Type) : nodesCount(_nodesCount), depth(nodesCount.size()), gen((unsigned int) time(NULL)), Type(_Type){
    this->ActivationFunctionPtrs = ActivationFunction::SetNetworkFunctions(_Type);

    buildNodeLayers();
    buildWeightLayers();
}

Network::Network(std::string fileName){
    import(fileName);
    this->ActivationFunctionPtrs = ActivationFunction::SetNetworkFunctions(this->Type);
}

void Network::buildNodeLayers(){
    //Ceate new layers.
    this->layers = std::vector<std::vector<Node>>(this->depth);
    for(unsigned int i = 0; i < this->depth; i++) {
        //Build next layer
        this->layers.at(i) = std::vector<Node>(this->nodesCount.at(i));
    }
}

//Builds all of the weights between each layers of the Network.
void Network::buildWeightLayers() {
    this->weights = std::vector<std::vector<std::vector<float>>>(this->depth);
    for(unsigned int i = 0; i < this->depth - 1; i++){
        createWeightLayer(i);
    }
}

void Network::save(std::string fileName){
    //Open File
    std::ofstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Save info
    networkFile << this->Type << "\n";
    networkFile << this->depth << "\n";
    saveNodesCount(networkFile);
    saveBias(networkFile);
    saveWeights(networkFile);

    networkFile.close();
}

void Network::import(std::string fileName){
    //Open File
    std::ifstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Import info
    int type;
    networkFile >> type;
    this->Type = (ActivationType) type;
    networkFile >> this->depth; 
    importNodesCount(networkFile);
    importBias(networkFile);
    importWeights(networkFile);

    networkFile.close();
}

int Network::input(std::vector<float> inputs){
    //Check for error
    if(inputs.size() != this->nodesCount.at(0)) {
        std::cout << "Input values do not match the input layer of network.\n Input Layer Size: " << this->nodesCount.at(0) << "\n";
        std::cout << "Passed Input Size: " << inputs.size() << "\n";
        return 0;
    }
    
    //Set input layer to _input.
    for (unsigned int i = 0; i < this->nodesCount.at(0); i++){
        this->layers.at(0).at(i).value = inputs.at(i);
    }
    return 1;
}

//Calculation is done using the weight layers as a reference(the spacing inbetween layers. i.e. index 0 is going from layer 1 to 2). 
void Network::pass(){
    for(unsigned int i = 0; i < this->depth - 1; i++){
        calculateLayerValue(this->layers.at(i + 1), this->layers.at(i), this->weights.at(i));
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

void Network::saveNodesCount(std::ofstream &networkFile){
    for (unsigned int i = 0; i < this->depth; i++){
        networkFile << this->nodesCount.at(i) << ' ';
    }
    networkFile << "\n";
}

/****  Utility Functions  ****/

//Creates a group of weights which contains all the weights connecting all of the nodes in a layer to the nodes in the previous layer.
void Network::createWeightLayer(unsigned int targetConnect) {
    //Build weight vectors.
    this->weights.at(targetConnect) = std::vector<std::vector<float>>(this->nodesCount.at(targetConnect + 1));
    
    //Call function to generate random weights for all nodes.
    for (unsigned int i = 0; i < this->nodesCount.at(targetConnect + 1); i++){
        //this->createWeights(targetConnect, i);
        createWeights(targetConnect, i);
    }
}

//Creates weights at random connecting a node to all of the nodes in the previous layer(nth connection between layers (layer n and n+1). n number of weights).
void Network::createWeights(unsigned int targetConnect, unsigned int targetNode) {
    //Build weights.
    this->weights.at(targetConnect).at(targetNode) = std::vector<float>(this->nodesCount.at(targetConnect));

    for(unsigned int i = 0; i < this->nodesCount.at(targetConnect); i++){
        
        this->weights.at(targetConnect).at(targetNode).at(i) = ActivationFunctionPtrs.randomGen(this->nodesCount, this->gen, targetConnect);
        //this->weights.at(targetConnect).at(targetNode).at(i) = this->generateGaussian(0, sqrt((double)2/this->nodesCount.at(targetConnect)));
    }
}

//Save Biases(Excluding input layer as the biasses are 0)
void Network::saveBias(std::ofstream &networkFile){
    for(unsigned int i = 1; i < this->depth; i++){
        for (unsigned int j = 0; j < this->nodesCount.at(i); j++){
            networkFile << this->layers.at(i).at(j).bias << ' '; 
        }
        networkFile << "\n";
    }
}

void Network::saveWeights(std::ofstream &networkFile){
    for (unsigned int i = 0; i < this->depth - 1; i++){//Weight Layer
        for (unsigned int j = 0; j < this->nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            for (unsigned int k = 0; k < this->nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile << this->weights.at(i).at(j).at(k) << ' ';
            }
            networkFile << "\n";
        }
    }
}

void Network::importNodesCount(std::ifstream &networkFile){
    this->nodesCount = std::vector<unsigned int>(this->depth);
    
    for (unsigned int i = 0; i < this->depth; i++){
        networkFile >> this->nodesCount.at(i);
    }
}

//Import Biases(Excluding input layer as the biasses are 0)
void Network::importBias(std::ifstream &networkFile){
    this->layers = std::vector<std::vector<Node>>(this->depth); //Initialize layer vector
    this->layers.at(0) = std::vector<Node>(this->nodesCount.at(0)); //Initialize input layer

    for(unsigned int i = 1; i < this->depth; i++){
        this->layers.at(i) = std::vector<Node>(this->nodesCount.at(i));//Initialize Node vector
        for (unsigned int j = 0; j < this->nodesCount.at(i); j++){
            networkFile >> this->layers.at(i).at(j).bias; 
        }
    }
}

void Network::importWeights(std::ifstream &networkFile){
    this->weights = std::vector<std::vector<std::vector<float>>>(this->depth); //Initialize Weight Layer Vector
    for (unsigned int i = 0; i < this->depth - 1; i++){//Weight Layer
        this->weights.at(i) = std::vector<std::vector<float>>(this->nodesCount.at(i + 1)); //Initialize Connected Node Vector

        for (unsigned int j = 0; j < this->nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            this->weights.at(i).at(j) = std::vector<float>(this->nodesCount.at(i)); //Initialize  Connecting Node Vector

            for (unsigned int k = 0; k < this->nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile >> this->weights.at(i).at(j).at(k);
            }
        }
    }
}

void Network::calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer){
    for (unsigned int i = 0; i < layerNodes.size(); i++){
        calculateNodeValue(layerNodes.at(i), inputLayerNodes, weightLayer.at(i));
    }
}

void Network::calculateNodeValue(Node &targetNode, std::vector<Node> &inputNodes, std::vector<float> _weights){
    float nodeVal = targetNode.bias;

    for (unsigned int i = 0; i < inputNodes.size(); i++){
        nodeVal += (inputNodes.at(i).value * _weights.at(i));
    }
    targetNode.value = ActivationFunctionPtrs.activate(nodeVal);
}