#pragma once
#include <vector>

class Node{
    private:
        int layer;
        float bias = 0;
    public:
        float value;

        void setBias(float biasVal);
        float getBias();
};