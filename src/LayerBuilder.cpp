#include "..\include\LayerBuilder.h"
#include "..\include/Node.h"

#include <vector>
#include <iostream>

void LayerBuilder::buildLayers(Network &Network){
    //Ceate new layers.
    Network.layers = std::vector<std::vector<Node>>(Network.depth);
    
    for(unsigned int i = 0; i < Network.depth; i++) {
        //Build next layer
        Network.layers.at(i) = std::vector<Node>(Network.nodesCount.at(i));
    }
}