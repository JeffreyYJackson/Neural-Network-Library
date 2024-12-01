#pragma once

#include <vector>

class Node{
    private:
        int layer;
        float bias = 0;
        
        float value;

    public:

        void setBias(float biasVal);
        float getBias();

        void setValue(float _value);
        float getValue();

        //float calculateValue(std::vector<Node> input, std::vector<float> weights);
};