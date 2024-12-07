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

bool evaluate_result(std::vector<uint64_t>& section, std::vector<char>& operator_to_use) {
    uint64_t result = section[1];  
    for (int i = 2; i < section.size(); i++) {
        if (operator_to_use[i - 2] == '+') {
            result += section[i];
        } else {
            result *= section[i];
        }
    }
    return result == section[0];  
}

bool try_combination(std::vector<uint64_t>& section, int addition) {
    std::vector<char> operator_to_use(section.size() - 1, '*');  
    for (int i = 0; i < addition; i++) {
        operator_to_use[i] = '+';  
    }

    std::sort(operator_to_use.begin(), operator_to_use.end());  

    do {
        if (evaluate_result(section, operator_to_use)) {
            return true;  
        }
    } while (std::next_permutation(operator_to_use.begin(), operator_to_use.end()));

    return false;  
}

uint64_t compare_result(std::vector<uint64_t>& section) {
    for (int i = 0; i <= section.size() - 2; i++) {  
        if (try_combination(section, i)) {
            return section[0]; 
        }
    }
    return 0;  

int main() {
    std::ifstream file("day7_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<uint64_t>> map;
    uint64_t number;
    char delimiter;
    int j = 0;
    
    // Lectura del archivo
    while (std::getline(file, line)) {
        map.push_back(std::vector<uint64_t>());
        std::istringstream iss(line);
        if (line.find(':') != std::string::npos) {
            iss >> number >> delimiter;
            map[j].push_back(number);
            while (iss >> number) {
                map[j].push_back(number);
            }
        }
        j++;
    }      

    uint64_t result = 0;
    uint64_t partial_result;

    // Procesar cada línea del archivo
    for (int i = 0; i < map.size(); i++) {
        partial_result = compare_result(map[i]);

        // Verificar si la suma produce un overflow
        if (result > std::numeric_limits<uint64_t>::max() - partial_result) {
            std::cout << "Overflow detectado en la suma." << std::endl;
            return 1;
        }

        result += partial_result;  // Sumar el resultado parcial al total
    }

    std::cout << "Resultado final: " << result << std::endl;
    return 0;
}
