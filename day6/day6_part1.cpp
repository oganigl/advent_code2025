#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <set>
#include <algorithm>
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
long int resolve_map(std::vector<std::string>& map){
    Pos pos = find_guard(map);
    int map_size = map.size();
    int line_size = map[0].size();
    long int total = 0;
    while(!(pos.x < 0 || pos.x > (map_size - 1) || pos.y < 0 || pos.y > (line_size - 1))){
        switch (pos.orientation){
        case LEFT:
                if(map[pos.x][pos.y] != '#'){
                    if(map[pos.x][pos.y] != 'X'){
                        map[pos.x][pos.y] = 'X';
                        total++;
                    }
                }else{
                    pos.y++;
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                pos.y--; // left movement
            break;
        case RIGHT:
              if(map[pos.x][pos.y] != '#'){
                    if(map[pos.x][pos.y] != 'X'){
                        map[pos.x][pos.y] = 'X';
                        total++;
                    }
                }else{
                    pos.y--;
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                pos.y++; // right movement
            break;
        case UP:
              if(map[pos.x][pos.y] != '#'){
                    if(map[pos.x][pos.y] != 'X'){
                        map[pos.x][pos.y] = 'X';
                        total++;
                    }
                }else{
                    pos.x++;
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                pos.x--; // up movement
            break;
        case DOWN:
              if(map[pos.x][pos.y] != '#'){
                    if(map[pos.x][pos.y] != 'X'){
                        map[pos.x][pos.y] = 'X';
                        total++;
                    }
                }else{
                    pos.x--;
                    pos.orientation = static_cast<Orientation>((pos.orientation + 1) % 4);
                    continue;
                }
                pos.x++; // down movement
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
