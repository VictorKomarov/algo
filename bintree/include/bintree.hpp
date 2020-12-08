#pragma once
#include <memory>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
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
    size_t height = 0;  // count node to root
    std::shared_ptr<Node<T>> parent;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;

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

    std::shared_ptr<Node<T>>& prev_node()
    { // case when no childs
        auto& last_leaf = [](auto& self, std::shared_ptr<Node<T>>& n) -> std::shared_ptr<Node<T>>& {
            if (n->right) return n;
            return self(self, n->right);
        }(last_leaf, left);

        return last_leaf;
    }

    void parent_to_child(std::shared_ptr<Node<T>>& child)
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

    static std::string pretty(std::shared_ptr<Node<T>>& n)
    {
        if (!n) {
            return "empty";
        }

        std::stringstream str;
        str << n->val << "(" << n->key << ")";
        return str.str();
    }
};


template <typename T>
class BinTree {
private:
    using node = std::shared_ptr<Node<T>>;
    node root = nullptr;
    size_t max_height = 0;  // for print target
    std::vector<std::vector<std::string>> print_tree_helper(node& left, node& right)
    {
        std::vector<std::vector<std::string>> nodes = {{Node<T>::pretty(left), Node<T>::pretty(right)}};
        
        std::vector<std::vector<std::string>> left_childs;
        if (left) {
            left_childs = print_tree_helper(left->left, left->right);
        }

        std::vector<std::vector<std::string>> right_childs;
        if (right) {
            right_childs = print_tree_helper(right->left, right->right);
        }

        size_t l = 0, r = 0;
        while (l < left_childs.size() || r < right_childs.size())
        {
            std::vector<std::string> temps;
            if (l < left_childs.size()) temps.insert(temps.end(), left_childs[l].begin(),left_childs[l].end());
            if (r < right_childs.size()) temps.insert(temps.end(),right_childs[r].begin(),right_childs[r].end());
            nodes.push_back(temps);

            ++l, ++r;
        }
        
        return nodes;
    }

    node search_helper(node& n, size_t key)
    {
        if (!n) return nullptr;
        if (n->key == key) return n;
        
        return (n->key > key) ? search_helper(n->left, key) : search_helper(n->right, key); 
    }

    size_t insert_helper(size_t key, T val, node& n)
    {
        if (n->key > key) {
            if (!n->left) {
                n->left.reset(new Node<T>{val, key, n->height+1, n});
                return n->height+1;
            }

            return insert_helper(key,val,n->left);
        }

        if (!n->right) {
            n->right.reset(new Node<T>{val, key,n->height+1,n});
            return n->height+1;
        }

        return insert_helper(key, val,n->right);
    }

    void remove_helper(size_t key)
    {
        auto& removed = search_helper(root, key);
        if (!removed) return;

        switch (count_child(removed))
        {
        case CHILD_ZERO:
            if (removed != root) {
                removed->parent.remove_child(key);
            }
            break;
        case CHILD_ONE:
            auto& child = (removed->left) ? removed->left : removed->right;
            if (removed == root) {
                root.reset(child.realese());
            } else {
                removed.parent_to_child(child);
            }
            break;
        case CHILD_TWO:
            /*auto& prev = n; // prev always has empty right
            auto& prev_left_child = prev->left;
            auto& removed_right = n->right;

            if (removed == root) {
                //
            } else {
                removed.parent_to_child(prev);
            }

            break;*/
            break;
        }
        removed.reset();
    }
public:
    void print_tree()
    {
        std::cout << Node<T>::pretty(root) << '\n';
        auto nodes = print_tree_helper(root->left, root->right);
        for(size_t i = 0; i < nodes.size(); ++i)
        {
            for(auto it = nodes[i].begin(); it != nodes[i].end(); ++it) std::cout << *it << " ";
            std::cout << std::endl;
        }
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

        auto height = insert_helper(key, val, root);
        if (height > max_height) max_height = height;
    }

    void remove(size_t key)
    {
        remove_helper(key);
    }
};