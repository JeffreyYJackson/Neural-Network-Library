#include "Network.h"

class WeightBuilder{
    public:
        static void buildWeightLayers(Network &Network);
    private:
        static void createWeightLayer(unsigned int targetConnection, Network &Network); 
        static void createWeights(unsigned int targetConnect, unsigned int targetNode, Network &Network);
};