#pragma once

#include<vector>
#include<random>
#include<string>
#include <fstream>
#include <time.h>

#include"Node.h"

class Network{
    public:
        std::vector<unsigned int> nodesCount;
        unsigned int depth;

        std::vector<std::vector<Node>> layers;
        std::vector<std::vector<std::vector<float>>> weights;
        
        //Normal Dist Gen
        std::mt19937 gen;
        float generateGaussian(double mean, double standardDev);

        Network(std::string fileName);
        Network(std::vector<unsigned int> _nodesCount);
        
        static void buildNodeLayers(Network &Network);
        static void buildWeightLayers(Network &Network);

        static void import(Network &Network, std::string fileName);
        static void save(Network &Network, std::string fileName);

        static int input(Network &Network, std::vector<float> inputs);
        static void pass(Network &Network);

        void printWeight();
        void printLayerVals(unsigned int _i);
    private:
        //Utility Functions
        static void createWeightLayer(unsigned int targetConnection, Network &Network); 
        static void createWeights(unsigned int targetConnect, unsigned int targetNode, Network &Network);

        static void saveNodesCount(Network &Network, std::ofstream &networkFile);
        static void saveBias(Network &Network, std::ofstream &networkFile);
        static void saveWeights(Network &Network, std::ofstream &networkFile);

        static void importNodesCount(Network &Network, std::ifstream &networkFile);
        static void importBias(Network &Network, std::ifstream &networkFile);
        static void importWeights(Network &Network, std::ifstream &networkFile);

        static void calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer);
        static void calculateNodeValue(Node &targetNode, std::vector<Node> inputNodes, std::vector<float> weights);
};