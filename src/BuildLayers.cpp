#include "include/Network.h"

void Network::buildNetworkLayers(){
    for(unsigned int i = 0; i < this->depth; i++) {
        //Create an element for next layer.
        std::vector<Node> a;//////////////////////////////////////////////Naming
        this->layers.push_back(a);

        //Build next layer
        this->buildLayer(this->layers.at(i), this->nodesCount.at(i));
    }
}

//Function to build a layer.
void Network::buildLayer(std::vector<Node> nodes, unsigned int numberOfNodes) {
    for(unsigned int i = 0; i < numberOfNodes; i++) {
        Node node = Node();
        nodes.push_back(node);
    }
}