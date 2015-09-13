#include "mdmatrix.hpp"

int main(){
    //MDMatrix<int, 0> m(1);
    //MDMatrix<int, 1> c = {1,2,3};
    MDMatrix<int, 2> d  {{1,2,3},{2,3,4}};
    MDMatrix<int, 3> e {{{1,2,3},{1,2,4}}, {{1,2,3}, {1,2,6}}};
    
        printMatrix(e);
    return 0;
}
