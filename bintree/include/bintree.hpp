#pragma once
#include <memory>
#include <iostream>

template <typename T>
struct Node
{
    T val;
    size_t key;
    std::unique_ptr<Node<T>> parent;
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

    node& search_helper(node& n, size_t key)
    {
        if (n == nullptr) return nullptr;
        if (n->key == key) return n;
        
        return (n->key > key) ? search_helper(n->left, key) : search_helper(n->right, key); 
    }

    void insert_helper(size_t key, T val, node& n)
    {
        if (n->key > key) {
            if (n->left == nullptr) {
                node insterted = new Node<T>{val, key, n}; 
                n->left.reset(insterted);
                return;
            }

            insert_helper(key,val,n->left);
        } else {
            if (n->right == nullptr) {
                node insterted = new Node<T>{val, key, n}; 
                n->right.reset(insterted);
                return;
            }

            insert_helper(key, val,n->right);
        }
    }
    size_t count_child(node& n)
    {
        if (n->left || n->right) {
            return (n->left && n->right) ? 2 : 1;
        }
        return 0;
    }
    void delete_child(node& n, size_t key_child)
    {
        if (n) {
            if (n->left && n->left->key == key_child) {
                n->left = nullptr;
            } else (n->right && n->right->key == key_child) {
                n->right = nullptr;
            }
        }
    }
    node& next_elem(node& n)
    {
        if (n->right) {
            // rec for limit left
        }
    }
    void remove_helper(size_t key)
    {
        auto n = search_helper(root, key);
        if (n == nullptr) return;

        switch (count_child(n))
        {
        case 0:
            delete_child(n->parent, key);
            n.reset(nullptr); // TODO::does it delete node?
            break;
        case 1:
            node& child = (n->left) ? n->left : n->right;
            if (n->parent)  { 
               if (n->parent->left && n->parent->left->key == key) {
                   n->parent->left = child;
               }  else {
                   n->parent->right = child;
               } 
            } else { // n - is root
                root = child;
            }
            n.reset(nullptr);   
            break;
        case 2:

            break;
        }
    }
public:
    void print_tree()
    {
        print_tree_helper(root);
    };

    bool search(size_t key)
    {
        auto n = search_helper(root, key);
        return n != nullptr;
    }

    void insert(size_t key, T val)
    {
        if (root == nullptr) {
            root.reset(new Node<T>{val, key});
            return;
        }

        insert_helper(key, val, root);
    }

    void remove(size_t key)
    {
        remove_helper(key);
    }
};