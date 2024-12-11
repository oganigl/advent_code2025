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
void print(std::unordered_map<uint64_t,uint64_t>& stones){
    std::cout<<"\n";
    for(const auto& [key,value] : stones){
        std::cout<<"  "<<key<<" : "<<value;
    }
    std::cout<<"\n";
}
bool even_number(uint64_t number, uint64_t& part1_number, uint64_t& part2_number) {
    // Determina la cantidad de dígitos en el número
    uint64_t factor = 1;
    size_t i;
    for (i = 0; factor <= number; i++) {
        factor *= 10;
    }

    // Si la cantidad de dígitos es impar, retorna falso
    if (i % 2 != 0) {
        return false;
    }

    // Divide el número en dos partes (superior e inferior)
    uint64_t split = pow(10, (i / 2));
    part1_number = number / split;  // Parte superior
    part2_number = number % split;  // Parte inferior
    return true;
}

int main() {
    std::ifstream file("day11_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    std::string line;
    std::unordered_map<uint64_t, uint64_t> stones; // first = stone number / second = count of stones with that number
    uint64_t number;

    // Leer el archivo y poblar el mapa stones
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> number) {
            stones[number] = 1;  // Suponemos que hay una piedra por cada número en la entrada
        }
    }

    uint64_t MAX_SIZE = stones.max_size();
    uint64_t part_number1, part_number2;

    for (int i = 0; i < 75; i++) {
        std::cout << "Iteration: " << i << "\n";
        //print(stones);
        std::unordered_map<uint64_t,uint64_t> temporal;
        for (const auto& [key, value] : stones) {
            if (key == 0) {
                temporal[1] += value; 
            } else if (even_number(key, part_number1, part_number2)) {
                temporal[part_number1] += value;  
                temporal[part_number2] += value;  
            } else {
                temporal[key * 2024] += value;
            }
        }
        stones = temporal;
    }

    // Calcular el resultado sumando todos los valores de las piedras
    uint64_t result = 0;
    for (const auto& pair : stones) {
        result += pair.second;
    }

    std::cout << "Result: " << result << "\n";
    return 0;
}
