#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstring>
int dont = 0;
int does=0;
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
void check_line(std::string& line,long unsigned int& result,bool& enable){
    std::string mul = "mul(",enable_mult = "do()",disable_mul = "don't()";
    std::string temp,temp_disable;
    int pos_ini;
    int final_pos;
    std::cout<<enable<<std::endl;
    for (size_t i = 0; i < line.size(); i++){
        temp = line.substr(i,4);
        temp_disable = line.substr(i,7);
        if(temp == enable_mult){
            if(!enable)std::cout<<!enable<<std::endl;
            enable = true;
            does++;
        }
        if(temp_disable == disable_mul){
            if(enable)std::cout<<!enable<<std::endl;
            enable = false;
            dont++;
        }
        if(enable && temp == mul){
            pos_ini = i;
            i+=4;
            result += valid_multiplication(line,i,final_pos);
            if(final_pos > 0){
                std::string multi = line.substr(pos_ini,final_pos-pos_ini);
                std::cout<<multi<<std::endl;
            }
        }
    }
    std::cout<<"do:"<<does<<std::endl;
    std::cout<<"dont: "<<dont<<std::endl;
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
    bool enable=true;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        check_line(line,result,enable);
    }
    std::cout<<result;
    return 0;
}

