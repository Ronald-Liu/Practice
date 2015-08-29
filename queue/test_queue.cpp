
#include <iostream>
#include <unistd.h>
using namespace std;
#include "queue_cond.hpp"

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

queue_cond<myClass> q(2);
void* producer(void* arg){
    while(1){
        sleep(1);
        myClass a(rand());
        q.push(std::move(a));
    }
}

void* customer(void* arg){
    while(1){
        myClass t;
        q.popTo(t);
        cout << t.getValue() << endl;
    }
}

int main(){
    pthread_t plist[18];
    for (int i = 0; i < 3; i++){
        pthread_create(plist+i, nullptr, producer, nullptr);        
    }

    sleep(10);
    for (int i = 0; i < 15; i++){
        pthread_create(plist+i+3, nullptr, customer, nullptr);
    }
    for (int i = 0; i < 18 ;i++)
        pthread_join(plist[i], nullptr);
    return 0;
}
