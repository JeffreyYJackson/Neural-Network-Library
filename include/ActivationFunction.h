#pragma once
#include <random>
#include <vector>

enum ActivationType{
    ReLU
};

struct ActivationFunctionPtr
{
    float (*activate) (float);
    float (*randomGen) (std::vector<unsigned int>, std::mt19937&, unsigned int);
};

class ActivationFunction{
    public:
        static ActivationFunctionPtr SetNetworkFunctions(ActivationType Type);

        static float ReLU(float value);

        static float ReLU_Random_Gen(std::vector<unsigned int> nodesCount, std::mt19937 &_gen, unsigned int targetConnect);
};