#pragma once

#include<vector>
#include<random>

#include"Node.h"

class Network{
    private:
        std::vector<unsigned int> nodesCount;
        unsigned int depth;

        std::vector<std::vector<Node>> layers; //2 dimensional vector storing layers. First layer being input and last layer being output.
        std::vector<std::vector<std::vector<float>>> weights; //3 dimensional vector containing the weights to use in the edges.

        //Build the first gen network on random values.
        void buildLayer(std::vector<Node> nodes, unsigned int numberOfNodes); //Function to build layers of the networks. Specify input, hidden vs output layer initiation.
        void buildNetworkLayers();

        void buildWeightLayers();
        void createWeightLayer(unsigned int targetConnection); 
        void createWeights(unsigned int targetConnect, unsigned int targetNode);
        

        std::mt19937 gen;//Random Device
        float generateGaussian(double mean, double standardDev);//Create random floar values from a normal distribution.
        
    public:
        Network(std::vector<unsigned int> nodesCount);
        //Functions to import and save networks.
        void import();////////////////////////////////////////////////////////////////
        void save();

        //Functions to retrieve private attributes of the object.
        std::vector<unsigned int> getNodeCount() {return this -> nodesCount;}
        unsigned int getDepth() {return this -> depth;}
        void printWeight();
};