#include <iostream>
#include <vector>
#include <random>

#include "..\include/Node.h"
#include "..\include/Network.h"
#include "..\include/ActivationFunction.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {3, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);

    myNetwork.printLayerVals(0);

    if (myNetwork.input({1, 4, 3}) == 0) return 0;

    myNetwork.printLayerVals(0);

    
    return 0;
}