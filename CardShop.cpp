/*
Author Name: Nicholas Grzyb
File Name: CardShop.cpp
Date Created/Modified: 3/31/2023

Implementation of the CardShop class for sorting algorithms using doubly linked lists
*/


#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

template<typename Comparator>
int CardShop::bubbleSort(Comparator comp, std::string key){
   int count{0};
   bool check_swap = true;
   while(check_swap){
    check_swap = false;
    for(int i = 0; i < getLength() - 1; i++){
     if(key == "atk"){
      if(comp(getItem(i+1)->getAtk(),getItem(i)->getAtk())){
        swap(i+1,i);
        check_swap = true;
        count++;
      }
    }
   else if(key == "def"){
     if(comp(getItem(i+1)->getDef(),getItem(i)->getDef())){
        swap(i,i+1);
        check_swap = true;
        count++;
     }
   }
  }
 }
   return count;
}

template<typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key){
  int count{0};
  int x;
  for(int i = 0; i < item_count_; i++){
    x = i;
    if(key == "atk"){
      while(x > 0 && comp(getItem(x)->getAtk(),getItem(x-1)->getAtk())){
        swap(x-1,x);
        count++;
        x--;
      }
    }
    if(key == "def"){
      while(x > 0 && comp(getItem(x)->getDef(),getItem(x-1)->getDef())){
        swap(x-1,x);
        count++;
        x--;
      }
    }
  }
  return count;
}

template<typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key){
  return 0;
}

template<typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key){
  int count = 0;
  preQuick(comp,key,0,item_count_ - 1, count);
  return count;
}
// the method that does the acutal swapping, partitions all pointers in the doubly linked list
  template<typename Comparator>
  int CardShop::part(Comparator comp, std::string key, int first, int last, int& count){
    Node<YGOCard*>* pivot_node = getPointerTo(last);
    int first_node = first - 1;
    int last_node = last - 1;
    for(int i = first; i <= last_node; i++){
      if(key == "atk"){
        if(comp(getPointerTo(i)->getItem()->getAtk(), pivot_node->getItem()->getAtk())){
          first_node++;
          swap(first_node,i);
          count++;
        }
      }else if(key == "def"){
       if(comp(getPointerTo(i)->getItem()->getDef(), pivot_node->getItem()->getDef())){
          first_node++;
          swap(first_node,i);
          count++;
       }
      }
    } 
    first_node++;
    swap(first_node,last);
    count++;
    return first_node;
  }
//sets up the quick sort method, so it can just be called in the actual quick sort method (legit does the quick sort for the quick sort function)
  template<typename Comparator>
  void CardShop::preQuick(Comparator comp, std::string key, int first, int last, int& count){
    if(last <= first){
      return;
    }
    int pivot = part(comp, key, first, last, count);
    preQuick(comp, key, first, pivot - 1, count);
    preQuick(comp, key, pivot + 1, last, count);
  }

