#include <iostream>
#include <map>
#include <fstream>
#include <string.h>
#include "Item.cpp"
using namespace std;

#define MACROSCOUNT 6

class ItemList {
public:
   map<string, Item> items;
   // variable length array storing name-item pairs
   ItemList() {}
   void load(fstream& in){
      char str[256];
      while(in.getline(str,256)){
         try{
            string line(str);
            Item item = Item(line);
            items.insert({item.name, item});
         } catch(const string msg){
            cerr << msg << endl;
            break;
         }
      }
   }
   void save(fstream& out){
      for(auto item : items){
         out << item.second.name << ",";
         for(int i=0;i<MACROSCOUNT-1;++i) out << item.second.nutri[i] << ",";
         out << item.second.nutri[MACROSCOUNT-1];
         out << endl;
      }
   }
   void put(string a, array<double, MACROSCOUNT> vals){
      if(items.find(a)!=items.end()) items.erase(a);
      items.insert({a, Item(a, vals)}); //TO DO
   }
   void remove(string name){
      if(items.find(name)!=items.end()) items.erase(name);
      else cout << "Err: Item \"" << name << "\" DNE";
   }
   void clear(){
      items.clear();
   }
   void print(fstream& out){
      for(std::pair<std::string,Item> elem : items){
         elem.second.print(out);
      }
   }
   void printOut(){
      for(std::pair<std::string,Item> elem : items){
         elem.second.printOut();
      }
   }
};
