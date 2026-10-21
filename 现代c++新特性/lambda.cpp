#include<iostream>
#include<vector>
#include<algorithm>
int main(){
    //1.接收两个int，计算它们的和
    auto sum = [](int x,int y){
        return x+y;
    };

    std::cout<<sum(1,2)<<std::endl;


    //2.接收一个int，判断是否为偶数
    auto x = [](int x){
        return x%2 == 0 ? true :false; 
    };

    
    if(x(2)){
        std::cout<<"ou"<<std::endl;
    }
    else{
        std::cout<<"not ou"<<std::endl;
    }



    //3.判断一个数是否大于外部定义的limit
    int limit = 10;
    auto y = [&](int x){
      if(x >= limit){
        return true;
      }  
      return false;
    };

    std::cout<<(y(15) ? "yes":"no")<<std::endl;
    

    //4.lambda排序
    std::vector<int> v= {2, 5, 1,5, 1,8 ,4 ,0, 1,77,100,2666};
    std::sort(v.begin(),v.end(),[](int a,int b){
        return a>b;
    });


    for(const& a:v){
        std::cout<<a<<" ";
    }
    std::cout<<std::endl;
    


    //5.统计大于limit的个数
    std::vector<int> v1 = {1,2,3,4,5,6,4,34,2,31,3,5,4532,423,6345,4324,7657,46,22,77};
    int limit1 = 50;
    auto many = [&limit1]( const std:: vector<int>& v){
        int count = 0;
        for(const auto& a:v){
            if(a >= limit1) count++;
        }
        return count;
    };

    std::cout<<"shuliang:"<<many(v1)<<std::endl;


    return 0;
}