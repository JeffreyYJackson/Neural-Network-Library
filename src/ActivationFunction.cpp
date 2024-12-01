#include "..\include/ActivationFunction.h"

float ActivationFunction::ReLU(float value){
    if (value < 0) {return 0;}
    return value;
}
