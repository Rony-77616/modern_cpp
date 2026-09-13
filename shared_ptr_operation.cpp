#include<iostream>
#include<memory>
#include<string>

class Test{//定义一个Test类:
public:
    Test(){//Test类型构造函数

        std::cout<<"执行Test构造函数"<<std::endl;
        
    }

    Test(int x):num(x){
        std::cout<<"执行Test构造函数,num = "<<num<<std::endl;
    }

    Test(std::string str) {
        std::cout<<"执行Test构造函数，str = "<<str<<std::endl;
    }

    ~Test(){//Test类型析构函数
        std::cout<<"执行Test析构函数"<<std::endl;
    }

    void setnum(int x){//成员函数，设定私有成员num的值
        num = x;
    }

    void print(){//成员函数，打印num的值
        std::cout<<"num = "<<num<<std::endl;
    }

private:
int num;
};


int main(){
      //1.通过构造函数初始化shared_ptr
      std::shared_ptr<int> p1(new int(3));
      std::cout<<"p1 use_count = "<<p1.use_count()<<std::endl;//查看有多少个智能指针指向该块new出来的内存,注意：必须要用拷贝构造，
                                                              //才能保证两个智能指针管理同一个内存，如果用同一个裸指针分别构造，就会导致两个智能指针原始地址相同
                                                              //但是use_count都是1，即所有权不同，都会析构一次，会报错

      //2.通过移动构造和拷贝构造初始化shared_ptr
      std::shared_ptr<int> p2 = move(p1);//移动构造，管理这块内存的指针由p1变为了p2, p1丢失管理权
      std::cout<<"p1 use_count = "<<p1.use_count()<<std::endl;//查看有多少个指针指向该内存,由于失去管理权，已被置空，p1指向的内存为null，没有其他的指针与其指向同一块内存，
      //use_count应为0
      std::cout<<"p2 use count = "<<p2.use_count()<<std::endl;//应为1


      std::shared_ptr<int> p3 = p2;//拷贝构造函数，之所以用p2，是因为此时该块内存的管理权在p2上
      std::cout<<"p2 use_count = "<<p2.use_count()<<std::endl;
      std::cout<<"p2 use_count = "<<p3.use_count()<<std::endl;//查看有多少个指针管理着这块内存，此时有p2，p3两个指针，应为2


      //3.通过std::make_shared辅助函数初始化
      std::shared_ptr<int> p4 = std::make_shared<int>(8);//直接开辟一个int，初始化为8，并且由p4管理
      std::shared_ptr<Test> p5 = std::make_shared<Test>(5);//开辟一个Test，由带int参数的构造函数初始化，由p5管理
      std::shared_ptr<Test> p6 = std::make_shared<Test>("hello world");//由带string类型参数的构造函数初始化，由p6管理


      //4.通过reset初始化
        //reset有两个功能，一个是重置指针，另一个是让一个指针重新指向另一块内存
        //重置指针:
      p6.reset();//reset之后，p6重置，不再管理上面那块字符串初始化的内存，引用计数变为0，由于引用计数变为0，该块内存就被析构掉了
      std::cout<<"p6 use_count = "<<p6.use_count()<<std::endl;//应为0

        //让一个指针指向管理另一块内存
        p5.reset(new Test(99));//reset后不能指向一块与原本类型不同的内存空间，必须前后一致
        std::cout<<"p5 use_count = "<<p5.use_count()<<std::endl;





        //shared_ptr的使用：
        //1.get方法获取原始指针，返回智能指针内部管理的原始指针，也就是它所管理的内存块的地址。
        Test* t = p5.get();// ！！注意：p5虽然是一个智能指针，但是他是一个类模板，是一个智能指针对象，内部封装了get方法，所以用.来调用get，而不是->。
        t->setnum(1000);
        t->print();

        //2.通过智能指针对象直接进行操作
        //应该把智能指针直接看作一个指针
        p5->setnum(999);
        p5->print();


        //指定删除器函数
        std::shared_ptr<Test> ppp(new Test(100), [](Test *t){
            //做一个释放内存的操作
            std::cout<<"----------------"<<std::endl;
            delete t;
        });//new后面指定了删除器，可以在外面写，也可以直接写一个匿名函数,用于告诉智能指针，在释放它管理的内存资源时，
            //不要用默认的delete，而是用我指定的方式去释放
            //什么时候构造必须要指定删除器呢，就是在这个智能指针管理一个数组的时候，直接默认delete不能够删除掉一个数组，因此必须要指定删除器。

        std::shared_ptr<Test> ppp1(new Test[5],[](Test* t){
           delete[] t; 
        });//若此时不指定，只会析构一个元素.

        //若面对数组时不想自己写删除器，可以用c++提供的默认数组删除器函数

        std::shared_ptr<Test>(new Test[5], std::default_delete<Test[]>());

    return 0;
}