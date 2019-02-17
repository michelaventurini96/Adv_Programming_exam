#include <map>
#include <string>
#include <iterator>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>

int main()
{
    using namespace std::chrono;
    std::vector<int> keys;
    duration<double> sum;

    srand (time(NULL));
    std::map<int, int> myMap;
    while( myMap.size()<NUM){
      myMap.insert(std::make_pair(rand(), rand()));
      keys.push_back(rand());

    }
    int j=0; 
    while (j<keys.size() ) {
      auto start = high_resolution_clock::now();
      myMap.find(keys[j]);
      auto end = high_resolution_clock::now();
      duration<double> diff = duration_cast<duration<double>>(end - start);
      sum += diff;
      j++;
    }
    std::cout<<sum.count()/keys.size()<<" "<<NUM<<std::endl;

    return 0;
}
