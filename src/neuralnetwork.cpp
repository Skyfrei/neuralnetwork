#include "neuralneddtwork.h"
#include <iostream>

#include <cmath>
#include <numbers>
#include <random>

Network::Network(std::vector<float> in, int outp, int hidden, mat2d w) : outputSize(outp){
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

         for (int i = 0; i < 2; i++){
             std::vector<float> temp = {0.2, 0.1};
             m1.push_back(temp);
         }
         for (int i = 0; i < 2; i++){
             m1[i].insert(m1[i].begin(), 0.0f);
         }

         AddLayer(2, m1);
     }

     // Output
     mat2d outpp;
     for (int i = 0; i < 2; i++){
         std::vector<float> temp = {1.0};
         outpp.push_back(temp);
     }
     for (int i = 0; i < 2; i++){
         outpp[i].insert(outpp[i].begin(), 0.0f);
     }
     AddLayer(2, outpp);
     


}

void Network::AddLayer(int unit, mat2d z){
    Layer l(unit);
    l.zweights = z;
    layers.push_back(l);
}

std::vector<float> Network::GetLastCol(mat2d inp){
    std::vector<float> output;
    for (int i = 0; i < r.size(); i++){
        output.push_back(r[i][r.size()]);
    }
    return output;
}


int Network::GetClassifier(){

    int index;
    float max = 0.0f;
    mat2d r = CalculateNetworkValue();
    std::vector<float> output = GetLastCol(r);

    for (int i = 0; i < output.size(); i++){
       if (max < output[i]){
           index = i;
           max = output[i];
       }
    }

   return index + 1;
}

void Network::print(mat2d a){
    for (int i = 0; i < a.size(); i++){
       for (int j = 0; j < a[0].size(); j++){
           std::cout<<a[i][j] << " ";
       }
       std::cout<<"\n";
    }
}

float Network::Sigmoid(float z){
    return 1 / (1 + std::pow(std::numbers::e, - 1 * z));
}

mat2d Network::CalculateNetworkValue(){
    mat2d res;
   
   for (int i = 0; i < layers[0].zweights.size(); i++){
       float z = layers[0].zweights[i][0]; 
       std::vector<float> temp = {z};
       res.push_back(temp);
   }

   for (int i = 0; i < layers.size() - 1; i++){
       std::vector<float> tempV;

       for (int wCol = 0; wCol < layers[i + 1].zweights.size(); wCol++){
           float temp = 0.0f;
           for (int zRow = 0; zRow < layers[i].zweights.size(); zRow++){
               temp += res[zRow][i] * layers[i].zweights[zRow][wCol + 1];
           }
           tempV.push_back(Sigmoid(temp + layers[i].bias));
       }
       for(int g = 0; g < tempV.size(); g++){
           res[g].push_back(tempV[g]); 
       }
   
   }
   print(res);
   return res;
}

std::vector<float> Network::Sample(std::vector<float> inp, int size){
    std::vector<float> res;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, size - 1); // distribution in range [1, 6]
    
    for (int i = 0; i < size; i++)
        res.push_back(dist6(rng));

    return res;
}


void Network::SGD(){
    int batch_size = 4;
    float realY = 1.0f;

    for (int i = 0; i < epoch; i++){
        std::vector<float> fullpredY = GetLastCol(CalculateNetworkValue());
        std::vector<float> sample = Sample(lastCol, batch_size);
//        std::vector<float> realY;
        std::vector<float> predY;
        std::vector<float> loss;
        std::vector<float> gradVec;


        for (int j = 0; j < batch_size; j++){
            predY.push_back(fullpredY[sample[i]]);
//            realY.push_back()(
            loss.push_back(std::pow(realY[i] - predY[i]), 2);
//            gradVec.push_back(loss[i]) / batch_size);
//
        }



    }


}

void Network::Train(){


}
