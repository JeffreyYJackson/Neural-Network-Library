#pragma once

#include<vector>
#include<random>
#include<string>
#include <fstream>
#include <time.h>

#include"Layer.h"
#include "ActivationFunction.h"

class Network{
    public:
        std::vector<unsigned int> nodesCount;
        unsigned int depth = 0;

        std::vector<Layer> layers;
        
        Network() : gen((unsigned int) time(NULL)){};
        Network(std::string fileName);
        //Network(std::vector<unsigned int> _nodesCount, ActivationType Type);
        
        void pushLayer(unsigned int nodeCount);

        void randomizeLayerWeights(unsigned int layerIndex, float (*activationFunctionRandomGen) (unsigned int, std::mt19937&));

        std::mt19937 gen;


/////////////////
        void save(std::string fileName);
        void import(std::string fileName);

        int input(std::vector<float> inputs);
        void pass();

        void printWeight();
        void printLayerVals(unsigned int _i);
    private:
        /**********Utility Functions**********/

        void saveNodesCount(std::ofstream &networkFile);
        void saveBias(std::ofstream &networkFile);
        void saveWeights(std::ofstream &networkFile);

        void importNodesCount(std::ifstream &networkFile);
        void importBias(std::ifstream &networkFile);
        void importWeights(std::ifstream &networkFile);

        void calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer);
        void calculateNodeValue(Node &targetNode, std::vector<Node> &inputNodes, std::vector<float> _weights);
};