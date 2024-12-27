#pragma once
#include <random>
#include <vector>

enum ActivationFunctionType{
    ReLU,
    Sigmoid
};

class ActivationFunction{
    public:
        static void SetActivationFunctions(ActivationFunctionType Type, float (*&activationFunc) (float), float (*&randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen));

        static float ReLU(float value);
        static float ReLU_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen);

        static float Sigmoid(float value);
        static float Sigmoid_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen);
};