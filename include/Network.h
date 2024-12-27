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
        
        void pushLayer(unsigned int nodeCount, float (*activationFunc) (float), float (*randomGen) (unsigned int input_Node_Count, std::mt19937 &_gen));

        void randomizeLayerWeights(unsigned int layerIndex);

        std::mt19937 gen;

        int input(std::vector<float> inputs);
        void pass();

        void printWeight();
        void printLayerVals(unsigned int _i);

/////////////////
        void save(std::string fileName);
        void import(std::string fileName);

    private:
        /**********Utility Functions**********/

        void saveNodesCount(std::ofstream &networkFile);
        void saveBias(std::ofstream &networkFile);
        void saveWeights(std::ofstream &networkFile);

        void importNodesCount(std::ifstream &networkFile);
        void importBias(std::ifstream &networkFile);
        void importWeights(std::ifstream &networkFile);
};