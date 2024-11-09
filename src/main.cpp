#include <iostream>
#include <vector>
#include <random>

#include "include/Node.h"
#include "include/Network.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {784, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);

    myNetwork.printWeight();
    
    return 0;
}