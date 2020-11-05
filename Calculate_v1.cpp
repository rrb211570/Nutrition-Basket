/*1. class Item{//variables for macros, vitamins, etc.}
2. Print(Item)
3. HashMap<name, Item> blueprint //reveals nutrition data based on name
4. List groceries<Pair(name,quantity)>; //put, print, find, delete, clear
5. calculate(groceries) // calculate avg nutrition per day, based on "List groceries"
6. Implement pipe in/out for persistent local data storage.*/
#include <iostream>
#include <tr1/unordered_map>
#include <chrono>
#include <thread>
using namespace std;

#define MACROSCOUNT 6

string macros[MACROSCOUNT] = {"Protein", "Fat", "Saturated", "Unsaturated", "Carbs", "Sugar"};

class Item {
public:
   string name;
   int id;
   int grams;
   std::array<double, MACROSCOUNT> nutri;
   Item(string a, int b, int c, double protein, double fat, double saturated, double unsaturated, double carbs, double sugar) {
      name = a;
      id = b;
      grams = c;
      nutri = {protein, fat, saturated, unsaturated, carbs, sugar};
   }
   void print(){
      cout << "Nutrition: " << name << ", " << grams << "g"<< endl << endl;
      for(int i=0;i<MACROSCOUNT;++i){
         cout << macros[i] << ": " << nutri[i] << endl;
      }
   }
};

int main()
{
   using namespace std::chrono_literals;
   using std::chrono::system_clock;
   cout << "Let us first examine the first-ever discovered 'Brotato'.\n" << endl;
   Item test("Brotato",1,100,5,10,12.5,11.1,13,8);
   test.print();
   cout << endl << endl << "Wow, nutritious!" << endl;
   std::this_thread::sleep_for(3s);

   std::tr1::unordered_map<string, Item> bluePrint;
   while(1){
      cout << "Let us now add our wisdom.\n\nEnter: {string name, int id, int grams, int protein, int fat, int saturated, int unsaturated, int carbs, int sugar}\n\nEx: {\"Edible Spatula\", 2, 500, 10, 5, 6, 7, 8, 9}\n" << endl;
      break; // To be continued...
   }
   return 0;
}
