#include <array>
#include <fstream>
#include <iostream>
#include <string.h>
#include "../src/ItemList.cpp"
using namespace std;

std::array<double, MACROSCOUNT> vals = {1,5,4,3,4,5};

// add Item
void test1(ItemList *basket, fstream *file){
   basket->put("Brotato", vals);
   basket->print(*file);
}

// add multiple items
void test2(ItemList *basket, fstream *file){
   basket->put("Brotato2", vals);
   basket->print(*file);
}

// update item
void test3(ItemList *basket, fstream *file){
   vals[2] = 22;
   basket->put("Brotato", vals);
   basket->print(*file);
}

// remove item
void test4(ItemList *basket, fstream *file){
   basket->remove("Brotato");
   basket->print(*file);
}

// save ItemList
void test5(ItemList *basket, fstream *file){
   basket->save(*file);
}

// load ItemList
void test6(ItemList *basket, fstream *file){
   basket->clear();
   fstream loadFile("expected_output/expected_test_6.txt");
   basket->load(loadFile);
   basket->save(*file);
}

// Avg of ItemList
void test7(ItemList *basket, fstream *file){
   array<double, MACROSCOUNT> avgVals = basket->average(7);
   for(int i=0;i<MACROSCOUNT;++i){
      *file << macros[i] << ":" << avgVals[i] << endl;
   }
}

struct {
   const char *output;
   const char *expectedOutput;
   void (*operation)(ItemList*, fstream*);
   const char *label;
} fileList[] = {
   {"test_output/test_1.txt", "expected_output/expected_test_1.txt", test1, "Add Item          "},
   {"test_output/test_2.txt", "expected_output/expected_test_2.txt", test2, "Add Multiple Items"},
   {"test_output/test_3.txt", "expected_output/expected_test_3.txt", test3, "Update Item       "},
   {"test_output/test_4.txt", "expected_output/expected_test_4.txt", test4, "Remove Item       "},
   {"test_output/test_5.txt", "expected_output/expected_test_5.txt", test5, "Save ItemList     "},
   {"test_output/test_6.txt", "expected_output/expected_test_6.txt", test6, "Load ItemList     "},
   {"test_output/test_7.txt", "expected_output/expected_test_7.txt", test7, "Avg of ItemList   "}
};

int main()
{
   int tests = 7;
   int passed = 0;
   ItemList basket;

   cout << "Running tests:" << endl;
   for (int i = 0; i < 7; ++i) {
      cout << fileList[i].label << " : ";
      ofstream temp(fileList[i].output); //creates if necessary
      temp.close();
      fstream file1(fileList[i].output);
      fstream file2(fileList[i].expectedOutput);

      fileList[i].operation(&basket, &file1); // (run) print test output to file
      file1.clear();   // reset pointers/flags
      file1.seekg(0,ios::beg);
      file2.clear(); // necessary b/c of load test
      file2.seekg(0,ios::beg);

      int lineCount1=0; // compare line count
      int lineCount2=0;
      string str;
      while(getline(file1,str)) lineCount1++;
      while(getline(file2,str)) lineCount2++;
      if(lineCount1 != lineCount2) {
         cout << "Fail: diff lineCount" << endl;
         continue;
      }

      file1.clear();   // reset pointers/flags
      file1.seekg(0,ios::beg);
      file2.clear();
      file2.seekg(0,ios::beg);

      char line1[256], line2[256]; // compare lines
      bool diff = false;
      while(file1.getline(line1,256)&&file2.getline(line2,256))
      {
         if(strcmp(line1,line2) != 0){
            cout << "Fail: different lines" << endl;
            diff = true;
            break;
         }
      }
      if(diff==false){
         cout << "Pass" << endl;
         passed++;
      }
   }
   cout << "\nTests Passed: " << passed << "/" << tests << endl;
   return 0;
}
