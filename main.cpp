#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

//Student struct
struct Student {
  string firstName;
  string lastName;
  int ID;
  float GPA;
};

//Linked list node struct
template <typename T>;
struct Node {
  T* s;
  Node* n;
};

#include "hashTable.h"

//Prototypes
vector<Student*> generateStudents(int num, int IDnum, vector<string> firstNames, vector<string> lastNames);
  
int main () {

  //Generate name vectors
  ifstream firstNames("firstNames");
  ifstream lastNames("lastNames");
  vector<string> firstNames;
  vector<string> lastNames;
  
  if (firstNames.is_open() && lastNames.is_open()) {
    string name;
    
    //Get first names
    while (getline(firstNames, name)) {
      firstNames.push_back(name);
    }

    //Get last names
    while (getline(lastNames, name)) {
      lastNames.push_back(name);
    }
  }
  
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

vector<Student*> generateStudents (int num, int IDnum, vector<string> firstNames, vector<string> lastNames) {

  //Seed random numbers
  //Help from the google IA
  mt19937 engine(chrono::system_clock::now().time_since_epoch().count());
  
  vector<Student*> students;
  while (num != 0) {
    Student* s = new Student;

    uniform_int_distribution<size_t> dist(0, firstNames.size() - 1);
    s->firstName = firstNames[dist(engine)];

    uniform_int_distribution<size_t> dist(0, lastNames.size() - 1);
    s->lastName = lastNames[dist(engine)];

    s->ID = IDnum;
    IDnum ++;

    uniform_real_distribution<float> dist(0.0f, 4.001f);
    s->GPA = dist(engine);

    students.push_back(s);
  }
  return students;
}
