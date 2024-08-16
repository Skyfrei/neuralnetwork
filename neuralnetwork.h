#include <iostream>
#include <vector>
#include <numbers>
#include <cmath>

typedef std::vector<std::vector<float>> mat2d;

struct Layer{
    
    Layer(int l) : units(l){}
    int units;
    std::vector<std::vector<float>> zweights;
};

class Network{
    
    public:

        Network(std::vector<float> in, int outp, int hidden, mat2d w);
        void AddLayer(int unit, mat2d z);

        int GetClassifier();
    private:
        void print(mat2d a);
        void SGD();
        float Sigmoid(float z);
        mat2d CalculateUnitValue();

    private:
        std::vector<Layer> layers;
        int outputSize;
        float bias = 2;
};


