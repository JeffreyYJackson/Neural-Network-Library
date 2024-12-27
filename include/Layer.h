#pragma once

#include <vector>
#include <random>

struct Node
{
    float value;
    float bias = 0;
};

class Layer{
    public:
        std::vector<Node> nodes;
        std::vector<std::vector<float>> weights;

        unsigned int nodeCount;
        unsigned int inputCount = 0;

        Layer(unsigned int _nodeCount, unsigned int inputNodeCount);
        Layer(unsigned int _nodeCount);


        void randomizeWeights(float (*randomGen) (unsigned int, std::mt19937&), std::mt19937& gen);
};