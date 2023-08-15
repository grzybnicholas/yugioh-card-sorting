#include "Node.hpp"
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include "CardShop.cpp"
#include <iostream>
#include <algorithm>

int main(){
  CardShop list;
  list.insert(0, new YGOCard("Dark Magician", "Spellcaster", 7, "Spellcaster", "Dark", 2500, 2100));
  list.insert(1, new YGOCard("Blue-Eyes White Dragon", "Dragon", 8, "Dragon", "Light", 3000, 2500));
  list.insert(2, new YGOCard("Red-Eyes Black Dragon", "Dragon", 7, "Dragon", "Dark", 2400, 2000));
  list.insert(3, new YGOCard("Exodia the Forbidden One", "Spellcaster", 12, "Spellcaster", "Dark", 0, 0));
  list.insert(4, new YGOCard("Summoned Skull", "Fiend", 6, "Fiend", "Dark", 2500, 1200));
  list.insert(5, new YGOCard("Gaia the Fierce Knight", "Warrior", 4, "Warrior", "Earth", 2300, 1200));
  list.insert(6, new YGOCard("Curse of Dragon", "Spellcaster", 4, "Spellcaster", "Dark", 1500, 1200));
  list.bubbleSort(std::less<int>(), "atk");
  list.display();
}