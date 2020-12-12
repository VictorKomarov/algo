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

    std::shared_ptr<Node<T>> prev_node()
    { // case when no childs
        auto last_leaf = [](auto& self, std::shared_ptr<Node<T>>& n) -> std::shared_ptr<Node<T>> {
            if (!n->right) return n;
            return self(self, n->right);
        };

        return last_leaf(last_leaf, left);
    }

    void parent_to(std::shared_ptr<Node<T>>& node)
    {
        switch (my_dir())
        {
        case ROOT:
            return;
        case CHILD_LEFT:
            node->parent = parent;
            parent->left = node;
            break;
        case CHILD_RIGHT:
            node->parent = parent;
            parent->right = node;
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

    std::string pretty()
    {
        std::stringstream str;
        str << val;
        return str.str();
    }
};


template <typename T>
class BinTree {
private:
    using node = std::shared_ptr<Node<T>>;
    node root = nullptr;
    size_t max_height = 0;  // for print target
    std::vector<std::vector<std::string>> nodes_by_level(node& n)
    {
        std::vector<std::vector<std::string>> nodes = {{n->pretty()}};

        std::vector<std::vector<std::string>> left_childs;
        if(n->left) {
            left_childs = nodes_by_level(n->left);
        } else {
            left_childs.push_back({"X"});
        }

        std::vector<std::vector<std::string>> right_childs;
        if(n->right) {
            right_childs = nodes_by_level(n->right);
        } else {
            right_childs.push_back({"X"});
        }

        auto max = (left_childs.size() > right_childs.size()) ? left_childs.size() : right_childs.size();
        for(size_t i = 0; i < max; ++i)
        {
            std::vector<std::string> temp;
            if(i  >= left_childs.size()) {
                auto sz = right_childs[i].size();
                left_childs.push_back(std::vector<std::string>(sz, "X"));
            }

            if (i >= right_childs.size()) {
                auto sz = left_childs[i].size();
                right_childs.push_back(std::vector<std::string>(sz, "X"));
            }

            temp.insert(temp.end(), left_childs[i].begin(),left_childs[i].end());
            temp.insert(temp.end(), right_childs[i].begin(),right_childs[i].end());
            nodes.push_back(temp);
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
        auto removed = search_helper(root, key);
        if (!removed) return;

        switch (removed->count_childs())
        {
        case CHILD_ZERO:
            if (root == removed) {
                root.reset();
            } else {
                removed->parent->remove_child(key);
            }
            break;
        case CHILD_ONE:
            if(root == removed) {
                root = (removed->left) ? removed->left : removed->right; 
            } else {
                auto child = (removed->left) ? removed->left : removed->right;
                removed->parent_to(child);
            }
            break;
        case CHILD_TWO:
            auto prev = removed->prev_node(); //always have empty right;
            
            if (prev->parent->left != prev) {
                if(!prev->left) {
                    prev->left = removed->left;
                    removed->left->parent = prev; 
                }
            }
        

            prev->right = removed->right;
            removed->right->parent = prev;
            removed->parent_to(prev);
            break;
        }

        std::cout << "Before reset " << removed.use_count() << std::endl;
        removed.reset();
    }
public:
    void print_tree()
    {
        if (!root) {
            std::cout << "Empty" << std::endl;
            return;
        }

        auto nodes = nodes_by_level(root);
        auto max_size = nodes[nodes.size()-2].size() * 2; // refact this
        size_t offset = 0;
        for(size_t i = 0; i < nodes.size()-1; ++i)
        {
            auto counts = nodes[i].size();
            auto before_nodes = (max_size-counts-(counts-1)*offset) / 2;
            std::cout << '|' << std::setfill('_') <<  std::setw(before_nodes+1);
            for(size_t j = 0; j < nodes[i].size(); ++j)
            {
                std::cout << nodes[i][j];
                if (j != nodes[i].size()-1){
                    std::cout << std::setfill('_') << std::setw(offset+1);
                } else {
                    std::cout << std::setfill('_') << std::setw(before_nodes+1) << '|' << std::endl;
                }
            }
            offset = before_nodes;
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