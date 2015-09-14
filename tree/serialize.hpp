#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_
#include <string>
#include <sstream>
#include "tree.hpp"

template<class T>
std::string DFSSerializeTree(TreeNode<T>* node){
    std::stringstream ss;
    ss << node->value << ',';
    if (node->left)
        ss << DFSSerializeTree(node->left);
    else
        ss << '#';
    ss << ',';
    if (node->right)
        ss <<DFSSerializeTree(node->right);
    else
        ss << '#';
    return ss.str();
}

TreeNode<int>* DFSReconstructTree(std::stringstream &ss){
    if (ss.eof())
        return nullptr;
    std::string buf;
    std::getline(ss, buf, ',');
    if (buf[0] == '#')
        return nullptr;
    auto *node = new TreeNode<int>(std::stoi(buf));
    node->left = DFSReconstructTree(ss);
    node->right = DFSReconstructTree(ss);
    return node;
}

TreeNode<int>* DFSReconstructTree(const std::string &s){
    std::stringstream ss(s);
    return DFSReconstructTree(ss);
}

#endif
