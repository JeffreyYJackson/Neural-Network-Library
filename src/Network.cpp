#include "..\include/Network.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

#define APPROXIMATION_CONST (float)0.1

Network::Network(std::string fileName){
    import(fileName);
}

void Network::pushLayer(unsigned int nodeCount, ActivationFunctionType _type){
    depth++;
    nodesCount.push_back(nodeCount);

    Layer _layer = Layer(_type, nodeCount, nodesCount.at(depth-2));
    ActivationFunction::SetActivationFunctions(_type, _layer.activationFunc, _layer.randomGen);

    layers.push_back(_layer);

    randomizeLayerWeights(depth - 1);
}

void Network::pushLayer(unsigned int nodeCount){
    depth++;
    nodesCount.push_back(nodeCount);

    layers.push_back(Layer(nodeCount));

}

void Network::randomizeLayerWeights(unsigned int layerIndex){
    this->layers.at(layerIndex).randomizeWeights(gen);
}

int Network::input(std::vector<float> inputs){
    //Check for error
    if(inputs.size() != nodesCount.at(0)) {
        std::cout << "Input values do not match the input layer of network.\n Input Layer Size: " << nodesCount.at(0) << "\n";
        std::cout << "Passed Input Size: " << inputs.size() << "\n";
        return 0;
    }
    
    //Set input layer to _input.
    for (unsigned int i = 0; i < nodesCount.at(0); i++){
        layers.at(0).nodes.at(i).value = inputs.at(i);
    }
    return 1;
}

void Network::pass(){
    for (unsigned int i = 1; i < depth; i++){
        layers.at(i).calculateNodeValues(layers.at(i-1).nodes);
    }
}

float Network::loss(std::vector<float> expectedOutput){
    if(expectedOutput.size() != nodesCount.back()){
        std::cout << "Expected output does not match output layer size" << '\n';
    }

    float loss = 0;

    for (unsigned int i = 0; i < layers.back().nodeCount; i++){
        loss += 0.5 * (expectedOutput.at(i) - layers.back().nodes.at(i).value);
    }

    return loss;
}

float Network::cost(){
    float cost = 0;
    for (unsigned int i = 0; i < trainingData.size(); i++){//Add up the loss of each training value.
        input(trainingData.at(i));
        pass();
        cost += loss(expectedValues.at(i));
    }

    cost = cost / (float)trainingData.size(); //Average of all loss values.
    return cost;
}


void Network::aproximateGradient(){
    for (unsigned int i = 1; i < depth; i++){
        for(auto& node: layers.at(i).nodes){
            approximateBias(node);
            approximateWeights(node);
        }
    }
}

void Network::approximateBias(Node& _node){
    float biasInit = _node.bias;
    float costInit = cost();

    float biasFinal = biasInit + APPROXIMATION_CONST;
    _node.bias = biasFinal;
    float costFinal = cost();

    float gradient = (costFinal - costInit)/(biasFinal - biasInit);
    
    _node.bias = biasInit;
    _node.biasGradient = gradient;
}

void Network::approximateWeights(Node& _node){
    for (unsigned int i = 0; i < _node.weights.size(); i++){

        float weightInit = _node.weights.at(i);
        float costInit = cost();

        float weightFinal = weightInit + APPROXIMATION_CONST;
        _node.weights.at(i) = weightFinal;
        float costFinal = cost();

        float gradient = (costFinal - costInit)/(weightFinal - weightInit);

        _node.weights.at(i) = weightInit;
        _node.weightsGradient.at(i) = gradient;
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

void Network::save(std::string fileName){
    //Open File
    std::ofstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Save info
    networkFile << this->depth << "\n";
    saveNodesCount(networkFile);
    saveActivationType(networkFile);
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
    networkFile >> this->depth; 
    importNodesCount(networkFile);
    initializeLayers();
    importActivationType(networkFile);
    importBias(networkFile);
    importWeights(networkFile);

    networkFile.close();
}

/****  Utility Functions  ****/

void Network::saveNodesCount(std::ofstream &networkFile){
    for (const auto& count: nodesCount){
        networkFile << count << ' ';
    }
    networkFile << '\n';
}

void Network::saveActivationType(std::ofstream &networkFile){
    for(unsigned int i = 1; i < depth; i++){
        networkFile << layers.at(i).type << ' ';
    }
    networkFile << '\n';
}

//Save Biases(Excluding input layer as the biasses are 0)
void Network::saveBias(std::ofstream &networkFile){
    for(unsigned int i = 1; i < depth; i++){
        for(const auto& node: layers.at(i).nodes){
            networkFile << node.bias << ' ';
        }
        networkFile << '\n';
    }
}

//Save Weights(Excluding input layer as the weights are 0)
void Network::saveWeights(std::ofstream &networkFile){
    for (unsigned int i = 1; i < depth; i++){
        for (const auto& connectedNode: layers.at(i).nodes){
            for (const auto& weight: connectedNode.weights){
                networkFile << weight << ' ';
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

void Network::initializeLayers(){
    layers = std::vector<Layer>(depth);//Initialize layer vector

    this->layers.at(0) = Layer(nodesCount.at(0)); //Initialize input layer

    for(unsigned int i = 1; i < depth; i++){ //Initialize other layers.
        layers.at(i) = Layer(nodesCount.at(i), nodesCount.at(i - 1));
    }
}

void Network::importActivationType(std::ifstream &networkFile){
    int type;
    for(unsigned int i = 1; i < depth; i++){
        networkFile >> type;
        layers.at(i).type = (ActivationFunctionType) type;
        ActivationFunction::SetActivationFunctions(layers.at(i).type, layers.at(i).activationFunc, layers.at(i).randomGen);
    }
}

//Import Biases(Excluding input layer as the biasses are 0)
void Network::importBias(std::ifstream &networkFile){
    for(unsigned int i = 1; i < this->depth; i++){
        for(auto& node: layers.at(i).nodes){
            networkFile >> node.bias;
        }
    }
}

void Network::importWeights(std::ifstream &networkFile){
    for (unsigned int i = 1; i < this->depth; i++){//Layer
        for(auto& connectedNode: layers.at(i).nodes){
            for(auto& weight: connectedNode.weights){
                networkFile >> weight;
            }
        }
    }
}