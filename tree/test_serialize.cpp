#include "tree.hpp"
#include "serialize.hpp"
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

int main(){
    srand(time(nullptr));

    auto t =  GenRandomTree(100);
    auto t2 = DFSReconstructTree(DFSSerializeTree(t));
    
    assert(*t2 == *t);
    return 0;
}
