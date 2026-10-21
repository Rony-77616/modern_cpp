#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<functional>

int count = 0;

std::mutex mtx;//可以把锁定义在全局变量，减少传参

void add(){
    mtx.lock();
    for(int i = 0;i<10000;i++){
    count++;
    }
    mtx.unlock();
}


void insert_vec(int x,std::vector<int>& v){
    for(int i = 0;i<500;i++){
    mtx.lock();
    v.push_back(i+x);
    mtx.unlock();
    }
}



int main(){
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout<<count<<std::endl;

    std::vector<int> v;
    std::thread t3(insert_vec,0,std::ref(v));//若要传引用，线程里面传递参数必须要显示ref传递。
    std::thread t4(insert_vec,1000,std::ref(v));

    t3.join();
    t4.join();

    std::cout<<v.size()<<std::endl;


    return 0;

}
