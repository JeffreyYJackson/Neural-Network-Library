#include <vector>

#include "..\include\Network.h"
#include "..\include\LayerBuilder.h"
#include "..\include\WeightBuilder.h"

//Main function for testing
int main(){
    std::vector<unsigned int> nodeLayers = {5, 20, 20, 10};
    Network myNetwork = Network(nodeLayers);
    
    LayerBuilder::buildLayers(myNetwork);
    WeightBuilder::buildWeightLayers(myNetwork);

    myNetwork.printWeight();
    return 0;
}