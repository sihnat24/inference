#pragma once
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

class Tensor {
public:
    int rows;
    int cols;
    std::vector<float> data;

    Tensor(int rows, int cols)
        : rows(rows), cols(cols), data(rows * cols + 1, 0.0f) //+1 for bias column
    {}

    float& at(int i, int j) {
        return data[i * cols + j];
    }

    const float& at(int i, int j) const {
        return data[i * cols + j];
    }

    static Tensor from_file(const std::string& path, int rows, int cols) {
        Tensor v(rows, cols);
        std::ifstream f(path, std::ios::binary);
        if (!f) throw std::runtime_error("Cannot open: " + path);
        f.read(reinterpret_cast<char*>(v.data.data()), rows * cols * sizeof(float));
        return v;
    }

    Tensor add(const Tensor& a, const Tensor& b){

        if (a.rows != b.rows || a.cols != b.cols) {
            throw std::invalid_argument("Tensor dimension mismatch");
        }
        
        Tensor out(a.rows, a.cols);
        
        for (int i = 0; i < a.rows; i++){
            for (int j = 0; j < a.cols; j++){
                out.at(i,j) = a.at(i,j) + b.at(i,j);
            }
        }
        return out;
    }

    //Tensor transpose

    Tensor matmul(const Tensor& other){
       if (cols != other.rows){
        throw std::invalid_argument("Tensor dimension mismatch");
       } 

       Tensor m(rows,other.cols); //create new tensor
       
       float dp;

       for (int i = 0; i < rows; i++){
        for (int j = 0; j < other.cols; j++){
            dp = 0.0;
            for (int p = 0; p < cols; p++){ //shared dim
                dp += this->at(i,p) * other.at(p,j);
            }
            m.at(i,j) = dp;
        }
       }
       return m;
    }

    Tensor transpose() const{
        Tensor t(cols,rows);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                t.at(j,i) = this->at(i,j);
            }
        }
        return t;
    }

    void relu(){ //mutuate the tensor in place
        for (int i = 0; i<rows; i++){
            for (int j = 0; j<cols; j++){
                this->at(i,j) = std::max(0.0f,this->at(i,j));
            }
        }
    }

    void sigmoid(){
        for (int i = 0; i<rows; i++){
            for (int j = 0; j<cols; j++){
               this->at(i, j) = 1.0f / (1.0f + std::exp(-this->at(i, j))); 
            }
        }
    }

};
