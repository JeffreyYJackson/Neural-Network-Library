#include "..\include/Network.h"
#include "..\include\LayerBuilder.h"

//Constructor function.
Network::Network(std::vector<unsigned int> _nodesCount) : nodesCount(_nodesCount), depth(nodesCount.size()), gen(std::random_device{}()) {
    this->buildWeightLayers();
}