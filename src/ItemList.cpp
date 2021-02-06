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
   array<double, MACROSCOUNT> sumNutri = {0,0,0,0,0,0};
   // variable length array storing name-item pairs
   ItemList() {}
   // Memory Interactions
   void load(fstream& in){
      char str[256];
      while(in.getline(str,256)){
         try{
            string line(str);
            Item item = Item(line);
            this->put(item.name, item.nutri);
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
   // Modifications
   void put(string a, array<double, MACROSCOUNT> vals){
      if(items.find(a)!=items.end()) this->remove(a);
      items.insert({a, Item(a, vals)});
      for(int i=0;i<MACROSCOUNT;++i) sumNutri[i] += vals[i];
   }
   void remove(string name){
      if(items.find(name)!=items.end()){
         Item item = items.at(name);
         for(int i=0;i<MACROSCOUNT;++i) sumNutri[i] -= item.nutri[i];
         items.erase(name);
      } else cout << "Err: Item \"" << name << "\" DNE";
   }
   void clear(){
      items.clear();
      memset(&sumNutri, 0, sizeof(sumNutri));
   }
   // Features
   array<double, MACROSCOUNT> average(int days){
      array<double, MACROSCOUNT> vals = sumNutri;
      for(int i=0;i<MACROSCOUNT;++i) vals[i]/=days;
      return vals;
   }
   // Printing
   void print(fstream& out){
      for(std::pair<std::string,Item> elem : items){
         elem.second.print(out);
      }
   }
   void printSum(){
      for(int i=0;i<MACROSCOUNT;++i) cout << sumNutri[i] << " ";
   }
   void printOut(){
      for(std::pair<std::string,Item> elem : items){
         elem.second.printOut();
      }
   }
};
