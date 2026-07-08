#include <vector>
#include <iostream>
#include <utility>

class Tensor{
    public:
        int rows;
        int cols;
        std::vector<std::vector<double>> data;
        
        Tensor(int rows, int cols) : 
            rows(rows), 
            cols(cols), 
            data(rows, std::vector<double>(cols, 0.0))
        {}

        Tensor(std::vector<std::vector<double>> input) : 
            data(input), 
            rows(input.size()), //number of lists in list
            cols(input.empty() ? 0 : input[0].size()) //size of sublist
        {}


        std::pair<int,int> size(){
            return {rows,cols};
        }

        std::vector<double>& operator[](int x){
            return data[x];
        }

        const std::vector<double>& operator[](int x) const{
            return data[x];
        }
};

int main(){
    std::cout << "gabagoo" << std::endl;
};