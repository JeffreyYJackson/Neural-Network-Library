#include "..\include\Network.h"

#include<iostream>

std::vector<std::vector<float>> generateRandom2DVector(int numElements, int numValuesPerElement) {
    std::vector<std::vector<float>> vec(numElements, std::vector<float>(numValuesPerElement));
    for (int i = 0; i < numElements; ++i) {
        for (int j = 0; j < numValuesPerElement; ++j) {
            vec[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }
    }
    return vec;
}

std::vector<std::vector<float>> multiply2DVectorByTwo(const std::vector<std::vector<float>> vec) {
    std::vector<std::vector<float>> result = vec;
    for (auto& row : result) {
        for (auto& elem : row) {
            elem *= 2;
        }
    }
    return result;
}

//Main function for testing
int main(){
    Network network = Network("gradientDescentTest.txt");

    if(!network.input({27})){return 0;}
    network.pass();
    network.printLayerVals(3);


    
    
    return 0;
}