#include <iostream>
#include <vector>


struct NetworkParameters
{
        int depth; //Total number of layers.
        std::vector<int> NodesCount;//Number of nodes in layers all layers.(0==Input, Last==Output, Rest==Hidden)
};

class Node{
        int layer;
        float bias = 0;

    public:
        float value;

        void setBias(float biasVal){this->bias = biasVal;}
        float getBias(){return this -> bias;}

        float calculateValue(std::vector<Node> input, std::vector<float> weights);
};




class Network{
        

        NetworkParameters parameters;

        std::vector<std::vector<Node>> layers; //2 dimensional vector storing layers. First layer being input and last layer being output.
        std::vector<std::vector<std::vector<float>>> weights; //3 dimensional vector containing the weights to use in the edges.

    public:
        Network(NetworkParameters param, bool isRandom = true): parameters(param){}
        //Functions to import and save networks.
        void import();////////////////////////////////////////////////////////////////
        void save();

        //Build the first gen network on random values.
        void buildNetwork(); //Function to build the entire network.
        void buildLayer(std::vector<Node> &nodes, int numberOfNodes); //Function to build layers of the networks. Specify input, hidden vs output layer initiation.


        //Functions to retrieve private attributes of the object.
        std::vector<int> getNodeCount(){return this -> parameters.NodesCount;}
        int getDepth(){return this -> parameters.depth;}
};

//Constructor function.
Network::Network(NetworkParameters param, bool isRandom = true){

    for(int i = 0; i < param.depth; i++){
        this->buildLayer(this->layers.at(i), param.NodesCount.at(i));
    }


}

//Function to build a layer.
void Network::buildLayer(std::vector<Node> &nodes, int numberOfNodes){

    for(int i = 0; i < numberOfNodes; i++){
            Node node = Node();
            nodes.push_back(node);
        }
}

int main(){
    
    NetworkParameters param {4, {5, 10, 5, 2}};

    Network myNetwork = Network(param);

    myNetwork.buildNetwork();

    
    
    /*
    cout << myNetwork.getInputNodes() << "\n";
    cout << myNetwork.getOutputNodes() << "\n";
    cout << myNetwork.getDepth() << "\n";
    cout << myNetwork.getHiddenNodes() << "\n";
    */

    return 0;
}