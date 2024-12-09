#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <queue>
uint64_t calculate_checksum(std::vector<int64_t>& memory) {
    uint64_t result = 0;
    uint64_t max_value = std::numeric_limits<uint64_t>::max();

    for (size_t i = 0; i < memory.size(); i++) {
        if (memory[i] != -1) {
            // Verificar posible overflow en la multiplicación
            if (memory[i] > 0 && i > max_value / memory[i]) {
                std::cerr << "Overflow detectado en la multiplicación: memory[" << i << "] * " << i << std::endl;
                return result; // Puedes manejarlo devolviendo el resultado parcial
            }

            // Suma segura después de multiplicación
            uint64_t term = memory[i] * i;
            if (result > max_value - term) {
                std::cerr << "Overflow detectado en la suma: result + " << term << std::endl;
                return result; // Puedes manejarlo devolviendo el resultado parcial
            }

            result += term;
        }
    }
    return result;
}
void alaign_memory(std::vector<int64_t>& memory){
    for(int i = 0; i < memory.size(); i++){
        while(memory[memory.size()-1] == -1){
            memory.pop_back();
        }
        if(memory[i] == -1){
            memory[i] = memory[memory.size() -1];
            memory.pop_back();
        }
    }
}
void create_memory(std::queue<int>& size_files,std::queue<int>& empty_space,std::vector<int64_t>& memory){
    int size;
    int64_t file = -1;
    while(!size_files.empty()){
        size = size_files.front();
        file++;
        for(int i = 0; i < size; i++){
            memory.push_back(file);
        }
        size_files.pop();
        size = empty_space.front();
        for(int i = 0; i < size; i++){
            memory.push_back(-1);
        }
        empty_space.pop();
    }
}
int main(){
    std::ifstream file("day9_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    std::string line;
    int number;
    std::queue<int> size_files;
    std::queue<int> empty_space;
    bool is_empty_space = false;
    // Lectura del archivo
    while (std::getline(file, line)){
        for(int i = 0; i < line.size(); i++){
            number = line[i] - '0';
            if(is_empty_space){
                empty_space.push(number);
            }else{
                size_files.push(number);
            }
            is_empty_space = !is_empty_space;
        }
    }      
    std::cout << "empty : "<<empty_space.size()<< "  file:"<<size_files.size();
   std::vector<int64_t> memory;
    create_memory(size_files,empty_space,memory);
    alaign_memory(memory);
    uint64_t result = calculate_checksum(memory);
    std::cout<<std::endl<<"result: "<<result<<std::endl;
    return 0;
}
