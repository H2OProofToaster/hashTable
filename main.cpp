#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>

using namespace std;

//Student struct
struct Student {
  string firstName;
  string lastName;
  int ID;
  int GPA;
};

//Linked list node struct
template <typename T>;
struct Node {
  T* s;
  Node* n;
};

#include "hashTable.h"

//Prototypes
void generateStudents(int num, int nextID);
  
int main () {  

  HashTable table = new HashTable();
  
  bool quit = false;

  while (!quit) {

    cout << "What is your action? (ADD, DELETE, PRINT, QUIT)" << endl;
    string action;
    cin >> action;

    if (action.compare("ADD") == 0) {

      cout << "ADD" << endl; 
    }
    else if (action.compare("DELETE") == 0) {

      cout << "DELETE" << endl;
    }
    else if (action.compare("PRINT") == 0) {

      cout << "PRINT" << endl;
    }
    else if (action.compare("QUIT") == 0) {

      cout << "QUIT" << endl;
    }
    else {

      cout << "Not an action" << endl;
    }

    //Clear action
    action.clear();
  }
  
  return 0;
}

void generateStudents(int num, int nextID, vector<string> firstNames, vector<string> lastNames) {
  ifstream firstNames("firstNames");
  ifstream lastNames("lastNames");

  if(firstNames.is_open() && lastNames.is_open()) {
    vector<string> firstNames;
    vector<string> lastNames;

    //GetFirst
