#include <vector>

#include "..\include/ActivationFunction.h"

#include "..\include\Network.h"
#include "..\include\LayerBuilder.h"
#include "..\include\WeightBuilder.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {5, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);
    
    LayerBuilder::buildLayers(myNetwork);
    WeightBuilder::buildWeightLayers(myNetwork);

    myNetwork.printLayerVals(0);

    if (myNetwork.input({1, 4, 3}) == 0) return 0;

    myNetwork.printLayerVals(0);

    
    return 0;
}