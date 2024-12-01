#include "..\include/Network.h"

int Network::input(std::vector<float> inputs){
    //Check for error
    if(inputs.size() != this->nodesCount.at(0)) {
        std::cout << "Input values do not match the input layer of network.\n Input Layer Size: " << this->nodesCount.at(0) << "\n";
        std::cout << "Passed Input Size: " << inputs.size() << "\n";
        return 0;
    }
    
    //Set input layer to _input.
    for (unsigned int i = 0; i < this->nodesCount.at(0); i++){
        this->layers.at(0).at(i).setValue(inputs.at(i));
    }
    return 1;
}

void Network::printLayerVals(unsigned int _i){
    std::cout << "Values:\n";
    for (Node i: this->layers.at(_i)){
        std::cout  << i.getValue() << "\n";
    }
}

void Network::calculateNodeValue(unsigned int layer, unsigned int position){
    
}