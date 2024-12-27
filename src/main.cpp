#include "..\include\Network.h"

#include<iostream>

//Main function for testing
int main(){
    Network myNetwork;

    myNetwork.pushLayer(1);
    myNetwork.pushLayer(5, ReLU);
    myNetwork.pushLayer(5, Sigmoid);

    myNetwork.printWeight();

    if(!myNetwork.input({7})){return 0;}
    myNetwork.pass();
    myNetwork.printLayerVals(1);

    myNetwork.save("test.txt");

    std::cout << "new network\n";

    Network newNetwork = Network("test.txt");

    newNetwork.printWeight();

    if(!newNetwork.input({7})){return 0;}
    newNetwork.pass();
    newNetwork.printLayerVals(1);
    
    return 0;
}