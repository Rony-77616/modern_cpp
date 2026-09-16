#include<iostream>
#include<memory>


class node{
public:

    std::shared_ptr<node> next;
    std::weak_ptr<node> pre;

    node(){
        std::cout<<"constructing node!"<<std::endl;
    }

    node(int x) : data(x){
        std::cout<<"data = "<<x<<std::endl;
    }

    ~node(){
        std::cout<<"distructing node!"<<std::endl;
        next.reset();
        pre.reset();
    }

        int print_num(){
            return data;
        }


private:
int data;
};

class doublelist : public std::enable_shared_from_this<doublelist>{
public:
    std::shared_ptr<node> head;

    void push_back(int x){
        std::shared_ptr<node> newnode = std::make_shared<node> (x);
        if(!head){
            std::cout<<"head_node is empty! use this as a head_node!(push_back) "<<std::endl;
            head = newnode;
        }
        else{
            std::shared_ptr<node> cur = head;
            while(cur->next){
                cur = cur->next;
            }
            cur->next = newnode;
            newnode->pre = cur;
            std::cout<<"push_back node completed! The node in the back is : "<<x<<std::endl;
    }
}

    void push_forward(int x){
        std::shared_ptr<node> newnode = std::make_shared<node>(x);
            if(!head){
                head = newnode;
                std::cout<<"head_node is empty! use this as a head_node(push_forward)"<<std::endl;
            }
            else{
                newnode->next = head->next;
                newnode->next->pre = newnode;
                newnode->pre = head;
                head->next = newnode;
                std::cout<<"push_forward node is completed! The node in the forward is : "<<x<<std::endl;
            }
        }

    void delete_list(){
        head.reset();
        std::cout<<"list is distracted!"<<std::endl;
    }


    void traverse(std::shared_ptr<node> head){
        if(!head){
            std::cout<<"list is distracted already!"<<std::endl;
        }
        if(!head->next){
            std::cout<<"only has head_node!(traverse)"<<std::endl;
            return ;
        }
        else if(head->next){
            std::shared_ptr<node>cur = head->next;
            while(cur){
                std::cout<<cur->print_num()<<" "<<"->"<<" ";
                cur= cur->next;
            }
            std::cout<<std::endl;
        }
    }


    void pre_traverse(std::shared_ptr<node> head){
        if(!head){
            std::cout<<"list is distracted already!"<<std::endl;
        }
        if(!head->next){
            std::cout<<"only has head_node !(pre_traverse)"<<std::endl;
            return ;
        }
        else if(head->next){
            std::shared_ptr<node> cur = head->next;
            while(cur->next){
                cur = cur->next;
            }
            while(cur->pre.lock()){
                std::cout<<cur->print_num()<<" "<<"->"<<" ";
                cur = cur->pre.lock();
            }
            std::cout<<std::endl;
        }
    }
};


int main(){

    doublelist list;
    list.push_back(100);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_forward(0);
    list.push_forward(-1);
    list.traverse(list.head);
    list.delete_list();
    list.pre_traverse(list.head);
    return 0;
}



