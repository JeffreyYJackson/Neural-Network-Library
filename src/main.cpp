#include "..\include/ActivationFunction.h"

#include "..\include\Network.h"

#include<iostream>

//Main function for testing
int main(){
    
    std::vector<unsigned int> nodeLayers = {3, 4};
    Network myNetwork = Network(nodeLayers);

    /*
    if(!Network::input(myNetwork, {200, 3.5})){return 0;}

    myNetwork.printLayerVals(0);

    Network::pass(myNetwork);
    myNetwork.printLayerVals(2);
    */
    
    myNetwork.printWeight();

    myNetwork.save(myNetwork, "test.txt");
    
    Network newNetwork = Network("test.txt");

    std::cout<< "Depth: " << newNetwork.depth << "\n";
    std::cout<< "Nodes:\n";
    for(unsigned int i = 0; i < newNetwork.depth; i++){
        std::cout << newNetwork.nodesCount.at(i) << "\n";
    }

    std::cout<< "Biases:\n";
    for (std::vector<Node> i : newNetwork.layers) {
        for (Node j : i){
            std::cout << j.bias;
        }
        std::cout << "\n";
    }

    newNetwork.printWeight();

    
    return 0;
}