//Main.cc

#include <iostream>
#include <utility>
#include <string>
#include <stdlib.h>
#include <chrono> //--> per random
#include "../include/BST.h"

int main(){

  srand (time(NULL));

  BST<int, int> bst_int;
  int i = 0; bool add=false;
  while(i<NUM){
    add = bst_int.add(rand(), rand());
    if(add) i++;
  }

  long int search_key = rand();

  auto start1 = std::chrono::steady_clock::now();
  bst_int.find(search_key);
  auto end1 = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff1 = end1-start1;
  std::cout<<"notb "<<diff1.count()<<" "<<NUM<<std::endl;


  bst_int.balance();

  auto start = std::chrono::steady_clock::now();
  bst_int.find(search_key);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end-start;
  std::cout<<"b "<<diff.count()<<" "<<NUM<<std::endl;

}
