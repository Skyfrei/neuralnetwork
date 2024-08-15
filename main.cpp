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

        Network(std::vector<float> in, int outp, mat2d w) : outputSize(outp){
            mat2d m;
            for (int i = 0; i < w.size(); i++){
                m.push_back(w[i]);
            }
        

            for (int i = 0; i < in.size(); i++){
                m[i].insert(m[i].begin(), in[i]);
            }

            AddLayer(in.size(), m);;
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
                std::vector<float> temp;
                temp.push_back(z);
                res.push_back(temp);
            }



            for (int i = 0; i < layers.size(); i++){
                for (int j = 0; j < layers[i].zweights.size(); j++){
                    for (int k = 1; k < layers[i].zweights[0].size(); k++){
                        float r = 0.0f;
                        for (int g = 0; g < layers[i].zweights[0].size(); g++){
                            r += res[j][0] * layers[i].zweights[k][g];
                        }                       
                        res[j][k].push_back(Sigmoid(r));
                    }
                }
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
    mat2d guess = {{3, 2}, {1.5, 2}};


    Network net(input, output, guess);

    return 0;
}
