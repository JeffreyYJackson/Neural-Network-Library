#include "include/Network.h"
#include "include/Node.h"

#include <vector>
#include <iostream>

void Network::buildNetworkLayers(){
    //Ceate new layers.
    this->layers = std::vector<std::vector<Node>>(this->depth);
    
    for(unsigned int i = 0; i < this->depth; i++) {
        //Build next layer
        this->layers.at(i) = std::vector<Node>(this->nodesCount.at(i));
    }
}