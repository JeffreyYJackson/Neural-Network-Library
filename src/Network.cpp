#include "..\include/Network.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

//Network::Network(std::string fileName){
//    import(fileName);
//    this->ActivationFunctionPtrs = ActivationFunction::SetNetworkFunctions(this->Type);
//}

void Network::pushLayer(unsigned int nodeCount, float (*activationFunc) (float), float (*randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen)){
    depth++;
    nodesCount.push_back(nodeCount);

    if(depth == 1){//if first, create a layer without weights.
        layers.push_back(Layer(activationFunc, randomGen, nodeCount));
        return;
    }
    //if not first, create a layer with nodes and weights.
    layers.push_back(Layer(activationFunc, randomGen, nodeCount, nodesCount.at(depth-2)));
}

void Network::randomizeLayerWeights(unsigned int layerIndex){
    this->layers.at(layerIndex).randomizeWeights(this->gen);
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
        this->layers.at(0).nodes.at(i).value = inputs.at(i);
    }
    return 1;
}

void Network::pass(){
    for (unsigned int i = 1; i < depth; i++){
        layers.at(i).calculateNodeValues(layers.at(i-1).nodes);
    }
}

void Network::printWeight(){
    std::cout << "Weigths:\n";
    int sum = 0;

    for (const auto& layer: layers){
        for(const auto& connectedNode: layer.nodes){
            for (const auto& weight: connectedNode.weights){
                std::cout << weight << '\n';
                sum++;
            }
        }
    }
    std::cout << "Number of Weights: " << sum<< '\n';
}

void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (const Node& i: this->layers.at(_i).nodes){
        std::cout  << i.value << '\n';
    }
}

/*
void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (const Node& i: this->layers.at(_i)){
        std::cout  << i.value << '\n';
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

void Network::saveNodesCount(std::ofstream &networkFile){
    for (const auto& count: nodesCount){
        networkFile << count << ' ';
    }
    networkFile << '\n';
}
*/

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


*/