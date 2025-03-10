#include <iostream>

using namespace std;


template<typename T>
class list_node{
protected:
    T value;
    list_node* anc;
    list_node* nex;
public:
    list_node(){
        value = 0;
        anc = nullptr;
        nex = nullptr;
    }

    T getvalue(){return value;}
    list_node* getnext(){return nex;}

    bool operator<<(T a){
        if (value == 0){
            value = a;
            return 1;
        }
        list_node* tmp = this;
        while(tmp->nex != nullptr) tmp = tmp->nex;
        tmp->nex = new list_node();
        tmp->nex->anc = tmp;
        tmp->nex->value = a;
        return 1;
    }

    bool operator>>(T& a){
        a = this->pop(this->size()-1);
        return 1;
    }

    T& operator[](int n){
        list_node* tmp = this;
        for(int i = 0; i < n; i++){
            if(tmp->nex != nullptr) tmp = tmp->nex;
        }
        return tmp->value;
    }

    T pop(int n){
        if(n == 0){
            if(nex == nullptr){
                if(value == 0) return 0;
                int a = value;
                value = 0;
                return a;
            }
            value = nex->value;
            list_node*tmp = nex;
            nex = nex->nex;
            if(nex!=nullptr) nex->anc = this;
            T a = tmp->value;
            delete tmp;
            return a;

        }
        list_node* tmp = this;
        for(int i = 0; i < n; i++){
            if(tmp->nex == nullptr) return 0;
            tmp = tmp->nex;
        }
        tmp->anc->nex = tmp->nex;
        if (tmp->nex != nullptr) tmp->nex->anc = tmp->anc;
        T a = tmp->value;
        delete tmp;
        return a;
    }
    void push(const T a, int n){
        list_node* tmp = this;
        for(int i = 0; i < n-1; i++){
            if(tmp->nex!=nullptr) tmp=tmp->nex;
        }
        list_node* old_nex = tmp->nex;
        tmp->nex = new list_node();
        tmp->nex->anc = tmp;
        tmp->nex->value = a;
        tmp->nex->nex = old_nex;
    }

    int size(){
        int c = 1;
        list_node* tmp = this;
        while(tmp->nex != nullptr){
            c++;
            tmp = tmp->nex;
        }
        return c;
    }

};
template<typename T>
std::ostream& operator<<(std::ostream& os, list_node<T>& ls){
    list_node<T>* tmp = &ls;
    while(tmp->getnext() != nullptr){
        os << tmp->getvalue() << ", ";
        tmp = tmp->getnext();
    }
    os << tmp->getvalue() << '\n';
    return os;
}

int main()
{
    list_node<float> ls;
    ls<<1;
    ls<<2.77;
    ls<<3;
    ls<<4;
    ls.push(10.88, 1);
    ls<<5;
    ls[2] = 7;
    float a;
    ls>>a;
    cout << a << endl;
    cout << ls[6];
    return 0;
}
