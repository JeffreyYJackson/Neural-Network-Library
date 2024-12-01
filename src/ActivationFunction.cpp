#include "..\include/ActivationFunction.h"

double ActivationFunction::ReLU(double value){
    if (value < 0) {return 0;}
    return value;
}
