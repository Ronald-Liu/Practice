#ifndef __MD_MATRIX_H_
#define __MD_MATRIX_H_

#include <initializer_list>
#include <utility>
#include <cstdlib>
#include <stdexcept>

template<class T, unsigned int d>
class MDMatrix{
    typedef MDMatrix<T, d-1> LessDim;
    LessDim* nM;
    int n;
public:
    MDMatrix(std::initializer_list<LessDim> il):nM(nullptr){
        n = il.size();
        nM = static_cast<LessDim*>(malloc(il.size()*sizeof(LessDim)));
        int cnt = 0;
        for (auto& i: il){
            new (nM+(cnt++)) LessDim(i);
        }
    }

    MDMatrix(MDMatrix&& other){
        nM = other.nM;
        n = other.n;
        other.nM = nullptr;
    }

    MDMatrix(const MDMatrix& other){
        n = other.n;
        nM = static_cast<LessDim*>(malloc(n*sizeof(LessDim)));
        for (int i = 0; i < n; i++){
            new (nM+i) LessDim(other.nM[i]);
        }
    }
    
    ~MDMatrix(){
        if (nM){
            //for (int i = 0; i < n; i++)
            //    (nM+i)->MDMatrix<T, d-1>::~MDMatrix();
            
            free(nM);
        }
    }

    MDMatrix& operator=(MDMatrix&& other){
        std::swap(other.nM, nM);
    }
    
    int size() const{
        return n;
    }

    LessDim& operator[](int p){
        if (p >= n)
            throw std::out_of_range("Out of range");
        return (nM[p]);
    }
};

template<class T>
class MDMatrix<T, 0>{
    T value;
public:
    MDMatrix(T a):value(a){}

    ~MDMatrix(){}

    size_t size() const{
        return 1;
    }

    T& operator[](int n){
        if (n == 0)
            return value;
        throw std::out_of_range("Out of range");
    }
};
#include <iostream>
template<class T, unsigned int d>
void printMatrix(MDMatrix<T, d>& matrix){
    for (int i = 0; i < matrix.size(); i++){
        printMatrix(matrix[i]);
        std::cout << ' ';
    }
    std::cout << std::endl;
}

template<class T>
void printMatrix(MDMatrix<T, 0>& matrix){
    std::cout << matrix[0];
}

#endif
