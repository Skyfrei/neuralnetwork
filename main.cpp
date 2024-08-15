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

        Network(std::vector<float> in, int outp, int hidden, mat2d w) : outputSize(outp){
            mat2d m;
            for (int i = 0; i < w.size(); i++){
                m.push_back(w[i]);
            }
        

            for (int i = 0; i < in.size(); i++){
                m[i].insert(m[i].begin(), in[i]);
            }

            AddLayer(in.size(), m);

            for (int i = 0; i < hidden; i++){
                mat2d m1;

                for (int i = 0; i < outp * 2; i++){
                    std::vector<float> temp = {0.0, 0.0};
                    m1.push_back(temp);
                }
                for (int i = 0; i < 2; i++){
                    m1[i].insert(m1[i].begin(), 0.0f);
                }

                AddLayer(2, m1);
            }
        }

        void AddLayer(int unit, mat2d z){
            Layer l(unit);
            l.zweights = z;
            layers.push_back(l);
            mat2d a = CalculateUnitValue();
            print(a);
        }

        void print(mat2d a){
            for (int i = 0; i < a.size(); i++){
                for (int j = 0; j < a[0].size(); j++){
                    std::cout<<a[i][j] << " ";
                }
                std::cout<<"\n";
            }
        }


    private:
        float Sigmoid(float z){
            return 1 / (1 + std::pow(std::numbers::e, -1 * z));
        }

        mat2d CalculateUnitValue(){
            mat2d res;
            
            for (int i = 0; i < layers[0].zweights.size(); i++){
                float z = Sigmoid(layers[0].zweights[i][0]); 
                std::vector<float> temp = {z};
                res.push_back(temp);
            }


            for (int i = 0; i < layers.size(); i++){
                std::vector<float> tempV;
                for (int wCol = 1; wCol < layers[i].zweights[0].size(); wCol++){
                    float temp;
                    for (int zRow = 0; zRow < layers[i].zweights.size(); zRow++){
                        temp += res[zRow][wCol - 1] * layers[i].zweights[zRow][wCol];
                    }
                    tempV.push_back(Sigmoid(temp));
                }
                res.push_back(tempV);
            }   
            return res;
        }
    
    private:
        std::vector<Layer> layers;
        int outputSize;
        float bias = 2;
};


int main(){
    
    std::vector<float> input = {0.3, 0.2};
    int output = 2;
    int hidden = 1;
    mat2d guess = {{3, 2}, {1.5, 2}};


    Network net(input, output, hidden, guess);

    return 0;
}
