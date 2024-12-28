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
        
        void pushLayer(unsigned int nodeCount, ActivationFunctionType _type);
        void pushLayer(unsigned int nodeCount);

        void randomizeLayerWeights(unsigned int layerIndex);

        std::mt19937 gen;

        int input(std::vector<float> inputs);
        void pass();

        std::vector<std::vector<float>> trainingData;
        std::vector<std::vector<float>> expectedValues;

        float loss(std::vector<float> expectedOutput);
        float cost();

        void aproximateGradient();
        void approximateBias(Node& node);
        void approximateWeights(Node& node);

        void printWeight();
        void printLayerVals(unsigned int _i);

        void save(std::string fileName);
        void import(std::string fileName);

    private:
        /**********Utility Functions**********/

        void saveNodesCount(std::ofstream &networkFile);
        void saveActivationType(std::ofstream &networkFile);
        void saveBias(std::ofstream &networkFile);
        void saveWeights(std::ofstream &networkFile);

        void importNodesCount(std::ifstream &networkFile);
        void initializeLayers();
        void importActivationType(std::ifstream &networkFile);
        void importBias(std::ifstream &networkFile);
        void importWeights(std::ifstream &networkFile);
};