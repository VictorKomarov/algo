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

    std::string pretty()
    {
        std::stringstream str;
        if (val < 10) {
            str << 0 << val;
        } else {
            str << val;
        }
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
            left_childs.push_back({"XX"});
        }

        std::vector<std::vector<std::string>> right_childs;
        if(n->right) {
            right_childs = nodes_by_level(n->right);
        } else {
            right_childs.push_back({"XX"});
        }

        auto max = (left_childs.size() > right_childs.size()) ? left_childs.size() : right_childs.size();
        for(size_t i = 0; i < max; ++i)
        {
            std::vector<std::string> temp;
            if(i  >= left_childs.size()) {
                auto sz = right_childs[i].size();
                std::vector<std::string> do_it(sz, "XX");
                left_childs.push_back(do_it);
            }

            if (i >= right_childs.size()) {
                auto sz = left_childs[i].size();
                std::vector<std::string> do_it(sz, "XX");
                right_childs.push_back(do_it);
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
        auto nodes = nodes_by_level(root);
        auto max_size = nodes[nodes.size()-1].size() * 2; // refact this
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