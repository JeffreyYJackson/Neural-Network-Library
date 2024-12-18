#include "..\include/ActivationFunction.h"
#include <iostream>

ActivationFunctionPtr ActivationFunction::SetNetworkFunctions(ActivationType Type){
    switch (Type)
    {
    case ActivationType::ReLU:
        return {&ActivationFunction::ReLU, &ActivationFunction::ReLU_Random_Gen};
        break;
    default:
        return {nullptr, nullptr};
        break;
    }
}

float ActivationFunction::ReLU(float value){
    if (value < 0) {return 0;}
    return value;
}

float ActivationFunction::ReLU_Random_Gen(std::vector<unsigned int> nodesCount, std::mt19937 &_gen, unsigned int targetConnect){
    std::normal_distribution<> dist(0, sqrt((double)2/nodesCount.at(targetConnect)));
    return (float)dist(_gen);
}
