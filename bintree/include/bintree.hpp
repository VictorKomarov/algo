#pragma once
#include <memory>
#include <iostream>

template <typename T>
struct Node
{
    T val;
    size_t key;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;
};


template <typename T>
class BinTree {
private:
    using node = std::unique_ptr<Node<T>>;
    node root = nullptr;
    void print_tree_helper(node& n, size_t pos = 20)
    {
        // need to implement -> need to know the height
    }

    bool search_helper(node& n, size_t key)
    {
        if (n == nullptr) return false;
        if (n->key == key) return true;
        
        return (n->key > key) ? search_helper(n->left, key) : search_helper(n->right, key); 
    }

    void insert_helper(size_t key, T val, node& n)
    {
        if (n->key > key && n->left == nullptr) {
            n->left.reset(new Node<T>{val, key});
        } else if (n->key < key && n->right == nullptr) {
            n->right.reset(new Node<T>{val, key});
        } else if (n->key > key) {
            insert_helper(key,val,n->left);
        } else {
            insert_helper(key, val,n->right);
        }
    }
public:
    void print_tree()
    {
        print_tree_helper(root);
    };

    bool search(size_t key)
    {
        return search_helper(root, key);
    }

    void insert(size_t key, T val)
    {
        if (root == nullptr) {
            root.reset(new Node<T>{val, key});
            return;
        }

        insert_helper(key, val, root);
    }
};