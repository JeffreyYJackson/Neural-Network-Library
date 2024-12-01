#include "..\include/ActivationFunction.h"

#include "..\include\Network.h"
#include "..\include\LayerBuilder.h"
#include "..\include\WeightBuilder.h"
#include "..\include\ForwardPass.h"

#include<iostream>

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {1, 1};
    Network myNetwork = Network(nodeLayers);
    
    LayerBuilder::buildLayers(myNetwork);
    WeightBuilder::buildWeightLayers(myNetwork);

    if (ForwardPass::input(myNetwork ,{5}) == 0) return 0;

    myNetwork.printLayerVals(0);
    std::cout<<"\n";
    myNetwork.printWeight();
    std::cout<<"\n";
    myNetwork.printLayerVals(1);
    std::cout<<"\n";
    
    ForwardPass::pass(myNetwork);
    
    myNetwork.printLayerVals(1);
    
    return 0;
}