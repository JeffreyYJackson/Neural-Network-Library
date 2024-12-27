#include "..\include/Network.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

//Network::Network(std::string fileName){
//    import(fileName);
//    this->ActivationFunctionPtrs = ActivationFunction::SetNetworkFunctions(this->Type);
//}

void Network::pushLayer(unsigned int nodeCount){
    depth++;
    nodesCount.push_back(nodeCount);

    if(depth == 1){//if first, create a layer without weights.
        layers.push_back(Layer(nodeCount));
        return;
    }
    //if not first, create a layer with nodes and weights.
    layers.push_back(Layer(nodeCount, nodesCount.at(depth-2)));
}

void Network::randomizeLayerWeights(unsigned int layerIndex, float (*activationFunctionRandomGen) (unsigned int, std::mt19937&)){
    this->layers.at(layerIndex).randomizeWeights(activationFunctionRandomGen, this->gen);
}

void Network::printWeight(){
    std::cout << "Weigths:\n";
    int sum = 0;

    for (const auto& layer: layers){
        for(const auto& connectedNode: layer.weights){
            for (const auto& weight: connectedNode){
                std::cout << weight << '\n';
                sum++;
            }
        }
    }
    std::cout<<sum<<'\n';



/*
    for (const auto& k: this->weights){
        for(const auto& i: k){
            int count = 0;
            for(const auto& j: i){
                std::cout << j << '\n';

                count++;
                sum++;
            }
            std::cout<<count<<'\n';
        }
    }
    std::cout<<sum<<'\n';
    */
}

/*
void Network::printWeight(){
    std::cout << "Weigths:\n";
    int sum = 0;
    for (const auto& k: this->weights){
        for(const auto& i: k){
            int count = 0;
            for(const auto& j: i){
                std::cout << j << '\n';

                count++;
                sum++;
            }
            std::cout<<count<<'\n';
        }
    }
    std::cout<<sum<<'\n';
}








void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (const Node& i: this->layers.at(_i)){
        std::cout  << i.value << '\n';
    }
}


*/







/*


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



void Network::saveNodesCount(std::ofstream &networkFile){
    for (const auto& count: nodesCount){
        networkFile << count << ' ';
    }
    networkFile << '\n';
}

/****  Utility Functions  ****/

/*
//Save Biases(Excluding input layer as the biasses are 0)
void Network::saveBias(std::ofstream &networkFile){
    for(unsigned int i = 1; i < this->depth; i++){
        for(const auto& node: this->layers.at(i)){
            networkFile << node.bias << ' ';
        }
        networkFile << '\n';
    }
}

void Network::saveWeights(std::ofstream &networkFile){
    for (const auto& weightLayer: weights){
        for (const auto& connectedNode: weightLayer){
            for (const auto& inputNode: connectedNode){
                networkFile << inputNode << ' ';
            }
            networkFile << '\n';
        }
    }
}

void Network::importNodesCount(std::ifstream &networkFile){
    this->nodesCount = std::vector<unsigned int>(this->depth);

    for (auto& nodeCount: this->nodesCount){
        networkFile >> nodeCount;
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
*/