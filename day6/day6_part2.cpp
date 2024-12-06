#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <utility>
enum Orientation{
    LEFT,
    UP,
    RIGHT,
    DOWN,
};
struct Pos{
    int x;
    int y;
    Orientation orientation;
    Pos(int i, int j, Orientation ori):x(i),y(j),orientation(ori){}
};
// Define a function to sort left_right
bool compareLeftRight(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}
// Define a function to sort up_down
bool compareUpDown(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second < b.second || (a.second == b.second && a.first < b.first);
}

//global variables 
std::set<std::pair<int, int>, decltype(&compareLeftRight)> left(&compareLeftRight);
std::set<std::pair<int, int>, decltype(&compareLeftRight)> right(&compareLeftRight);
std::set<std::pair<int, int>, decltype(&compareUpDown)> up(&compareUpDown);
std::set<std::pair<int, int>, decltype(&compareUpDown)> down(&compareUpDown);
bool reach_a_point_without_crashing(std::vector<std::string>& map,Pos ini,int x_final, int y_final){
    Orientation orientation = ini.orientation;
    int x = ini.x;
    int y = ini.y;
    switch (orientation)
    {
    case LEFT:
        while(y != y_final){
            if(map[x][y] == '#'){
                return false;
            }
            y--;
        }
        return true;
    case RIGHT:
        while(y != y_final){
            if(map[x][y] == '#'){
                return false;
            }
            y++;
        }
        return true;
    case UP:
        while(x != x_final){
            if(map[x][y] == '#'){
                return false;
            }
            x--;
        }
        return true;
    case DOWN:
        while(x != x_final){
            if(map[x][y] == '#'){
                return false;
            }
            x++;
        }
        return true;
    }
    return true;
}
bool check_create_loop(std::vector<std::string>& map,Pos actual){
    int x = actual.x;
    int y =  actual.y;
    Orientation orientation = actual.orientation;
    switch (orientation)
    {
    case LEFT:
        for(const auto& coordinate : up){
            if(y == coordinate.second && x > coordinate.first){
                if(reach_a_point_without_crashing(map,Pos(x,y,static_cast<Orientation>((orientation + 1) % 4)),coordinate.first,coordinate.second)){
                    return true;
                }
            }
        }
        break;
    case RIGHT:
         for(const auto& coordinate : down){
            if(y == coordinate.second && x < coordinate.first){
                if(reach_a_point_without_crashing(map,Pos(x,y,static_cast<Orientation>((orientation + 1) % 4)),coordinate.first,coordinate.second)){
                    return true;
                }
            }
        }
        break;
    case UP:
         for(const auto& coordinate : right){
            if(x == coordinate.first && y < coordinate.second){
                if(reach_a_point_without_crashing(map,Pos(x,y,static_cast<Orientation>((orientation + 1) % 4)),coordinate.first,coordinate.second)){
                    return true;
                }
            }
        }
        break;
    case DOWN:
        for(const auto& coordinate : left){
            if(x == coordinate.first && y > coordinate.second){
                if(reach_a_point_without_crashing(map,Pos(x,y,static_cast<Orientation>((orientation + 1) % 4)),coordinate.first,coordinate.second)){
                    return true;
                }
            }
        }
        break;
    }
    return false;
}
Pos find_guard(std::vector<std::string>& map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == '<'){
                return Pos(i,j,Orientation::LEFT);
            }else if(map[i][j] == '>'){
                return Pos(i,j,Orientation::RIGHT);
            }else if(map[i][j] == '^'){
                return Pos(i,j,Orientation::UP);
            }else if(map[i][j] == 'v'){
                return Pos(i,j,Orientation::DOWN);
            }
        }
    }
    return Pos(-1,-1,DOWN);
}
long int resolve_map(std::vector<std::string>& map){
    Pos pos = find_guard(map);
    int map_size = map.size();
    int line_size = map[0].size();
    long int total = 0;
    while(!(pos.x < 0 || pos.x > (map_size - 1) || pos.y < 0 || pos.y > (line_size - 1))){
        switch (pos.orientation){
        case LEFT:
                if(map[pos.x][pos.y] != '#'){
                    if(check_create_loop(map,pos)){
                        total++;
                    }
                    pos.y--;
                }else{
                    pos.y++;
                    left.insert(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
            break;
        case RIGHT:
              if(map[pos.x][pos.y] != '#'){
                if(check_create_loop(map,pos)){
                    total++;
                }
                    pos.y++;
                }else{
                    pos.y--;
                    right.insert(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
            break;
        case UP:
            if(map[pos.x][pos.y] != '#'){
                if(check_create_loop(map,pos)){
                    total++;
                }
                pos.x--;
                }else{
                    pos.x++;
                    up.insert(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
            break;
        case DOWN:
            if(map[pos.x][pos.y] != '#'){
                if(check_create_loop(map,pos)){
                    total++;
                }
                pos.x++;
                }else{
                    pos.x--;
                    down.insert(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
            break;
        }
    }
    return total;
}
int main() {
    std::ifstream file("day6_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> map;

    while (std::getline(file, line)) {
        map.push_back(line);
    } 
    long int result;
    result = resolve_map(map);
        
    std::cout<<"result: "<<result;
    return 0;
}
