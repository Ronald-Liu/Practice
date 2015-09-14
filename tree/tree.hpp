#ifndef __TREE_HPP_
#define __TREE_HPP_
template<class T>
class TreeNode{
public:
    TreeNode(T t):value(t), left(nullptr), right(nullptr){}
    T value;
    TreeNode *left, *right;

    bool operator==(const TreeNode& t){
        if (value != t.value)
            return false;
        if (t.left == nullptr || left== nullptr){
            if (!(t.left == left))
                return false;
        }
        else{
            if(!(*(t.left)== *left))
                return false;
        }
        
        if (t.right == nullptr || right == nullptr){
            if (!(t.right == right))
                return false;
        }
        else{
            if(!(*(t.right)== *right))
                return false;
        }
        
        return true;
    }

    ~TreeNode(){
        if (left)
            delete left;
        if (right)
            delete right;
    }
};


#include <cstdlib>

TreeNode<int>* GenRandomTree(int n){
    if (n == 0)
        return nullptr;
    auto node = new TreeNode<int>(rand());
    auto leftNum = rand()%(n);
    node->left = GenRandomTree(leftNum);
    node->right = GenRandomTree(n-leftNum-1);

    return node;
}

#endif
