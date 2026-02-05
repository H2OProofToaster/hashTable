#include "hashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int s) {

  table = new Node<Student>*[s];
  for(int i = 0; i < s; i++) { table[i] = nullptr; }
  size = s;
}

HashTable::~HashTable() {
  for (int i = 0; i < size; i++) {

    Node<Student>* curr = table[i];
    while (curr != nullptr) {

      Node<Student>* temp = curr;
      curr = curr->next;

      delete temp->student;
      delete temp;
    }
  }

  delete[] table;
}

int HashTable::hash(Student *s) {

  int hashNum = 0.0f;
  hashNum += (int)(s->firstName[0]);
  hashNum += (int)(s->lastName[0]);
  hashNum += (int)(s->GPA);
  hashNum *= 67;

  hashNum %= size;
  return hashNum;
}

void HashTable::insert(Student* s) {

  int hashNum = hash(s);
  int collisions = 1;
  
  Node<Student>** currIndex = &table[hashNum];
  
  //Empty index
  if (*currIndex == nullptr) { table[hashNum] = new Node<Student>(s); }
  
  else {
    Node<Student>* currNode = *currIndex;
    
    while (currNode->next != nullptr) { currNode = currNode->next; collisions ++; }
    currNode->next = new Node<Student>(s);
  }
}

void HashTable::del(Student* s) {

  int hashNum = hash(s);
  Node<Student>* curr = table[hashNum];

  //Nothing at index
  if (curr = nullptr) { return; }

  while (curr->student != s) { curr = curr->next; }

  Node<Student>* temp = table[hashNum];
  while (temp->next != curr) { temp = temp->next; }
  temp->next = curr->next;

  delete curr;
}

//Private, automatically called with 3+ collisions
Node<Student>** HashTable::rehash(Node<Student>** old) {

  HashTable newTable(size * 2);

  for (int i = 0; i < size; i++) {

    Node<Student>* curr = old[i];
    do {

      if (curr->student != nullptr) {

	newTable.insert(curr->student);
	curr->deleteData = false; //Save student data
	delete curr;
	curr = curr->next;
      }
    } while (curr != nullptr);
  }

  size = size * 2;
  return newTable.table;
}

void HashTable::print() {

  for (int i = 0; i < size; i++) {

    Node<Student>** currIndex = &table[i];
    
    if (*currIndex != nullptr) {

      Node<Student>* currNode = *currIndex;

      do {

	currNode->student->print();
	cout << endl;
	currNode = currNode->next;
      } while (currNode != nullptr);
    }
  }
}
