#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

#include "structs.cpp"
#include "hashTable.h"

using namespace std;

//Prototypes
vector<Student*> generateStudents(int &currID, const vector<string> &firstNames, const vector<string> &lastNames); //Hands off a vector of student pointers
void addStudent(HashTable* t, int &currID, Student* s = nullptr);
void deleteStudent(HashTable* t, Student* s = nullptr);
void printStudents(HashTable* t);

int main () {

  cout << "Building..." << endl;
  //Generate name vectors
  ifstream fN("firstNames.txt");
  ifstream lN("lastNames.txt");
  vector<string> firstNames;
  vector<string> lastNames;

  if (fN.is_open() && lN.is_open()) {

    string name;
    
    //Get first names
    while (getline(fN, name)) {

      firstNames.push_back(name);
      //cout << "Add " << name << " to first names" << endl;
    }

    //Get last names
    while (getline(lN, name)) {

      lastNames.push_back(name);
      //cout << "Add " << name << " to last names" << endl;
    }
  }
  cout << "Done" << endl;

  //Hash Table
  HashTable *table = new HashTable(100); //Make sure size is prime

  //Running variable
  bool quit = false;

  //ID counter
  int currID = 1;

  while (!quit) {

    cout << "What is your action? (ADD, GENERATE, DELETE, PRINT, QUIT)" << endl;
    string action;
    cin >> action;

    if (action == "ADD") {

      cout << "Adding..." << endl;
      addStudent(table, currID);
      cout << "Done" << endl;
    }
    else if (action == "GENERATE") {

      cout << "Generating..." << endl;
      table->insert(generateStudents(currID, firstNames, lastNames));
    }
    else if (action == "DELETE") {

      cout << "Deleting..." << endl;
      deleteStudent(table);
      cout << "Done" << endl;
    }
    else if (action == "PRINT") {

      cout << "Printing..." << endl;
      printStudents(table);
      cout << "Done" << endl;
    }
    else if (action == "QUIT") {

      cout << "Quitting..." << endl;
      //Clean up
      delete table;
      cout << "Done" << endl;
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

vector<Student*> generateStudents(int &currID, const vector<string> &firstNames, const vector<string> &lastNames) {

  cout << "How many students? ";
  int num;
  cin >> num;

  cout << "Building..." << endl;
  
  //Seed random numbers
  //Help from the Google AI
  mt19937 engine(chrono::system_clock::now().time_since_epoch().count());
  
  vector<Student*> students;
  while (num != 0) {
    Student* s = new Student();

    uniform_int_distribution<size_t> distFirst(0, firstNames.size() - 1);
    s->firstName = firstNames[distFirst(engine)];

    uniform_int_distribution<size_t> distLast(0, lastNames.size() - 1);
    s->lastName = lastNames[distLast(engine)];

    s->ID = currID;
    currID ++;

    uniform_real_distribution<float> distGPA(0.0f, 4.001f);
    s->GPA = distGPA(engine);

    students.push_back(s);\

    num --;
  }
  cout << "Done" << endl;
  return students;
}

void addStudent(HashTable* t, int &currID, Student* s) {

  //No student given
  if (s == nullptr) {
    s =  new Student;

    cout << "What is the first name? ";
    cin >> s->firstName;

    cout << "What is the last name? ";
    cin >> s->lastName;

    s->ID = currID;
    currID ++;

    cout << "What is the GPA? ";
    cin >> s->GPA;
  }

  t->insert(s);
}

void deleteStudent(HashTable* t, Student* s) {
  if (s == nullptr) {
    s = new Student;

    cout << "What is the first name? ";
    cin >> s->firstName;

    cout << "What is the last name? ";
    cin >> s->lastName;

    cout << "What is the ID number? ";
    cin >> s->ID;

    cout << "What is the GPA? ";
    cin >> s->GPA;
  }

  t->del(s);
  delete s;
}

void printStudents(HashTable* t) {

  t->print();
}
