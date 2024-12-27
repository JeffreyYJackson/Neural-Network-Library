#include "..\include\Layer.h"

Layer::Layer(ActivationFunctionType _type, unsigned int _nodeCount, unsigned int _inputNodeCount) :nodeCount(_nodeCount), inputCount(_inputNodeCount), type(_type){
    this->nodes = std::vector<Node>(nodeCount, Node(inputCount)); //Initialize nodes
}

Layer::Layer(unsigned int _nodeCount, unsigned int _inputNodeCount) : nodeCount(_nodeCount), inputCount(_inputNodeCount){
    this->nodes = std::vector<Node>(nodeCount, Node(inputCount)); //Initialize nodes
}

void Layer::randomizeWeights(std::mt19937& gen){
    for (auto& layer_node: nodes){
        for(auto& connected_weight: layer_node.weights){
            connected_weight = randomGen(this->inputCount, gen);
        }
    }
}

void Layer::calculateNodeValues(std::vector<Node>& inputNodes){
    for (auto& node: nodes){
        float nodeVal = node.bias;

        for (unsigned int i = 0; i < inputCount; i++){
            nodeVal += (node.weights.at(i) * inputNodes.at(i).value);
        }
        
        node.value = activationFunc(nodeVal);
    }
}