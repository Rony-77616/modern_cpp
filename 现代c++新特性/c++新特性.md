# 一.auto

## 1.什么是auto？
- auto是c++的“自动类型推导”。我们写的初始化表达式，编译器根据右边的值推导左边类型的变量类型。


## 2.auto的编译规则
- auto不是动态类型，他的类型在编译期已经确定。
- auto会去掉引用和顶层const
```cpp
int x = 10;;
int& ref = x;
const int y = 20;

auto a = x; //auto推导为int
auto b = ref;  //auto推导为int
auto c = y;  //auto推导为int

//若想保留引用，要明确写&
auto& d= x; //推导为int&
const auto& e = y; //const int&
```
- auto必须立刻初始化，因为编译器需要右边来推导类型
  




# 二.range-based for

## 什么是range-based for
- range-based for是c++给我们提供的一个语法糖，在编译期会展开成一个基于迭代器的for循环，用于遍历容器、数组等可迭代对象，比手动使用下标或迭代器更简洁。
  
## 具体格式
for(元素类型 变量 ：容器名);
```cpp
 std::vector<char> v = {'a','b','c'};
    for(const auto& a : v){
        std::cout<<a<<" ";
    }
```

## 是否复制 能修改
- 由变量的写法来决定，若写成const auto& a ：
  就代表只读不复制，若直接写成auto a，就复制可以改。若不写&，就代表复制。


## 遍历键值对时
遍历map,c++可用结构化绑定：
```cpp
std::map<std::string, int> scores = {
    {"Tom", 90},
    {"Amy", 95}
};

for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << '\n';
}//其中name是键，score是值。
```




# 三.lambda

## 1.什么是lambda表达式
 - lambda表达式是一种匿名函数，通常用于临时、简短的函数逻辑

## 2.基本语法
```cpp
    [//捕获] ( /*参数列表*/ ) -> int /*返回值类型，可省略*/ {
        //语句
    }
```
- []捕获列表
- （int a）参数列表
-  -> int 返回值类型，可省略
-  {} 函数体
  
## 3.捕获列表
 lambda表达式的捕获列表位于最前方的[]中，用来指定如何使用外部变量。
 常见形式：
 - [] 不捕获任何外部变量
 - [ x ] 按值捕获x
 - [&x] 按引用捕获x
 - [=] 按值捕获所有用到的外部变量
 - [&] 按引用捕获所有用到的外部变量
 - [=,&x] 默认按值，但x按引用捕获
 - [&,x] 默认引用，但x按值捕获  

 捕捉的变量，会成为lambda内部可使用的数据，可用于读取变量值、参与计算、条件判断、调用其他函数、作为返回值的一部分等等。而[]内捕获的变量和参数列表内的参数的区别在于来源和和生命周期：

 |区别项目|捕获列表| 参数列表|
 |:---|:---|:---|
 |数据来源|lambda外部作用域|调用lambda时传入|
 |设置时间|创建lambda时|每次调用时|
 |是否每次不同|通常固定，除非按引用|每次可传入不同值|
 |作用|保存外部环境中的变量|接收调用者提供的数据|

## 4.实际应用
1. sort自定义排序：升序return a>b；降序return a<b；
2. findif：查找满足条件的元素
3. countif：统计满足条件的元素
4. foreach：遍历元素等等


## 5.返回类型
大多数情况下编译器可以能自动推断，可以不写，需要时可以显示写，但是如果返回有多个分支，每个分支的return类型需要一致。

auto和std::function都可以保存lambda，但作用不同：

- lambda本质上是一个函数对象，这个函数对象的真实类型很特殊，编译器自动生成，名字很长无法手写，所以用auto让编译器自动推断类型。
  ```cpp
  auto add = [](int x,int y){
    return x+y;
  };
  std::cout<<add(2,3);
  ```
  也就是auto add = 某个编译器生成的类型；

- std::function是一个通用的函数容器，只要函数签名一致，就能保存不同的lambda。
```cpp
#include<function>
std::function<int(int,int)> operation;
//operation可以保存不同的lambda，但是参数列表必须都是两个int，并且返回int。
operation = [](int a,int b){
    return a+b;
};

std::cout<<operation(2,3);//输出5

operation = [](int a,int b){
    return a*b;
}
std::cout<<operation(2,3)//输出6;
```

对比：
auto的类型就是这个具体的lambda的类型，之后不能给他另外的lambda。
而function保存的是接口，只要新函数符合function规定的参数和返回值类型，就可以替换





# 四.constexpr
constexpr的核心作用是，把能提前计算确定的计算放到编译阶段完成，要求编译器检查某个值是否能在编译期确定，并允许他在编译期计算。


## 1. constexpr变量
```cpp
    constexpr int max = 100;
    constexpr double pi = 3.1415926;
```
要求：
- 初始化后不能修改
- 初始化值必须能在编译期确定 
  
例如数组大小、模板参数等场景需要编译期常量


## 2.constexpr函数
```cpp
constexpr int square(int x){
    return x*x;
} //他表示这个函数在条件满足时，可以在编译期执行
//例如：
constexpr int a = square(5); //编译期计算，a = 25

//也可以正常初始运行时数据，例如：
int n;
std::cin>>n;
int b = square(n); //由于n需要在运行期由用户手动输入，所以在运行期计算
```

所以constexpr函数不是只能在编译期调用，而是根据传入的数据是编译期常量还是运行时数据来决定。


## 3.constexpr和const的区别
- const的重点是：不能修改值。
- constexpr的重点是：不能修改值，并且初始化时必须是编译期常量表达式。



