#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>
typedef struct recurrent{
    int number_of_times_left_side;
    int number_of_times_right_side;
} recurrent;
void merge(std::vector<int>& array, int ini, int fin){
    int medio = ini + (fin - ini)/2;
    int n1 = medio - ini + 1;
    int n2 = fin - medio;
    std::vector<int> left(n1),right(n2);
    for(int i = 0; i< n1; i++){
        left[i] = array[ini + i];
    }
    for(int i = 0; i< n2; i++){
        right[i] = array[medio +1 + i];
    }
    int i = 0, j = 0, k = ini;
    while (i < n1 && j < n2){
        if(left[i] <= right[j]){
            array[k] = left[i];
            i++;
        }else{
            array[k] = right[j];
            j++;
        }
        k++;
    }
    while( i < n1){
        array[k] = left[i];
        k++;
        i++;
    }
    while( j < n2){
        array[k] = right[j];
        k++;
        j++;
    }
    
}
void mergesort(std::vector<int>& array,int ini, int fin){
   if(ini < fin){
    int medio = ini + (fin - ini)/2;
    mergesort(array,ini,medio);
    mergesort(array,medio+1,fin);
    merge(array,ini,fin);
   }  
}
int main(){
    std::ifstream file("day1_puzzle");
    if(!file){
        std::cerr << "Error opening the file!"<<std::endl;
        return 1;
    }
    std::vector<int> left_side = {};
    std::vector<int> right_side;
    std::string line;
   int number1,number2;
    while(std::getline(file,line)){
        std::istringstream iss(line);
        if(iss >> number1 >> number2){
            left_side.push_back(number1);
            right_side.push_back(number2);
        }   
    }
    mergesort(left_side,0,left_side.size() - 1);
    mergesort(right_side,0,right_side.size()-1);
   int distance = 0;
    for (int i = 0; i < left_side.size();i++){
        if(left_side[i] < right_side[i]){
            distance += right_side[i] -left_side[i];
        }
        else{
            distance += left_side[i] - right_side[i];
        }
    }
    std::cout << distance;

}