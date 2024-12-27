#include "..\include/ActivationFunction.h"
#include <iostream>

float ActivationFunction::ReLU(float value){
    if (value < 0) {return 0;}
    return value;
}

float ActivationFunction::ReLU_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen){
    std::normal_distribution<> dist(0, sqrt((double)2/input_Node_Count));
    return (float)dist(_gen);
}


float ActivationFunction::Sigmoid(float value){
    if (value < 0) {return 0;}
    return value;
}

float ActivationFunction::Sigmoid_Random_Gen(unsigned int input_Node_Count, std::mt19937 &_gen){
    std::normal_distribution<> dist(0, sqrt((double)2/input_Node_Count));
    return (float)dist(_gen);
}
