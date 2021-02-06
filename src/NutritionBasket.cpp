#include <array>
#include <fstream>
#include <iostream>
#include <string.h>
#include "ItemList.cpp"
using namespace std;

int main(){
   ItemList basket, library;
   fstream libraryList("lists/library.txt");
   fstream basketList("lists/basket.txt");
   basket.load(&basketList);
   library.load(&library);

   // at this point, user can R/W into persistent storage (basket/library)
   // using ItemList.insert(), delete(), etc.
   return 0;
}
