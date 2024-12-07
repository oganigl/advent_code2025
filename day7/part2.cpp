#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdint>

uint64_t join_two_numbers(uint64_t a, uint64_t b) {
    uint64_t factor = 1;
    while (factor <= b) {
        factor *= 10;
    }
    return a * factor + b;
}

bool evaluate_result(const std::vector<uint64_t>& section, const std::vector<char>& operators) {
    uint64_t result = section[1];  
    for (size_t i = 2; i < section.size(); ++i) {
        if (operators[i - 2] == '+') {
            result += section[i];
        } else if (operators[i - 2] == '*') {
            result *= section[i];
        } else if (operators[i - 2] == '|') {
            result = join_two_numbers(result, section[i]);
        }
    }
    return result == section[0];  
}

bool try_combination(const std::vector<uint64_t>& section, int num_additions, int num_joins) {
    std::vector<char> operators(section.size() - 1, '*');
    for (int i = 0; i < num_additions; ++i) {
        operators[i] = '+';
    }
    for (int j = 0; j < num_joins; ++j) {
        operators[num_additions + j] = '|';
    }

    std::sort(operators.begin(), operators.end());
    do {
        if (evaluate_result(section, operators)) {
            return true;
        }
    } while (std::next_permutation(operators.begin(), operators.end()));

    return false;
}

uint64_t compare_result(const std::vector<uint64_t>& section) {
    for (int num_additions = 0; num_additions < section.size() - 1; ++num_additions) {
        for (int num_joins = 0; num_additions + num_joins < section.size() - 1; ++num_joins) {
            if (try_combination(section, num_additions, num_joins)) {
                return section[0];
            }
        }
    }
    return 0;
}

int main() {
    std::ifstream file("day7_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::vector<std::vector<uint64_t>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<uint64_t> section;
        std::istringstream iss(line);
        uint64_t number;
        char delimiter;

        if (line.find(':') != std::string::npos) {
            iss >> number >> delimiter;  
            section.push_back(number);
            while (iss >> number) {
                section.push_back(number);
            }
            data.push_back(section);
        }
    }

    uint64_t total_result = 0;

    for (const auto& section : data) {
        uint64_t partial_result = compare_result(section);

        if (total_result > std::numeric_limits<uint64_t>::max() - partial_result) {
            std::cerr << "Overflow detectado en la suma." << std::endl;
            return 1;
        }
        total_result += partial_result;
    }

    std::cout << "Resultado final: " << total_result << std::endl;
    return 0;
}
