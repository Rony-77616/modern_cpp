#include<iostream>
#include<memory>
#include<string>

class test : public std::enable_shared_from_this<test>{ //继承一个模板类enable_shared_from_this，把test当作参数传进去
public:
test(){
    std::cout<<" constructing test!"<<std::endl;
}
test(int x):num(x){
    std::cout<<"执行test的int有参构造函数,num = "<<num<<std::endl;
}

test(std::string str){
    std::cout<<"执行test的str有参构造函数,str = "<<str<<std::endl;
}

~test(){
    std::cout<<"destructing test!"<<std::endl;
}

    void print(){
        std::cout<<"num = "<<num<<std::endl;
    }

    void setnum(int x){
        num = x;
    }


/*    std::shared_ptr<test> get_shared_ptr(){
        return std::shared_ptr<test>(this);
    }                  错误的函数写法
*/   
std::shared_ptr<test> get_shared_ptr(){ //继承了一个模板类，把当前类test传进去后，调用内部函数shared_from_this();返回的sharedptr内部用一个weakptr来监测该对象，
                                        //并且升级一个sharedptr返回，usecount+1，不会出现问题。
    return shared_from_this(); 
}

private:
int num;
};


int main(){
    //初始化
    //1.sharedptr初始化weakptr，拷贝构造
    std::shared_ptr<test> sp1(new test);
    std::shared_ptr<test> sp2(new test(1));

    std::weak_ptr<test> wp1 = sp1;
    std::weak_ptr<test> wp2(sp2);

    //weakptr初始化weakptr
    std::weak_ptr<test> wp3 = wp1;
    std::weak_ptr<test> wp4(wp2);

    std::weak_ptr<test> wp5;
    wp5 = sp1;
    wp5 = wp2;//可以二次赋值，覆盖第一次。
    

    wp5.reset();//重置。

    wp5 = move(wp1);//move，wp1失去原本的，wp5得到wp1的。



    //expired返回bool类型，表示这个弱指针指向的内存是否已经被清除。
    if(wp2.expired()){
        std::cout<<"wp2指向的内存已被清除"<<std::endl;
    }
    else{
        std::cout<<"wp2指向的内容未被清除"<<std::endl;
    }



    //usecount返回弱指针指向的内存块的引用计数，但是弱指针本身不增加引用计数。
    std::cout<<"wp2的引用计数："<<wp2.use_count()<<std::endl;




    //lock函数可以将wk指针升级，返回一个指向该块内存的shared指针。若wk指针原本指向的内存块已经被清除，返回的shared指针就是空的。
    std::shared_ptr<test> sp3 = wp2.lock();



    //lock函数返回的内容即sharedptr，和sharedptr以及uniqueptr本身都可以做bool判断,如果没有指向任何内存块，就是false，若有指向，就是true。weakptr本身不能做判断
    if(wp2.lock()){
        std::cout<<"wp2内存未被清除"<<std::endl;
    }




    /*
        管理返回this的shared_ptr
        假如，有一个类，它的内部有一个成员函数的功能是创建并返回一个指向这个类的对象的shared_ptr
        也就是return shared_ptr<test>(this);
        若我们在函数外部以及有了这个类的一个对象，再用这个对象里面的这个函数返回了一个this的shared_ptr来构造了两个shared_ptr，就相当于是两个sharedptr都会析构一次，
        会造成重复析构
        为了解决这个问题，c++11提供了一个模板类std::enable_shared_from_this<T>,将这个类传进去，再使用这个类的函数shared_from_this()，就可以返回一个共享的智能指针对象，
        其内部是用weakptr来监测this对象，并且用lock升级成一个shared_ptr来返回。
        */

//        std::shared_ptr<test> p1(new test);
//       std::shared_ptr<test>p2 = p1->get_shared_ptr();
        
        //报错，这种情况返回this相当于用两个裸指针同时构造了两个指针p1和p2，会造成两次析构。
        std::cout<<"begin p1 part"<<std::endl;
        std::shared_ptr<test> p1(new test);
        std::shared_ptr<test> p2 = p1->get_shared_ptr();
        std::cout<<"p1这块内存的usecount : "<<p2.use_count()<<std::endl;

    return 0;
}