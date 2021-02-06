#include <iostream>
#include <array>
#include <string>
using namespace std;

#define MACROSCOUNT 6
string errorMsg[1] = {"Incorrect format: "};
string macros[MACROSCOUNT] = {"Carbs", "Protein", "Sugar", "Fat", "Saturated", "Unsaturated"};

class Item {
public:
   string name;
   array<double, MACROSCOUNT> nutri;
   Item(string a, array<double, MACROSCOUNT> vals) {
      name = a;
      nutri = vals;
   }
   Item(string line){
      //throw errorMsg[0]+line;
      int start = 0;
      int curField = 0; // 0:name, 1-6: Macros
      int commaIndex = line.find(',',start);
      name = line.substr(0,commaIndex);

      start = commaIndex;
      for(int i=0;i<MACROSCOUNT-1;++i){
         commaIndex = line.find(',',start+1);
         nutri[i] = atof(line.substr(start+1,commaIndex).c_str());
         start = commaIndex;
      }
      nutri[MACROSCOUNT-1] = atof(line.substr(start+1,line.length()).c_str());
   }
   void print(fstream& out) const{
      out << "Nutrition: " << name << endl << endl;
      for(int i=0;i<MACROSCOUNT;++i){
         out << macros[i] << ": " << nutri[i] << endl;
      }
   }
   void printOut(){
      cout << "Nutrition: " << name << endl << endl;
      for(int i=0;i<MACROSCOUNT;++i){
         cout << macros[i] << ": " << nutri[i] << endl;
      }
   }
};
