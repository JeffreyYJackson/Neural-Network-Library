#include "include/Network.h"
#include <iostream>

//Builds all of the weights between each layers of the Network.
void Network::buildWeightLayers() {
    for(unsigned int i = 0; i < this->depth - 1; i++){
        std::vector<std::vector<float>> a;
        this->weights.push_back(a);

        this->createWeightLayer(i);
    }
}

//Creates a group of weights which contains all the weights connecting all of the nodes in a layer to the nodes in the previous layer.
void Network::createWeightLayer(unsigned int targetConnect) {
    for (unsigned int i = 0; i < this->nodesCount.at(targetConnect + 1); i++){
        std::vector<float> a;
        this->weights.at(targetConnect).push_back(a);

        this->createWeights(targetConnect, i);
    }
}

//Creates weights at random connecting a node to all of the nodes in the previous layer(nth connection between layers (layer n and n+1). n number of weights).
void Network::createWeights(unsigned int targetConnect, unsigned int targetNode) {
    for(unsigned int i = 0; i < this->nodesCount.at(targetConnect); i++){
        //A normal distribution with a mean of 0 and a variance of 2/inputNumber for He initialization.
        this->weights.at(targetConnect).at(targetNode).push_back(this->generateGaussian(0, sqrt((double)2/this->nodesCount.at(targetConnect))));
    }
}

void Network::printWeight(){
    int sum = 0;
    for (std::vector<std::vector<float>> k: this->weights){
        for(std::vector<float> i: k){
            int count = 0;
            for(float j: i){
                std::cout << j << "\n";

                count++;
                sum++;
            }
            std::cout<<count<<"\n";
        }
    }
    std::cout<<sum<<"\n";
}

float Network::generateGaussian(double mean, double standardDev){
    std::normal_distribution<> dist(mean, standardDev);
    return (float)dist(this->gen);
}