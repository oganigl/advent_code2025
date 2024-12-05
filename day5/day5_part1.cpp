#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <set>

void swap(std::vector<int>& section,int pos, int i){
    int aux = section[pos];
    section[pos] = section[i];
    section[i] = aux;
}
int check_right_order(std::vector<int>& section, std::unordered_map<int,std::vector<int>>& print_numbers){
    std::set<int> numbers_already_print(section.begin(),section.end()); // to have it always in increasing order 
    for(int i = 0; i < section.size(); i++){
        numbers_already_print.erase(section[i]); //eliminate from the set
        if(print_numbers.find(section[i]) != print_numbers.end()){
            for(const auto& before_number : print_numbers[section[i]]){
                size_t pos = numbers_already_print.find(before_number);
                if( pos != numbers_already_print.end()){
                    swap(section,pos,i);
                    return 0;
                }
            }
        }
    }
    int half = 0 + (section.size() - 0)/2;
    return section[half];
}
int main() {
    std::ifstream file("day5_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    std::unordered_map<int,std::vector<int>> print_numbers; // key = number that has to go second value = vector with all the numbers that must go before this number 
    std::string line;
    int number1,number2;
    char delimiter;
    int number;
    std::vector<std::vector<int>> cases;
    std::string token;
    int i = 0;
    while (std::getline(file, line)) {
        if(line.empty()){
            continue;
        }
        std::istringstream iss(line);
        if(line.find('|') != std::string::npos){
            iss>>number1>>delimiter>>number2;
            print_numbers[number2].push_back(number1);
        
        }else{
             if (cases.size() <= i){
            cases.push_back(std::vector<int>()); // Crear un nuevo vector si no existe
            }   
            while(std::getline(iss,token,',')){
                cases[i].push_back(std::stoi(token));
            }
            i++;
        } 
    }      
    long int result = 0;
    for(int i = 0; i < cases.size(); i++){
        result += check_right_order(cases[i],print_numbers);
    }
        
    std::cout<<result;
    return 0;
}
