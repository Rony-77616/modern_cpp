#include<iostream>
#include<thread>


void fun(){
    std::cout<<"子线程执行"<<std::endl;
}



void print(int x){
    std::cout<<"x = "<<x<<std::endl;
}



void print_1(int id){
    for(int i = 1;i<=5;i++){
        std::cout<<"thread:"<<id<<"第"<<i<<"次\n";
    }
}



int main(){

    //创建线程
    std::thread t(fun);

    std::cout<<"主线程执行"<<std::endl;

    t.join();//主线程等待子线程结束


    //lambda创建线程
    std::thread t1([](){
        std::cout<<"子线程2执行"<<::std::endl;
    });

    t1.join();



    //传参创建线程
    std::thread t2(print,100);//相当于传print（100）进去
    t2.join();


    //lambda传参创建
    std::thread t3([](int y){
        std::cout<<"y = "<<y<<std::endl;
    },50);
    t3.join();



    //两个线程同时执行
    std::thread t4(print_1,1);
    std::thread t5(print_1,2);

    t4.join();
    t5.join(); //输出是混乱的，因为两个线程同时执行，由操作系统调度，可能穿插执行，穿插输出。
    //join用于让当前线程等待目标线程执行结束，并回收目标线程的相关资源。
    //不是在哪里join就在哪开始执行，从创建了线程开始就有可能开始执行了
    //join只是在这里让主线程等待他执行完，再往下执行。
    return 0;
}