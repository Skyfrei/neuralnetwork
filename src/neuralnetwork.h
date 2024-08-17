#include <vector>

typedef std::vector<std::vector<float>> mat2d;

struct Layer{
    
    Layer(int l) : units(l){}
    int units;
    std::vector<std::vector<float>> zweights;
    float bias = 1.0f;
};

class Network{
    
    public:

        Network(std::vector<float> in, int outp, int hidden, mat2d w);
        void AddLayer(int unit, mat2d z);

        int GetClassifier();
        void Train();
    private:
        void print(mat2d a);
        void SGD();
        float Sigmoid(float z);
        mat2d CalculateNetworkValue();
        std::vector<float> GetLastCol(mat2d inp);
        std::vector<float> Sample(std::vector<float> inp, int size);
    private:
        std::vector<Layer> layers;
        int outputSize;
        int epoch = 1000;
        const float lr = 0.01;

};


