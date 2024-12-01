#include "Network.h"
#include "Node.h"

class ForwardPass{
    public:
        static int input(Network &Network, std::vector<float> inputs);

        static void pass(Network &Network);
    private:
        static void calculateLayerValue(std::vector<Node> &layerNodes, std::vector<Node> &inputLayerNodes, std::vector<std::vector<float>> &weightLayer);
        static void calculateNodeValue(Node &targetNode, std::vector<Node> inputNodes, std::vector<float> weights);
        
};