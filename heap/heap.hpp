#ifndef __HEAP_H_
#define __HEAP_H_

#include <cstdint>


template <typename T, bool (*smaller)(T&, T&)>
class heap{
    T *buffer;
    size_t size;
    size_t capacity;

    T& getElement(size_t i){
        return *(buffer+i);
    }
    
    void fixDown(size_t i){
        while(i*2+1 < size){
            int j = i*2+1;
            if (j+1 <size && smaller(getElement(j+1), getElement(j))){
                j++;
            }
            if (!smaller(getElement(i), getElement(j))){
                std::swap(getElement(i), getElement(j));
                i = j;
            }
            else
                break;
        }
    }

    void pushUp(size_t i){
        while(i > 0){
            int j = (i-1)/2;
            if (smaller(getElement(i), getElement(j)))
                {
                    std::swap(getElement(i), getElement(j));
                    i = j;
                }
            else
                break;
        }
    }
    
    void resize(size_t s){
        T* tmp = static_cast<T*> (realloc(buffer, s*sizeof(T)));
        if (buffer == tmp)
            return;

        for (int i = 0; i < size; i++){
            new (tmp+i) T(getElement(i));
            getElement(i).T::~T();
        }
        free(buffer);
        buffer = tmp;
        capacity = s;
    }
    
public:
    heap():capacity(10){
        buffer = static_cast<T*>(malloc(capacity*sizeof(T)));
        size = 0;
    }
    void push(T&& c){
        if (size>capacity)
            resize(capacity*2);
        getElement(size) = std::move(c);
        size++;
        pushUp(size-1);
    }
    
    T&& pop(){
        
    }
    void popTo(T& c){
        c = std::move(getElement(0));
        std::swap(getElement(0), getElement(size-1));
        getElement(size-1).T::~T();
        size--;
        fixDown(0);
    }
};

#endif
