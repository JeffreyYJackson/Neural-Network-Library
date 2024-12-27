#include "..\include/ActivationFunction.h"
#include <iostream>
#include <cmath>

void ActivationFunction::SetActivationFunctions(ActivationFunctionType Type, float (*&activationFunc) (float), float (*&randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen)){
    switch (Type){
    case ActivationFunctionType::ReLU:
        activationFunc = ActivationFunction::ReLU;
        randomGen = ActivationFunction::ReLU_Random_Gen;
        break;
    case ActivationFunctionType::Sigmoid:
        activationFunc = ActivationFunction::Sigmoid;
        randomGen = ActivationFunction::Sigmoid_Random_Gen;
        break;
    default:
        return;
        break;
    }
}

float ActivationFunction::ReLU(float value){
    if (value < 0) {return 0;}
    return value;
}

float ActivationFunction::ReLU_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen){
    std::normal_distribution<> dist(0, sqrt((double)2/input_Node_Count));
    return (float)dist(_gen);
}

float ActivationFunction::Sigmoid(float value){
    return  1 / (1 + (float) exp(-value));
}

float ActivationFunction::Sigmoid_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen){
    std::normal_distribution<> dist(0, sqrt((double)2/input_Node_Count));
    return (float)dist(_gen);
}
