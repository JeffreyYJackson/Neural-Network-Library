#include "..\include/ActivationFunction.h"

#include "..\include\Network.h"

#include<iostream>

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {3, 4};
    Network myNetwork = Network(nodeLayers);
    myNetwork.save("test.txt");

    Network secondNetwork = Network("test.txt");

    if(!secondNetwork.input({7, 3.5, 1})){return 0;}

    secondNetwork.printLayerVals(0);

    secondNetwork.pass();
    secondNetwork.printLayerVals(1);
    return 0;
}