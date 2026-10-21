#include<iostream>

int main(){
    auto i = 0;
    auto x = "hello";
    auto& y = i; //int&类型
    auto&& z = 10;//int&&，10为右值，自动为右值
    auto&& c = i;//int& ，i为左值，自动为左值。
    //auto v; 报错，必须要初始化。

    return 0;
}