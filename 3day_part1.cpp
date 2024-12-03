#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstring>
int int_to_char(std::string number){
    int num = 0;
    for(int i = 0; i < number.size(); i++){
        num = num*10 + number[i] - '0';
    }
    return num;
}
//you have to give a position that starts with a number 
int get_number(std::string& line,size_t &pos){
     std::string number;
    do{
        number += line[pos];
        pos++;
    }while( pos < line.size() && line[pos] <= '9' && line[pos] >= '0');
    return int_to_char(number);
}
long unsigned int valid_multiplication(std::string& line, size_t pos,int& final_pos){
    final_pos = -1;
    if(line[pos] > '9' || line[pos] < '0'){
        return 0;
    }
    int first_number = get_number(line,pos);
    if((pos + 1) >= line.size() || line[pos] != ',' || line[pos+1] > '9' || line[pos +1] < '0'){
        return 0;
    }
    pos++;
    int second_number = get_number(line,pos);
    if(pos >= line.size() || line[pos]!=')'){
        return 0;
    }
    long unsigned int result = first_number* second_number;
    final_pos = ++pos;
    return result;
}
void check_line(std::string& line,long unsigned int& result){
    std::string mul = "mul(";
    std::string temp;
    int pos_ini;
    int final_pos;
    for (size_t i = 0; i < line.size(); i++){
        temp = line.substr(i,4);
        if(temp == mul){
            pos_ini = i;
            i+=4;
            result += valid_multiplication(line,i,final_pos);
            if(final_pos > 0){
                std::string multi = line.substr(pos_ini,final_pos-pos_ini);
                std::cout<<multi<<std::endl;
            }
        }
    }
}
int main() {
    std::ifstream file("day3_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> reports;
    std::string line;
    long unsigned int result = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        check_line(line,result);
    }
    std::cout<<result;
    return 0;
}
