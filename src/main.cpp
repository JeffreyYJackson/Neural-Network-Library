#include "..\include\Network.h"

#include<iostream>

//Main function for testing
int main(){
    Network Network;

    Network.pushLayer(5, ActivationFunction::ReLU, ActivationFunction::ReLU_Random_Gen);

    Network.pushLayer(5, ActivationFunction::ReLU, ActivationFunction::ReLU_Random_Gen);
    Network.randomizeLayerWeights(1);

    Network.printWeight();

    if(!Network.input({7, 3.5, 3, 4, 5})){return 0;}

    Network.pass();

    Network.printLayerVals(1);


    /*
    std::vector<unsigned int> nodeLayers = {3, 4};
    Network myNetwork = Network(nodeLayers, ReLU);
    myNetwork.save("test.txt");

    Network secondNetwork = Network("test.txt");

    if(!secondNetwork.input({7, 3.5, 1})){return 0;}

    secondNetwork.printLayerVals(0);

    secondNetwork.pass();
    
    secondNetwork.printLayerVals(1);
    */

    return 0;
}