#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstring>

enum Movements{
    LEFT_UP_DIAGONAL,
    RIGHT_UP_DIAGONAL,
    LEFT_DOWN_DIAGONAL,
    RIGHT_DOWN_DIAGONAL,
    VERTICAL_UP,
    VERTICAL_DOWN,
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT,
};
 struct Mystruct{
    int x;
    int y;
    Movements movement;
    Mystruct(int x,int y,Movements movement){
        this->movement = movement;
        this ->x = x;
        this->y = y;
    }
};
bool check_one_movement(std::vector<std::string>& text,Mystruct &Position, char char_to_check){
    int x = Position.x;
    int y = Position.y;
    Movements movement = Position.movement;
    int i,j; 
    switch (movement){
    case LEFT_DOWN_DIAGONAL:
        i = x+1;
        j = y-1;
        if(i < text.size() && j >= 0 && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case RIGHT_DOWN_DIAGONAL:    
        i = x+1;
        j = y+1;
        if(i < text.size() && j < text[i].size() && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case LEFT_UP_DIAGONAL:    
        i = x-1;
        j = y-1;
        if(i >=0 && j >= 0 && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case RIGHT_UP_DIAGONAL:    
        i = x-1;
        j = y+1;
        if(i >= 0  && j < text[i].size() && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case VERTICAL_DOWN:    
        i = x+1;
        j = y;
        if(i < text.size() && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case VERTICAL_UP:    
        i = x-1;
        j = y;
        if(i >= 0 && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case HORIZONTAL_LEFT:    
        i = x;
        j = y-1;
        if(j >= 0 && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;
        }
        break;
    case HORIZONTAL_RIGHT:    
        i = x;
        j = y+1;
        if( j < text[i].size() && text[i][j] == char_to_check){
            Position.x = i;
            Position.y = j;
            return true;

        }
        break;
    }
    return false;
}
std::vector<Mystruct> check_contacting_letters(std::vector<std::string>& text,int x, int y){
    std::vector<Mystruct> accepted;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if((x + i) >= 0 && (x + i) < text.size() && (y + j) >= 0 && (y + j) < text[x+i].size() && text[x+i][y+j] == 'M'){
                Movements movement;
                if(i == -1 && j == -1){ movement = LEFT_UP_DIAGONAL;  }
                else if(i == 0 && j == -1){ movement = HORIZONTAL_LEFT;  }
                else if(i == 1 && j == -1){ movement = LEFT_DOWN_DIAGONAL;  }
                else if(i == -1 && j == 0){ movement =  VERTICAL_UP;  }
                else if(i == 1 && j == 0){ movement = VERTICAL_DOWN;  }
                else if(i == -1 && j == 1){ movement = RIGHT_UP_DIAGONAL;  }
                else if(i == 0 && j == 1){ movement = HORIZONTAL_RIGHT;  }
                else if(i == 1 && j == 1){ movement = RIGHT_DOWN_DIAGONAL;  }

                accepted.push_back(Mystruct(x+i,y+j,movement));
            } 
        }
    }
    return accepted;
}

int check_for_xmas(std::vector<std::string>& text){
    int result = 0;
    const char* to_check = "AS";
    std::vector<Mystruct> possibilities_xmas;
    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < text[i].size(); j++){
            if(text[i][j] == 'X'){
                possibilities_xmas = check_contacting_letters(text,i,j);
                for(Mystruct possibility : possibilities_xmas){
                    if(check_one_movement(text,possibility,to_check[0]) && check_one_movement(text,possibility,to_check[1])){
                        result+=1;
                    }
                }
                
            }
        }
    }
    return result;
}
int main() {
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

