#include "..\include\Network.h"

#include <iostream>
#include <fstream>
#include <vector>

void Network::save(Network &Network, std::string fileName){
    std::ofstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) std::cout << "Unable to open file.";

    networkFile << Network.depth << "\n";

    //Save NodesCount
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile << Network.nodesCount.at(i) << ' ';
    }
    networkFile << "\n";

    //Save Biases(Excluding input layer as the biasses are 0)
    for(unsigned int i = 1; i < Network.depth; i++){
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile << Network.layers.at(i).at(j).bias << ' '; 
        }
    }
    networkFile << "\n";

    //Save Weights
    for (unsigned int i = 0; i < Network.depth - 1; i++){//Weight Layer
        for (unsigned int j = 0; j < Network.nodesCount.at(i + 1); j++){//Connected Layer(nth layer)
            for (unsigned int k = 0; k < Network.nodesCount.at(i); k++){//Connecting Layer(n-1th layer)
                networkFile << Network.weights.at(i).at(j).at(k) << ' ';
            }
            networkFile << "\n";
        }
    }

    networkFile.close();
}

void Network::import(Network &Network, std::string fileName){
    std::ifstream networkFile;
    networkFile.open(fileName);
    if (!networkFile.is_open()) std::cout << "Unable to open file.";

    //Read depth
    networkFile >> Network.depth; 

    //Read NodesCount
    Network.nodesCount = std::vector<unsigned int>(Network.depth);
    
    for (unsigned int i = 0; i < Network.depth; i++){
        networkFile >> Network.nodesCount.at(i);
    }

    //Read Biases(Excluding input layer as the biasses are 0)
    Network.layers = std::vector<std::vector<Node>>(Network.depth); //Initialize layer vector
    Network.layers.at(0) = std::vector<Node>(Network.nodesCount.at(0)); //Initialize input layer

    for(unsigned int i = 1; i < Network.depth; i++){
        Network.layers.at(i) = std::vector<Node>(Network.nodesCount.at(i));//Initialize Node vector
        for (unsigned int j = 0; j < Network.nodesCount.at(i); j++){
            networkFile >> Network.layers.at(i).at(j).bias; 
        }
    }
    //std::vector<std::vector<std::vector<float>>> weights

    //Read Weights
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






