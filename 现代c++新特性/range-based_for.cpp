#include<vector>
#include<iostream>
int main(){
    std::vector<char> v = {'a','b','c'};
    for(const auto& a : v){
        std::cout<<a<<" ";
    }

    return 0;
}