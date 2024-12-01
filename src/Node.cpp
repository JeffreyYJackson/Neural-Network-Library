#include "..\include/Node.h"

void Node::setBias(float biasVal) {this->bias = biasVal;}

float Node::getBias() {return this -> bias;}

void Node::setValue(float _value){this->value = _value;}

float Node::getValue(){return this->value;}