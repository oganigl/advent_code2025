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

uint64_t calculate_checksum(std::vector<int64_t>& memory) {
    uint64_t result = 0;
    uint64_t max_value = std::numeric_limits<uint64_t>::max();

    for (size_t i = 0; i < memory.size(); i++) {
        if (memory[i] != -1) {
            result += memory[i]*i;
        }
    }
    return result;
}
void clean_empty_spaces_at_the_end(std::vector<std::pair<int,int>>& empty_space, int last_pos){
    for(int i = empty_space.size() -1; i >= 0; i--){
        if(empty_space[i].second > last_pos){
            empty_space.pop_back();
        }else{
            return;
        }
    }
}
std::pair<int,int> find_size(std::vector<std::pair<int,int>>& empty_space,int size,int& pos_empty_space){
    
    for(int i = 0; i < empty_space.size(); i++){
        if(empty_space[i].first >= size){
            pos_empty_space = i;
            return empty_space[i];
        }
    }
    pos_empty_space = -1;
    return std::make_pair(-1,-1);
}
void alaign_memory(std::vector<std::pair<int,int>>& size_files,std::vector<std::pair<int,int>>& empty_space,std::vector<int64_t>& memory){
    int j;
    while(!size_files.empty() || !empty_space.empty()){
        int size_file = size_files[size_files.size()-1].first;
        int pos_file = size_files[size_files.size()-1].second;
        int pos_empty_space;
        clean_empty_spaces_at_the_end(empty_space,pos_file);
        std::pair<int,int> pos_to_replace = find_size(empty_space,size_file,pos_empty_space);
        if(pos_to_replace.second != -1){
            for(j = 0; j <  size_file; j++){
                memory[pos_to_replace.second + j] = memory[pos_file + j];
                memory[pos_file + j] = -1; //transform to empty
            }
            //eliminate empty space
            if(pos_to_replace.first == size_file){
                empty_space.erase(empty_space.begin() + pos_empty_space);
            }else{
                empty_space[pos_empty_space] = std::make_pair(pos_to_replace.first - size_file,pos_to_replace.second + j); 
            }
        }
        size_files.pop_back();
        
    }
}
void create_memory(std::vector<std::pair<int,int>>& size_files,std::vector<std::pair<int,int>>& empty_space,std::vector<int64_t>& memory){
    int size;
    for(int i = 0; i < size_files.size(); i++){
         size = size_files[i].first;
         size_files[i].second = memory.size();
        for(int j = 0; j < size; j++){
            memory.push_back(i);
        }
        if(empty_space.empty()) continue;
        size = empty_space[i].first;
        empty_space[i].second = memory.size();
        for(int j = 0; j < size; j++){
            memory.push_back(-1);
        }
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
    std::vector<std::pair<int,int>> size_files; //number of memory and where is located in memory the file
    std::vector<std::pair<int,int>> empty_space;
    bool is_empty_space = false;
    // Lectura del archivo
    while (std::getline(file, line)){
        for(int i = 0; i < line.size(); i++){
            number = line[i] - '0';
            if(is_empty_space){
                empty_space.push_back(std::make_pair(number,-1));
            }else{
                size_files.push_back(std::make_pair(number,-1));
            }
            is_empty_space = !is_empty_space;
        }
    }      
   
    std::vector<int64_t> memory;
    create_memory(size_files,empty_space,memory);
    std::cout << "empty : "<<empty_space.size()<< "  file:"<<size_files.size();
    alaign_memory(size_files,empty_space,memory);
    uint64_t result = calculate_checksum(memory);
    std::cout<<std::endl<<"result: "<<result<<std::endl;
    return 0;
}
