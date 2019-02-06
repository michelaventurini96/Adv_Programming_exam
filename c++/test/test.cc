#include "../include/BST.h"

int main() {
  //create a new bst
  BST<int,int> bst_int;
  //add elements
  bst_int.add(5,5);
  bst_int.add(3,9);
  bst_int.add(8,6);
  bst_int.add(7,12);
  bst_int.add(12,5);
  //try to add an existing key
  bst_int.add(12,5);
  //print the bst
  std::cout<< bst_int << std::endl;
  //balance the tree
  bst_int.balance();
  //iterate through the tree with Iterator
  for(auto it=bst_int.begin(); it != bst_int.end(); it++){
    std::cout<<"Key: "<<it->first<<",  Value: "<<it->second<<std::endl;
  }
  //iterate through the tree with ConstIterator
  for(auto cit=bst_int.cbegin(); cit != bst_int.cend(); cit++){
    std::cout<<"Key: "<<cit->first<<",  Value: "<<cit->second<<std::endl;
    //cit->second = 2; //---> try to modify through const iterator
  }
  //operator overloading []
  std::cout << "Look for existing key bst_int[8]= " <<bst_int[8] <<std::endl;
  std::cout << "Look for not existing key bst_int[55]= " << bst_int[55]<<std::endl;
  //find
  std::cout<<"Find() with exisiting key: "<<bst_int.find(55)->second<<std::endl;
  if(bst_int.find(999) != bst_int.end()) std::cout<<"key found."<<std::endl;
  else std::cout<<"Find() with no exisiting key - key not found"<<std::endl;

  BST<int,int> bst_int_copy;
  //copy assignment
  bst_int_copy = bst_int;
  std::cout << "Print the copied tree\n" << bst_int_copy << std::endl;
  bst_int.add(120,30);
  //after adding an element to the first tree the second does not change
  std::cout << "Print the tree" << bst_int << std::endl;
  std::cout << "Print the copied tree" << bst_int_copy << std::endl;

  //copy constructor
  BST<int,int> bst_int_copy_constr = bst_int;
  std::cout << "Print the tree constructed usign copy construct" << bst_int_copy_constr << std::endl;
  bst_int.add(130,20);
  //after adding an element to the first tree the second does not change
  std::cout << "Print the bst" << bst_int << std::endl;
  std::cout << "Print the constructed tree" << bst_int_copy_constr << std::endl;

  //move assignment
  BST<int,int> bst_int_move;
  bst_int_move = std::move(bst_int_copy_constr);
  std::cout << "Print the moved tree" << bst_int_move << std::endl;

  //move constructor
  BST<int,int> bst_int_move_constr = std::move(bst_int_copy);
  std::cout << "Print the moved constructor tree" << bst_int_move << std::endl;

  bst_int.clear();
  std::cout<<bst_int<<std::endl;
  bst_int.clear();

  BST<int,int> bst_prova;
  bst_prova.add(1,2);
  bst_prova.add(3,4);
  auto init = bst_prova.begin();

  std::cout << "init -> " <<(++init)->first <<std::endl;
  std::cout << "init -> " <<(init++)->first <<std::endl;
  try{
    init++;
  }catch(std::out_of_range e){
    std::cout<<"An exception occurred: "<<e.what()<<std::endl;
  }

//---------------------------------BST STRING VALUE---------------------//
  BST<int,std::string> bst_string;
  bst_string.add(3,"hello");
  bst_string.add(4,"everyone");
  bst_string.add(9, "monday");
  bst_string.add(11, "day");
  std::cout <<std::endl;

  std::cout << "Print the tree " << bst_string<<std::endl;
  bst_string.balance();

  std::cout << "Get value given existing [key] " << bst_string[4]<<std::endl;
  std::cout << "Get value given no existing [key] " <<bst_string[55] << std::endl;

  std::cout << "Find the key 9 in the tree ";
  auto value3 = bst_string.find(9);
  if (value3!=bst_string.end()) std::cout << value3->first << " "<<value3->second <<std::endl;
  else std::cout << "The key is not in the tree " << std::endl;

  std::cout << "Find the key 8 in the tree ";
  auto value4 = bst_string.find(8);
  if (value4!=bst_string.end()) std::cout << "("<<value4->first << ":"<<value4->second << ")"<<std::endl;
  else std::cout << "The key is not in the tree " << std::endl;

  std::cout << "Print the tree using Iterators " << '\n';
  for(auto i=bst_string.begin(); i!=bst_string.end(); i++){
    std::cout <<"("<<i->first <<":" <<i->second << ") ";
  }
  bst_string.clear();


  BST<std::string,std::string> bst_string1;
  bst_string1.add("hi","hello");
  bst_string1.add("everybody","everyone");
  bst_string1.add("sunday", "monday");
  bst_string1.add("night", "day");

  std::cout << "Print the tree " << bst_string1<<std::endl;
  bst_string1.balance();

  std::cout << "Get value given existing [key] " << bst_string1["everybody"]<<std::endl;
  std::cout << "Get value given no existing [key] " <<bst_string1["summer"] << std::endl;

  std::cout << "Find the key \"sunday\" in the tree ";
  auto value5 = bst_string1.find("sunday");
  if (value5!=bst_string1.end()) std::cout << value5->first << ": "<<value5->second <<std::endl;
  else std::cout << "The key is not in the tree " << std::endl;

  std::cout << "Print the tree using Iterators " << '\n';
  for(auto i=bst_string1.begin(); i!=bst_string1.end(); i++){
    std::cout <<"("<<i->first <<":" <<i->second << ") ";
  }
  bst_string1.clear();



}
