#include<iostream>
#include<memory>
#include<string>


class test{
public:
    test(){
        std::cout<<"调用test构造函数"<<std::endl;
    }
    test(int x):num(x){
        std::cout<<"调用test的int有参构造函数,num = "<<num<<std::endl;
    }
    test(std::string str){
        std::cout<<"调用test的string有参构造,std = "<<str<<std::endl;
    }

    void setnum(int x){
        num = x;
        return ;
    }

    void print(){
        std::cout<<"num = "<<num<<std::endl;
        return ;
    }



    ~test(){
        std::cout<<"调用test析构函数"<<std::endl;
    }
private:
    int num;
};


int main(){
    //unique_ptr的初始化：

    //1.unique_ptr的构造函数方式初始化
    std::unique_ptr<int>p1(new int(1));


    //注意：unique_ptr没有拷贝构造的方式来初始化，不然就会违背独占的智能指针的原则，有两个智能指针指向同一块内存了。
    //注意：unique_ptr没有use_ count函数，也没有make方法
    //2.unique_ptr的移动构造函数方式初始化：
    std::unique_ptr<int>p2 = move(p1);

    //3.reset方法初始化：
    std::unique_ptr<int> p3(new int(100));
    p3.reset();//p3对其一开始初始化的内存的管理权丧失。
    p3.reset(new int(99)); //p3管理这一块new出来的内存


    //unique_ptr的使用：
    //1.get方法来获取原始地址：
    std::unique_ptr<test> p4(new test(1));

    test *t = p4.get();

    //2.直接当成一个指针来使用:
    p4->setnum(100);
    p4->print();


    //unique_count的删除器使用以及写法:
    //unique_ptr的删除器与shared_ptr的删除器不同，前者需要指定函数器的类型，而后者不需要

    //1.删除器是一个无捕获的lambda表达式
    std::unique_ptr<test,void(*)(test*)> ppp(new test,[](test* t){
        delete t;
    });

    std::unique_ptr<test,void(*)(test*)> ppp1(new test[5],[](test* t){
        delete[] t;
    });
//删除器是一个无捕获的lambda表达式的时候，指定删除器类型的时候，用一个函数指针类型来指定，void表示函数没有返回值，（*）表示这是一个函数指针，（test*）表示传入函数的参数类型
    


    //unique_ptr可以管理数组类型的内存地址，可以自动释放，不需要删除器
    std::unique_ptr<test[]> ppp2(new test[10]);
    //必须要把数组类型写到模板参数里面，才支持管理数组，<test[]>
    //其实，shared_ptr也是支持这样的写法，只是在c++11不支持，后面的版本都支持。




std::cin.get();
return 0;
}