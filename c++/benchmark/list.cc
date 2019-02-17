//Main.cc

#include <iostream>
#include <utility>
#include <string>
#include <stdlib.h>
#include <chrono> //--> per random
#include <vector>
#include <algorithm>
#include "../include/BST.h"
int main(){
  using namespace std::chrono;
  duration<double> sum;
  //srand (time(NULL));
  std::vector<int> keys;
  BST<int, int> bst_int;
  int i = 0;

  while(i<NUM){
    bst_int.add(i, 1);
    keys.push_back(i);
    i++;
  }
  std::random_shuffle (keys.begin(), keys.end() );

  //long int search_key = rand();
  int j=0;
  while (j<keys.size() ) {
    auto start1 = high_resolution_clock::now();
    bst_int.find(keys[j]);
    auto end1 = high_resolution_clock::now();
    duration<double> diff1 = duration_cast<duration<double>>(end1 - start1);
    sum += diff1;
    j++;
  }
  std::cout<<"notb "<<sum.count()/keys.size()<<" "<<NUM<<std::endl;

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
  std::cout<<"b "<<sum2.count()/keys.size()<<" "<<NUM<<std::endl;
}
