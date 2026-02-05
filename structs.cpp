#ifndef STRUCTS_CPP
#define STRUCTS_CPP

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

//Student struct
struct Student {
    string firstName = "empty first name";
    string lastName = "empty last name";
    int ID = NULL;
    float GPA = NULL;
  
    bool operator==(Student& other) {

      return firstName == other.firstName && \
             lastName == other.lastName && \
             ID == other.ID && \
             GPA == other.GPA;
    }

    void print() { cout << firstName << endl << lastName << endl << ID << endl << fixed << setprecision(2) << GPA << endl; }
};

//Linked list node struct
template <typename T>
struct Node {
    T* student = nullptr;
    Node* next = nullptr;

    Node() {}
    Node(T* s) : student(s) {}
};

#endif
