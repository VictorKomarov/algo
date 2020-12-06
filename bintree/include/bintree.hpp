#pragma once
#include <memory>
#include <iostream>
#include <functional>

enum Child {
    CHILD_ZERO,
    CHILD_ONE,
    CHILD_TWO,
};

enum ChildDir {
    ROOT,
    CHILD_LEFT,
    CHILD_RIGHT,
};

template <typename T>
struct Node
{
    T val;
    size_t key;
    std::unique_ptr<Node<T>> parent;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    void remove_child(size_t key_child)
    {
       if (left && left->key == key_child) {
            left.reset();
        } else if (right && right->key == key_child) {
            right.reset();
        }
    }

    ChildDir my_dir()
    {
        if (!parent) ROOT;

        if (parent->left && parent->left->key == key) {
            return CHILD_LEFT;
        } else {
            return CHILD_RIGHT;
        }
    }

    std::unique_ptr<Node<T>>& prev_node()
    { // case when no childs
        auto& last_leaf = [](auto& self, std::unique_ptr<Node<T>>& n) -> std::unique_ptr<Node<T>>& {
            if (n->right) return n;
            return self(self, n->right);
        }(last_leaf, left);

        return last_leaf;
    }

    void parent_to_child(std::unique_ptr<Node<T>>& child)
    {
        switch (my_dir())
        {
        case ROOT:
            return;
        case CHILD_LEFT:
            parent->left->reset(child.realese());
            break;
        case CHILD_RIGHT:
            parent->right->reset(child.realese());
            break;
        }
    }

    Child count_childs()
    {
        if (left || right) {
            return (left && right) ? CHILD_TWO : CHILD_ONE;
        }
        return CHILD_ZERO;
    }
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
        if (!n) return nullptr;
        if (n->key == key) return n;
        
        return (n->key > key) ? search_helper(n->left, key) : search_helper(n->right, key); 
    }

    void insert_helper(size_t key, T val, node& n)
    {
        if (n->key > key) {
            if (!n->left) {
                n->left.reset(new Node<T>{val, key, n});
                return;
            }

            insert_helper(key,val,n->left);
        } else {
            if (!n->right) {
                n->right.reset(new Node<T>{val, key, n});
                return;
            }

            insert_helper(key, val,n->right);
        }
    }

    void remove_helper(size_t key)
    {
        auto& n = search_helper(root, key);
        if (!n) return;

        switch (count_child(n))
        {
        case CHILD_ZERO:
            if (n != root) {
                n->parent.remove_child(key);
            }
            break;
        case CHILD_ONE:
            auto& child = (n->left) ? n->left : n->right;
            if (n == root) {
                root.reset(child.realese());
            } else {
                n.parent_to_child(child);
            }
            break;
        case CHILD_TWO:
            // implement
            break;
        }
        n.reset();
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
        if (!root) {
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