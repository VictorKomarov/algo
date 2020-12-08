#include "include/bintree.hpp"
#include <iostream>
#include <iomanip>
#include <memory>

int main()
{
  BinTree<int> b;
  b.insert(4,4);
  b.insert(6,6);
  b.insert(2,2);
  b.insert(1,1);
  b.insert(3,3);
  b.insert(8,8);
  b.insert(5,5);
  b.insert(10,10);
  b.print_tree();
}