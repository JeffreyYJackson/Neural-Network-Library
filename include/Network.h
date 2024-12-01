#pragma once

#include<vector>
#include<random>

#include"Node.h"

class Network{
    public:
        std::vector<unsigned int> nodesCount;
        unsigned int depth;

        std::vector<std::vector<Node>> layers; //2 dimensional vector storing layers. First layer being input and last layer being output.
        std::vector<std::vector<std::vector<float>>> weights; //3 dimensional vector containing the weights to use in the edges.
        
        std::mt19937 gen;//Random Device
        float generateGaussian(double mean, double standardDev);//Create random floar values from a normal distribution.
        
        Network(std::vector<unsigned int> _nodesCount) : 
            nodesCount(_nodesCount), depth(nodesCount.size()), gen(std::random_device{}()) {}
        
        //Functions to import and save networks.
        void import();////////////////////////////////////////////////////////////////
        void save();


        int input(std::vector<float> inputs);

        void printWeight();
        void printLayerVals(unsigned int _i);

        void calculateNodeValue(unsigned int layer, unsigned int position);

};