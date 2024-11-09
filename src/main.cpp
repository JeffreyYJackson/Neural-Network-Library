#include <iostream>
#include <vector>
#include <random>

#include "include/Node.h"
#include "include/Network.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {200, 2, 2, 2};
    Network myNetwork = Network(nodeLayers);

    for (unsigned int i: myNetwork.getNodeCount()){
        std::cout << i << "\n";
    }
    return 0;
}