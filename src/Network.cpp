#include "..\include/Network.h"

#include <iostream>
#include <fstream>

void saveNodesCount(Network &Network, std::ofstream &networkFile);
void saveBias(Network &Network, std::ofstream &networkFile);
void saveWeights(Network &Network, std::ofstream &networkFile);

void importNodesCount(Network &Network, std::ifstream &networkFile);
void importBias(Network &Network, std::ifstream &networkFile);
void importWeights(Network &Network, std::ifstream &networkFile);

void Network::save(Network &Network, std::string fileName){
    //Open File
    std::ofstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Save info
    networkFile << Network.depth << "\n";
    saveNodesCount(Network, networkFile);
    saveBias(Network, networkFile);
    saveWeights(Network, networkFile);

    networkFile.close();
}

void Network::import(Network &Network, std::string fileName){
    //Open File
    std::ifstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) {std::cout << "Unable to open file."; return;}

    //Import info
    networkFile >> Network.depth; 
    importNodesCount(Network, networkFile);
    importBias(Network, networkFile);
    importWeights(Network, networkFile);

    networkFile.close();
}

void Network::printWeight(){
    std::cout << "Weigths:\n";
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

void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (Node i: this->layers.at(_i)){
        std::cout  << i.value << "\n";
    }
}

float Network::generateGaussian(double mean, double standardDev){
    std::normal_distribution<> dist(mean, standardDev);
    return (float)dist(this->gen);
}

void saveNodesCount(Network &Network, std::ofstream &networkFile){
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile << Network.nodesCount.at(i) << ' ';
    }
    networkFile << "\n";
}

//Save Biases(Excluding input layer as the biasses are 0)
void saveBias(Network &Network, std::ofstream &networkFile){
    for(unsigned int i = 1; i < Network.depth; i++){
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile << Network.layers.at(i).at(j).bias << ' '; 
        }
        networkFile << "\n";
    }
}

void saveWeights(Network &Network, std::ofstream &networkFile){
    for (unsigned int i = 0; i < Network.depth - 1; i++){//Weight Layer
        for (unsigned int j = 0; j < Network.nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            for (unsigned int k = 0; k < Network.nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile << Network.weights.at(i).at(j).at(k) << ' ';
            }
            networkFile << "\n";
        }
    }
}

void importNodesCount(Network &Network, std::ifstream &networkFile){
    Network.nodesCount = std::vector<unsigned int>(Network.depth);
    
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile >> Network.nodesCount.at(i);
    }
}

//Import Biases(Excluding input layer as the biasses are 0)
void importBias(Network &Network, std::ifstream &networkFile){
    Network.layers = std::vector<std::vector<Node>>(Network.depth); //Initialize layer vector
    Network.layers.at(0) = std::vector<Node>(Network.nodesCount.at(0)); //Initialize input layer

    for(unsigned int i = 1; i < Network.depth; i++){
        Network.layers.at(i) = std::vector<Node>(Network.nodesCount.at(i));//Initialize Node vector
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile >> Network.layers.at(i).at(j).bias; 
        }
    }
}

void importWeights(Network &Network, std::ifstream &networkFile){
    Network.weights = std::vector<std::vector<std::vector<float>>>(Network.depth); //Initialize Weight Layer Vector
    for (unsigned int i = 0; i < Network.depth - 1; i++){//Weight Layer
        Network.weights.at(i) = std::vector<std::vector<float>>(Network.nodesCount.at(i + 1)); //Initialize Connected Node Vector

        for (unsigned int j = 0; j < Network.nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            Network.weights.at(i).at(j) = std::vector<float>(Network.nodesCount.at(i)); //Initialize  Connecting Node Vector

            for (unsigned int k = 0; k < Network.nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile >> Network.weights.at(i).at(j).at(k);
            }
        }
    }
}