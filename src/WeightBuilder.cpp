#include "..\include/Network.h"
#include "..\include\WeightBuilder.h"

//Builds all of the weights between each layers of the Network.
void WeightBuilder::buildWeightLayers(Network &Network) {
    Network.weights = std::vector<std::vector<std::vector<float>>>(Network.depth);
    for(unsigned int i = 0; i < Network.depth - 1; i++){
        WeightBuilder::createWeightLayer(i, Network);
    }
}

//Creates a group of weights which contains all the weights connecting all of the nodes in a layer to the nodes in the previous layer.
void WeightBuilder::createWeightLayer(unsigned int targetConnect, Network &Network) {
    //Build weight vectors.
    Network.weights.at(targetConnect) = std::vector<std::vector<float>>(Network.nodesCount.at(targetConnect + 1));
    
    //Call function to generate random weights for all nodes.
    for (unsigned int i = 0; i < Network.nodesCount.at(targetConnect + 1); i++){
        //this->createWeights(targetConnect, i);
        WeightBuilder::createWeights(targetConnect, i, Network);
    }
}

//Creates weights at random connecting a node to all of the nodes in the previous layer(nth connection between layers (layer n and n+1). n number of weights).
void WeightBuilder::createWeights(unsigned int targetConnect, unsigned int targetNode, Network &Network) {
    //Build weights.
    Network.weights.at(targetConnect).at(targetNode) = std::vector<float>(Network.nodesCount.at(targetConnect));

    for(unsigned int i = 0; i < Network.nodesCount.at(targetConnect); i++){
        //A normal distribution with a mean of 0 and a variance of 2/inputNumber for He initialization.
        Network.weights.at(targetConnect).at(targetNode).at(i) = Network.generateGaussian(0, sqrt((double)2/Network.nodesCount.at(targetConnect)));
    }
}