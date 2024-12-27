#pragma once

#include <vector>
#include <random>

struct Node
{
    Node(unsigned int inputCount):weights(std::vector<float>(inputCount)){}
    float value;
    float bias = 0;
    std::vector<float> weights;
};

class Layer{
    public:
        std::vector<Node> nodes;
        unsigned int nodeCount;
        unsigned int inputCount = 0;

        Layer(float (*activationFunc) (float), float (*randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen), unsigned int _nodeCount, unsigned int inputNodeCount = 0);
        void randomizeWeights(std::mt19937& gen);

        void calculateNodeValues(std::vector<Node>& inputNodes);
    private:
        //Activation Function related function pointers
        float (*activationFunc) (float value);
        float (*randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen);
};