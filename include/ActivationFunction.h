#pragma once
#include <random>
#include <vector>

class ActivationFunction{
    public:
        static float ReLU(float value);
        static float ReLU_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen);

        static float Sigmoid(float value);
        static float Sigmoid_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen);
};