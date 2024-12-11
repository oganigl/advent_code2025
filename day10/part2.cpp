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
#include <queue>
struct Coordinate{
    int x;
    int y;
    Coordinate(int i, int j):x(i),y(j){}
};
bool find_coordinate_in_vector(std::vector<Coordinate>& nines_reach_from_a_zero,Coordinate a){
    for(const auto& coor : nines_reach_from_a_zero){
        if(coor.x == a.x && coor.y == a.y){
            return true;
        }
    }
    return false; 
}
void reach_trailheads(std::vector<Coordinate>& nines_reach_from_a_zero,int i, int j, std::vector<std::string>& map,uint64_t& total){
    if(map[i][j] == '9'){
        total++;
        nines_reach_from_a_zero.push_back(Coordinate(i,j));
        return;
    }
    if((j+1) < map[i].size() && map[i][j+1] == map[i][j] +1){
        reach_trailheads(nines_reach_from_a_zero,i,j+1,map,total);
    }
    if((j-1) >= 0 && map[i][j-1] == map[i][j] +1){
        reach_trailheads(nines_reach_from_a_zero,i,j-1,map,total);
    }
    if((i+1) < map.size() && map[i+1][j] == map[i][j] +1){
        reach_trailheads(nines_reach_from_a_zero,i+1,j,map,total);
    }
    if((i-1) >= 0 && map[i-1][j] == map[i][j] +1){
        reach_trailheads(nines_reach_from_a_zero,i-1,j,map,total);
    }
}
int main(){
    std::ifstream file("day10_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> map;
    // Read the file
    while (std::getline(file, line)){
       map.push_back(line);
    }    
    std::vector<Coordinate> nines_reach_from_a_zero; 
    
    uint64_t result = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '0'){
                uint64_t total = 0;
                nines_reach_from_a_zero.clear();
                reach_trailheads(nines_reach_from_a_zero,i,j,map,total);
                result += total;
            }
        }
    }
     std::cout<<"result: "<<result;
    return 0;
}
