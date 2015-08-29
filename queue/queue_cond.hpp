#ifndef __QUEUE_H_
#define __QUEUE_H_
#include <pthread.h>
#include <cstdint>
#include <cstdlib>

#include <utility>
template <typename T>
class queue_cond{
    void *buffer;
    size_t maxSize;
    size_t head, len;
    pthread_cond_t cond_is_not_empty;
    pthread_cond_t cond_is_not_full;
    pthread_mutex_t mutex;
public:
    queue_cond(size_t MaxSize): maxSize(MaxSize), head(0), len(0){
        buffer = malloc(maxSize * sizeof(T));
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&cond_is_not_empty, nullptr);
        pthread_cond_init(&cond_is_not_full, nullptr);
    }
    
    ~queue_cond(){
        
    }

    bool isFull(){
        return len == maxSize;
    }
    
    bool isEmpty(){
        return len == 0;
    }
    
    void push(T&& _ele){
        pthread_mutex_lock(&mutex);
        while (isFull())
             pthread_cond_wait(&cond_is_not_full, &mutex);

        new (static_cast<T*>(buffer)+(head+len)%maxSize) T(std::move(_ele));
        len++;
        pthread_cond_signal(&cond_is_not_empty);
        pthread_mutex_unlock(&mutex);
    }

    T&& pop(){
        
        pthread_mutex_lock(&mutex);
        while (isEmpty())
            pthread_cond_wait(&cond_is_not_empty, &mutex);
        T tmp = std::move(*(static_cast<T*>(buffer)+head));
        (static_cast<T*>(buffer) + head)->T::~T();
        head = (head+1) % maxSize;
        len--;
        pthread_cond_signal(&cond_is_not_full);
        pthread_mutex_unlock(&mutex);
        return std::move(tmp);
    }

    void popTo(T& v){
        pthread_mutex_lock(&mutex);
        while (isEmpty())
            pthread_cond_wait(&cond_is_not_empty, &mutex);

        v = std::move(*(static_cast<T*>(buffer)+head));
        (static_cast<T*>(buffer) + head)->T::~T();
        head = (head+1) % maxSize;
        len--;
        pthread_cond_signal(&cond_is_not_full);
        pthread_mutex_unlock(&mutex);
    }
};

#endif
