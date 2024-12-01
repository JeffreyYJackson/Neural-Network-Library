#include "..\include/Network.h"
#include "..\include\LayerBuilder.h"

#include <iostream>

void Network::printWeight(){
    int sum = 0;
    for (std::vector<std::vector<float>> k: this->weights){
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
}

float Network::generateGaussian(double mean, double standardDev){
    std::normal_distribution<> dist(mean, standardDev);
    return (float)dist(this->gen);
}