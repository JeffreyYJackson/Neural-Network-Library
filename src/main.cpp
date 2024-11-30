#include <iostream>
#include <vector>
#include <random>

#include "..\include/Network.h"
#include "..\include\LayerBuilder.h"


//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {784, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);
    
    LayerBuilder::buildLayers(myNetwork);

    std::cout << myNetwork.layers.at(3).size();
    
    return 0;
}