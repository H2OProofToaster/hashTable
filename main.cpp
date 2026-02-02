#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

#include "hashTable.h"

using namespace std;

//Prototypes
vector<Student*> generateStudents(int num, int IDnum, const vector<string> &firstNames, const vector<string> &lastNames); //Hands off a vector of student pointers
void addStudent(HashTable* t, Student* s = nullptr);
void deleteStudent(HashTable* t, Student* s = nullptr);

int main () {

  //Generate name vectors
  ifstream fN("firstNames");
  ifstream lN("lastNames");

  if (fN.is_open() && lN.is_open()) {
    vector<string> firstNames;
    vector<string> lastNames;
    string name;
    
    //Get first names
    while (getline(fN, name)) {
      firstNames.push_back(name);
    }

    //Get last names
    while (getline(lN, name)) {
      lastNames.push_back(name);
    }
  }

  //Hash Table
  HashTable *table = new HashTable(23); //Make sure size is prime

  //Running variable
  bool quit = false;

  //ID counter
  int currID = 0;

  while (!quit) {

    cout << "What is your action? (ADD, DELETE, PRINT, QUIT)" << endl;
    string action;
    cin >> action;

    if (action == "ADD") {

      /* TODO: the tails don't fix themselves,
       *       and they need to
       *       the add function also does not use the tails
       *       for some reason
       */
      cout << "Adding..." << endl;
      addStudent(table);
    }
    else if (action == "DELETE") {

      cout << "Deleting..." << endl;
    }
    else if (action == "PRINT") {

      cout << "PRINT" << endl;
    }
    else if (action == "QUIT") {

      //Clean up
      delete table;

      quit = true;
    }
    else {

      cout << "Not an action" << endl;
    }

    //Clear action
    action.clear();
  }
  
  return 0;
}

vector<Student*> generateStudents(int num, int IDnum, const vector<string> &firstNames, const vector<string> &lastNames) {

  //Seed random numbers
  //Help from the Google AI
  mt19937 engine(chrono::system_clock::now().time_since_epoch().count());
  
  vector<Student*> students;
  while (num != 0) {
    Student* s = new Student;

    uniform_int_distribution<size_t> distFirst(0, firstNames.size() - 1);
    s->firstName = firstNames[distFirst(engine)];

    uniform_int_distribution<size_t> distLast(0, lastNames.size() - 1);
    s->lastName = lastNames[distLast(engine)];

    IDnum ++;
    s->ID = IDnum;

    uniform_real_distribution<float> distGPA(0.0f, 4.001f);
    s->GPA = distGPA(engine);

    students.push_back(s);\

    num ++;
  }
  return students;
}

void addStudent(HashTable* t, Student* s) {

  //No student given
  if (s == nullptr) {
    s =  new Student;

    cout << "What is the first name?";
    cin >> s->firstName;

    cout << "What is the last name?";
    cin >> s->lastName;

    cout << "What is the ID number?";
    cin >> s->ID;

    cout << "What is the GPA?";
    cin >> s->GPA;
  }

  t->insert(s);
}

void deleteStudent(HashTable* t, Student* s) {
  if (s == nullptr) {
    s = new Student;

    cout << "What is the first name?";
    cin >> s->firstName;

    cout << "What is the last name?";
    cin >> s->lastName;

    cout << "What is the ID number?";
    cin >> s->ID;

    cout << "What is the GPA?";
    cin >> s->GPA;
  }

  t->del(s);
  delete s;
}