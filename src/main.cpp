#include "..\include/ActivationFunction.h"

#include "..\include\Network.h"
#include "..\include\LayerBuilder.h"
#include "..\include\WeightBuilder.h"
#include "..\include\ForwardPass.h"

#include<iostream>

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {5, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);
    
    LayerBuilder::buildLayers(myNetwork);
    WeightBuilder::buildWeightLayers(myNetwork);

    myNetwork.printLayerVals(0);

    if (ForwardPass::input(myNetwork ,{1, 4, 3, 1, 1}) == 0) return 0;

    myNetwork.printLayerVals(0);
   
    Node node;
    node.bias = -3;
    ForwardPass::calculateNodeValue(node, myNetwork.layers.at(0), myNetwork.weights.at(0).at(0));

    std::cout<<"Node value: " << node.value << "\n";

    
    return 0;
}