#include <map>
#include <string>
#include <iterator>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iostream>

int main()
{

    /* initialize random seed: */
    srand (time(NULL));
    std::cout<<RAND_MAX<<std::endl;
    std::map<int, int> myMap;
    // Inserting data in std::map
    while( myMap.size()<NUM){
      myMap.insert(std::make_pair(rand(), rand()));
    }

    // Searching element in std::map by key.
    auto start1 = std::chrono::steady_clock::now();
    myMap.find(rand());
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff1 = end1-start1;
    std::cout<<diff1.count()<<" "<<NUM<<std::endl;

    return 0;
}
