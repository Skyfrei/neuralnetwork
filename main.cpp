#include "src/neuralnetwork.h"
#include <iostream>

int main(){
    
    std::vector<float> input = {0.3, 0.2};
    int output = 2;
    int hidden = 1;
    mat2d guess = {{0.2, 0.3}, {0.2, 0.5}};


    Network net(input, output, hidden, guess);
    std::cout<< net.GetClassifier();
    return 0;
}
