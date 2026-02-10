#include "hashTable.h"
#include <iostream>
#include <vector>

using namespace std;

HashTable::HashTable(int s) {

  table = new Node<Student>*[s];
  for(int i = 0; i < s; i++) { table[i] = nullptr; }
  size = s;
}

HashTable::~HashTable() {
  if (table != nullptr) {
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
}

void HashTable::setTable(Node<Student>** t) { table = t; }

Node<Student>** HashTable::getTable() { return table; }

int HashTable::hash(Student *s) {

  int hashNum = 0.0f;
  hashNum += (int)(s->firstName[0]);
  hashNum += (int)(s->lastName[0]);
  hashNum += (int)(s->GPA);
  hashNum += s->ID;
  hashNum *= 67;

  hashNum %= size;
  return hashNum;
}

bool HashTable::insert(Student* s, bool inRehash) {

  int hashNum = hash(s);
  int collisions = 1;
  
  //Empty index
  if (table[hashNum] == nullptr) { table[hashNum] = new Node<Student>(s); }
  
  else {
    Node<Student>* currNode = table[hashNum];
    
    while (currNode->next != nullptr) { currNode = currNode->next; collisions ++; }

    currNode->next = new Node<Student>(s);
  }

  if (collisions > 3 && !inRehash) {

    bool doRehash = false;
    do {
      
      doRehash = false;
      cout << "Do rehash at size " << size << " with collisions " << collisions << endl;
      rehash();
    } while (doRehash);

    return false;
  }
  
  else if (collisions > 3 && inRehash) { return true; }

  return false;
}

void HashTable::del(Student* s) {

  int hashNum = hash(s);
  
  if (del(s, table[hashNum]) != nullptr) {

    Node<Student>* temp = table[hashNum]->next;
    delete table[hashNum]->student;
    delete table[hashNum];
    table[hashNum] = temp;
  }
}

Node<Student>* HashTable::del(Student* s, Node<Student>* curr) {

  if (curr == nullptr) { return nullptr; }

  else if (*(curr->student) == *s) {

    //fix : end of list
    return (curr->next != nullptr) ? curr->next : curr;
  }

  else {

    Node<Student>* fix = del(s, curr->next);

    //End of list
    if (fix == curr->next) {

      delete curr->next->student;
      delete curr->next;
      curr->next = nullptr;
    }

    else if (fix != nullptr) {

      delete curr->next->student;
      delete curr->next;
      curr->next = fix;
    }

    else { return nullptr; }
  }
}

//Private, automatically called with 3+ collisions
bool HashTable::rehash() {

  cout << "Rehashing with size = " << size * 2 << "..." << endl;

  HashTable* newTable = new HashTable(size * 2);

  bool redoRehash = false;
  
  for (int i = 0; i < size; i++) {

    Node<Student>* curr = table[i];
    if (curr != nullptr) {

      do {
	  
        redoRehash = newTable->insert(curr->student, true);
	curr = curr->next;
      } while (curr != nullptr);
    }
  }

  table = newTable->getTable();
  newTable->setTable(nullptr);
  delete newTable;
  size = size * 2;

  cout << "Done" << endl;

  return redoRehash;
}

void HashTable::insert(vector<Student*> sVect) {

  cout << "Inserting..." << endl;
  for (int i = 0; i < sVect.size(); i++) {

    insert(sVect[i]);
  }
  cout << "Done" << endl;
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
