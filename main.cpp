#include <iostream>
#include <vector>
#include<random>

class Node{
    private:
        int layer;
        float bias = 0;

    public:
        float value;

        void setBias(float biasVal) {this->bias = biasVal;}
        float getBias(){return this -> bias;}

        float calculateValue(std::vector<Node> input, std::vector<float> weights);
};

class Network{
    private:
        std::vector<int> nodesCount;
        int depth;

        std::vector<std::vector<Node>> layers; //2 dimensional vector storing layers. First layer being input and last layer being output.
        std::vector<std::vector<std::vector<float>>> weights; //3 dimensional vector containing the weights to use in the edges.

        void createWeightLayer(int targetConnection); 
        void createWeights(int targetConnect, int targetNode);
        void buildWeightLayers();
        
    public:
        Network(std::vector<int> nodesCount, bool isRandom = true);
        //Functions to import and save networks.
        void import();////////////////////////////////////////////////////////////////
        void save();

        //Build the first gen network on random values.
        void buildNetwork(); //Function to build the entire network.
        void buildLayer(std::vector<Node> &nodes, int numberOfNodes); //Function to build layers of the networks. Specify input, hidden vs output layer initiation.

        //Functions to retrieve private attributes of the object.
        std::vector<int> getNodeCount() {return this -> nodesCount;}
        int getDepth() {return this -> depth;}
};

//Constructor function.
Network::Network(std::vector<int> nodesCount, bool isRandom) : nodesCount(nodesCount), depth(nodesCount.size()) {
    for(int i = 0; i < this->depth; i++) {
        //Create an element for next layer.
        std::vector<Node> a;//////////////////////////////////////////////Naming
        this->layers.push_back(a);

        //Build next layer
        this->buildLayer(this->layers.at(i), nodesCount.at(i));
    }
}

//Function to build a layer.
void Network::buildLayer(std::vector<Node> &nodes, int numberOfNodes) {
    for(int i = 0; i < numberOfNodes; i++) {
        Node node = Node();
        nodes.push_back(node);
    }
}

//Creates weights at random connecting a node to all of the nodes in the previous layer.
void Network::createWeights(int targetConnect, int targetNode) {
    //Set up random device
    std::random_device rd;
    std::mt19937 gen(rd());

    //A normal distribution with a mean of 0 and a variance of 2/inputNumber for He initialization.
    std::normal_distribution<> dist(0, sqrt((double)2/this->nodesCount.at(targetConnect)));

    //Creating random weights for the nth connection between layers (layer n and n+1). n number of weights 
    for(int i = 0; i < this->nodesCount.at(targetConnect); i++){
        this->weights.at(targetConnect).at(targetNode).push_back(dist(gen));
    }
}

//Creates a group of weights which contains all the weights connecting all of the nodes in a layer to the nodes in the previous layer.
void Network::createWeightLayer(int targetConnect) {
    for (int i = 0; i < this->nodesCount.at(targetConnect + 1); i++){
        std::vector<float> b; ///////////////////////////////////////////////////// Naming
        this->weights.at(targetConnect).push_back(b);

        this->createWeights(targetConnect, i);
    }
}

//Builds all of the weights between each layers of the Network.
void Network::buildWeightLayers() {
    for(int i = 0; i < this->depth - 1; i++){
        std::vector<std::vector<float>> a;
        this->weights.push_back(a);/////////////////////////////////Naming

        this->createWeightLayer(i);
    }
}

//Main function for testing
int main(){
    
    std::vector<int> nodeLayers {5, 10, 5, 2};

    Network myNetwork = Network(nodeLayers);


    myNetwork.buildWeightLayers();


    
int sum = 0;

    
    

    for (std::vector<std::vector<float>> k: myNetwork.weights){
        for(std::vector<float> i: k){
            
            int count = 0;

            for(float j: i){

                std::cout << j << "\n";

                count++;
                sum++;
            }
        
            std::cout<<count<<"\n";
         
        }

    }

    
    std::cout<<sum<<"\n";


    

    return 0;
}