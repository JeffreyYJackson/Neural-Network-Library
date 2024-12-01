#include "Network.h"
#include "Node.h"

class ForwardPass{
    public:
        static int input(Network &Network, std::vector<float> inputs);

        static void calculateNodeValue(Node &targetNode, std::vector<Node> inputNodes, std::vector<float> weights);
        
};