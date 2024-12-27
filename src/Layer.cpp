#include "..\include\Layer.h"

Layer::Layer(unsigned int _nodeCount, unsigned int _inputNodeCount):nodeCount(_nodeCount), inputCount(_inputNodeCount){
    this->nodes = std::vector<Node>(nodeCount); //Initialize nodes
    this->weights = std::vector<std::vector<float>>(nodeCount, std::vector<float>(inputCount)); //Initialize weights
}

Layer::Layer(unsigned int _nodeCount){
    this->nodes = std::vector<Node>(_nodeCount); //Initialize nodes
}

void Layer::randomizeWeights(float (*randomGen) (unsigned int, std::mt19937&), std::mt19937& gen){
    for (auto& layer_node: weights){
        for(auto& connected_weight: layer_node){
            connected_weight = randomGen(this->inputCount, gen);
        }
    }
}