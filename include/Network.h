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
        
        void buildNodeLayers();
        void buildWeightLayers();

        void save(std::string fileName);
        void import(std::string fileName);

        int input(std::vector<float> inputs);
        void pass();

        void printWeight();
        void printLayerVals(unsigned int _i);
    private:
        /**********Utility Functions**********/
        void createWeightLayer(unsigned int targetConnection); 
        void createWeights(unsigned int targetConnect, unsigned int targetNode);

        void saveNodesCount(std::ofstream &networkFile);
        void saveBias(std::ofstream &networkFile);
        void saveWeights(std::ofstream &networkFile);

        void importNodesCount(std::ifstream &networkFile);
        void importBias(std::ifstream &networkFile);
        void importWeights(std::ifstream &networkFile);

        static void calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer);
        static void calculateNodeValue(Node &targetNode, std::vector<Node> &inputNodes, std::vector<float> weights);
};