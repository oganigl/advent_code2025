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
int resolve_map(std::vector<std::string> map,int i, int j){
    Pos pos = find_guard(map);
    if(map[i][j] == '#' || (i == pos.x && j == pos.y)){
        return 0;
    }else{
        map[i][j] = '#';
    }
    int map_size = map.size();
    int line_size = map[0].size();
    std::unordered_map<Orientation,std::vector<std::pair<int,int>>> corners;
    while(!(pos.x < 0 || pos.x > (map_size - 1) || pos.y < 0 || pos.y > (line_size - 1))){
        switch (pos.orientation){
            case LEFT:
                if(map[pos.x][pos.y] != '#'){
                    for(const auto& coordinate : corners[LEFT]){
                        if(pos.x == coordinate.first && pos.y == coordinate.second){
                            return 1;
                        }
                    }
                    pos.y--;
                }else{
                    pos.y++;
                    corners[pos.orientation].push_back(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                break;
            case RIGHT:
                if(map[pos.x][pos.y] != '#'){
                    for(const auto& coordinate : corners[RIGHT]){
                        if(pos.x == coordinate.first && pos.y == coordinate.second){
                            return 1;
                        }
                    }
                    pos.y++;
                }else{
                    pos.y--;
                    corners[pos.orientation].push_back(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                break;
            case UP:
                if(map[pos.x][pos.y] != '#'){
                    for(const auto& coordinate : corners[UP]){
                        if(pos.x == coordinate.first && pos.y == coordinate.second){
                            return 1;
                        }
                    }
                    pos.x--;
                }else{
                    pos.x++;
                    corners[pos.orientation].push_back(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                    }
                break;
            case DOWN:
                if(map[pos.x][pos.y] != '#'){
                    for(const auto& coordinate : corners[DOWN]){
                        if(pos.x == coordinate.first && pos.y == coordinate.second){
                            return 1;
                        }
                    }
                    pos.x++;
                }else{
                    pos.x--;
                    corners[pos.orientation].push_back(std::make_pair(pos.x,pos.y));
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                    }
                break;
        }
    }
    return 0;
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
    long int result = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map.size(); j++){
            result+=resolve_map(map,i,j);
        }
    }

        
    std::cout<<"result: "<<result<<std::endl;
    return 0;
}
