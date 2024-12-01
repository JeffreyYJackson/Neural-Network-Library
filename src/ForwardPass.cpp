#include "..\include\ForwardPass.h"
#include "..\include\ActivationFunction.h"

#include <iostream>

int ForwardPass::input(Network &Network, std::vector<float> inputs){
    //Check for error
    if(inputs.size() != Network.nodesCount.at(0)) {
        std::cout << "Input values do not match the input layer of network.\n Input Layer Size: " << Network.nodesCount.at(0) << "\n";
        std::cout << "Passed Input Size: " << inputs.size() << "\n";
        return 0;
    }
    
    //Set input layer to _input.
    for (unsigned int i = 0; i < Network.nodesCount.at(0); i++){
        Network.layers.at(0).at(i).value = inputs.at(i);
    }
    return 1;
}

void ForwardPass::pass(Network &Network){
    for(unsigned int i = 0; i < Network.depth - 1; i++){
        calculateLayerValue(Network.layers.at(i + 1), Network.layers.at(i), Network.weights.at(i));
    }
}

void ForwardPass::calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer){
    for (unsigned int i = 0; i < layerNodes.size(); i++){
        ForwardPass::calculateNodeValue(layerNodes.at(i), inputLayerNodes, weightLayer.at(i));
    }
}

void ForwardPass::calculateNodeValue(Node &targetNode, std::vector<Node> inputNodes, std::vector<float> weights){
    float nodeVal = targetNode.bias;

    for (unsigned int i = 0; i < inputNodes.size(); i++){
        nodeVal += (inputNodes.at(i).value * weights.at(i));
    }
    targetNode.value = ActivationFunction::ReLU(nodeVal);
}
