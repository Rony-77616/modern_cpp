#include<iostream>
#include<memory>
#include<string>


void print(const std::string& s){
    std::cout<<"左值:"<<s<<std::endl;
}

void print(std::string&& s){
    std::cout<<"右值："<<s<<std::endl;
}





int main(){
    std::string s = "hello1";
    std::string&& s1 = std::move(s);
    print("hello2");
    print(std::move(s));//编译器为了区分是移动构造还是拷贝，在编译器内部会有协议，用&&来优先接受右值引用，因此可以区分，这也是move要先将其转为右值的原因。
    print(s);
    print(s1);

    return 0;
}