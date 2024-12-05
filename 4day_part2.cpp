#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstring>

bool valid_x_mas(std::vector<std::string>& text, int i, int j){
    //possibilities possitions
    std::pair left_up = std::make_pair(i-1,j-1);
    std::pair left_down = std::make_pair(i+1,j-1);
    std::pair right_up = std::make_pair(i-1,j+1);
    std::pair right_down = std::make_pair(i+1,j+1);
    //First check one diagonal and then the other
    if((text[left_up.first][left_up.second] == 'M' && text[right_down.first][right_down.second] == 'S') || (text[left_up.first][left_up.second] == 'S' && text[right_down.first][right_down.second] == 'M')){
        if((text[left_down.first][left_down.second] == 'M' && text[right_up.first][right_up.second] == 'S') || (text[left_down.first][left_down.second] == 'S' && text[right_up.first][right_up.second] == 'M')){
            return true;
        }
    }
    return false;
}
int check_for_xmas(std::vector<std::string>& text){
    int result = 0;
    for(int i = 1; i < text.size(); i++){
        for(int j = 1; j < text[i].size(); j++){
            //all the comprobations
            if(text[i][j]=='A' && (i+1) < text.size() && (i-1) >= 0 && (j+1) < text[i].size() && (j-1) >= 0 && valid_x_mas(text,i,j)){
                result+=1;
            }
        }
    }
    return result;
}
int main() {
    std::cout<<"empieza:\n";
    std::ifstream file("day4_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::vector<std::string> text;
    std::string line;
    while (std::getline(file, line)) {
        text.push_back(line);
    }
    int result = check_for_xmas(text);
    std::cout<<"Result: "<<result;
    return 0;
}

