#include <iostream>
#include <vector>
#include <random>

#include "include/Node.h"
#include "include/Network.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {3, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);

    if (myNetwork.input({1, 4, 3}) == 0) return 0;

    myNetwork.printLayerVals(0);
    
    return 0;
}