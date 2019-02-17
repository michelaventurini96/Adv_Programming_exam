#include <iostream>
#include <utility>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include "../include/BST.h"
int main(){
  using namespace std::chrono;
  duration<double> sum;
  srand (time(NULL));
  std::vector<int> keys;
  BST<int, int> bst_int;
  int i = 0; bool add=false;
  while(i<NUM){
    add = bst_int.add(rand(), rand());
    if(add) {
      i++;
      keys.push_back(rand());
    }
  }

  int j=0;
  while (j<keys.size() ) {
    auto start1 = high_resolution_clock::now();
    bst_int.find(keys[j]);
    auto end1 = high_resolution_clock::now();
    duration<double> diff1 = duration_cast<duration<double>>(end1 - start1);
    sum += diff1;
    j++;
  }
  auto timen = sum/keys.size();
  std::cout<<"notb "<<timen.count()<<" "<<NUM<<std::endl;

  bst_int.balance();

  j=0;
  duration<double> sum2;
  while (j<keys.size() ) {
    auto start = high_resolution_clock::now();
    bst_int.find(keys[j]);
    auto end = high_resolution_clock::now();
    duration<double> diff = duration_cast<duration<double>>(end - start);
    sum2 += diff;
    j++;
  }
  auto timeb = sum2/keys.size();
  std::cout<<"b "<<timeb.count()<<" "<<NUM<<std::endl;
}
