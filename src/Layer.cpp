#include "..\include\Layer.h"

Layer::Layer(float (*_activationFunc) (float), float (*_randomGen) (unsigned int input_Node_Count, std::mt19937& _gen), unsigned int _nodeCount, unsigned int _inputNodeCount) : nodeCount(_nodeCount), inputCount(_inputNodeCount), activationFunc(_activationFunc), randomGen(_randomGen){
    this->nodes = std::vector<Node>(nodeCount, Node(inputCount)); //Initialize nodes
    //this->weights = std::vector<std::vector<float>>(nodeCount, std::vector<float>(inputCount)); //Initialize weights
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