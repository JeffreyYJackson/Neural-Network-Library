#pragma once

#include <vector>
#include <random>

#include "ActivationFunction.h"

struct Node
{
    Node(unsigned int inputCount):weights(std::vector<float>(inputCount)), weightsGradient(std::vector<float>(inputCount)){}

    float value;
    float bias = 0;
    std::vector<float> weights;

    float biasGradient = 0;
    std::vector<float> weightsGradient;
};

class Layer{
    public:
        std::vector<Node> nodes;
        unsigned int nodeCount;
        unsigned int inputCount = 0;
        ActivationFunctionType type; 

        Layer(){};
        Layer(unsigned int _nodeCount, unsigned int _inputNodeCount = 0);
        Layer(ActivationFunctionType _type, unsigned int _nodeCount, unsigned int _inputNodeCount = 0);
        void randomizeWeights(std::mt19937& gen);

        void calculateNodeValues(std::vector<Node>& inputNodes);
        
        //Activation Function related function pointers
        float (*activationFunc) (float value) = ActivationFunction::ReLU;
        float (*randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen) = ActivationFunction::ReLU_Random_Gen;
};