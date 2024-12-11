#pragma once

enum ActivationType{
    ReLU
};

struct ActivationFunctionPtr
{
    float (*activationFunction) (float);
    float (*randomGenFunction) ();
};

class ActivationFunction{
    public:
        static ActivationFunctionPtr SetNetworkFunctions(ActivationType Type);

        static float ReLU(float value);

        static float ReLU_Random_Gen(){}
};