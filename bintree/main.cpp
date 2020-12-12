#include "include/bintree.hpp"
#include <iostream>
#include <iomanip>
#include <memory>

int main()
{
  BinTree<int> b;
  b.insert(8,8);
  b.insert(6,6);
  b.insert(7,7);
  b.insert(3,3);
  b.insert(4,4);
  b.insert(2,2);
  b.insert(9,9);
  b.print_tree();
  b.remove(6);
  b.print_tree();
}