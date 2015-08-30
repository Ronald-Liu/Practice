#include <iostream>
#include "heap.hpp"
using namespace std;

class myClass{
    int *v;
public:
    myClass(){v = nullptr;}
    myClass(int value){v = new int; *v = value;}
    myClass(myClass&& c){v = c.v; c.v = nullptr;}
    myClass(myClass& c){v = new int; *v = *(c.v);}
    myClass& operator=(myClass&& c){v = c.v; c.v = nullptr; return *this;}
    int getValue(){return *v;}
    ~myClass(){if (v) delete v;}
};

bool smaller(myClass& a, myClass &b){
    return a.getValue() < b.getValue();
}

heap<myClass, smaller> h;

int main(){
    for (int i = 0; i < 40; i++){
        myClass t(10-i);
        h.push(std::move(t));
    }

    for (int i = 0; i < 10; i++)
        {
            myClass t;
            h.popTo(t);
            cout << t.getValue()  << endl;
        }


    return 0;
}
