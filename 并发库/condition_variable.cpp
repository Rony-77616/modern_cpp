#include<iostream>
#include<mutex>
#include<queue>
#include<thread>
#include<condition_variable>


int main(){

    std::queue<int> q;
    std::queue<int> res;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    std::thread t([&](){
        std::unique_lock<std::mutex> uni_lock(mtx);
        cv.wait(uni_lock,[&ready](){
            return ready;
        });
        
        while(!q.empty()){
            res.push(q.front() * q.front());
            q.pop();
        }
        while(!res.empty()){
            std::cout<<res.front()<<" ";
            res.pop();
        }
        uni_lock.unlock();
    });
    
    {
        std::lock_guard<std::mutex> guard(mtx);
        int x;
        do{
            std::cin>>x;
            if(x!=0){
            q.push(x);
            }
        }while(x != 0);
        ready = true;//ready修改要写在锁里面
    }//准备数据好了，解锁
    
    cv.notify_all();
    t.join();
    return 0;
}