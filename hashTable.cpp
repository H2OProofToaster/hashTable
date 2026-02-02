#include "hashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int s) {

  table = new Node<Student>*[s];
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

//Public for manual insertion
void HashTable::insert(Student* s) {

  int hashNum = hash(s);
  Node<Student>* curr = *(this->table);

  //First thing
  if (curr->student == nullptr) { curr->student = s; }

  //Empty next, create one
  else if (curr->next == nullptr) { curr->next = new Node<Student>(s); }

  //Recursive call
  else { insert(s, hashNum, curr->next, 1); }
}

//Private, for recursion
Node<Student>* HashTable::insert(Student* s, int hashNum, Node<Student>* curr, int collisionCount) {

  //Too many collisions
  if (collisionCount > 3) { table = rehash(table); }

  //First thing
  if (curr->student == nullptr) { curr->student = s; return curr; }
  //Empty next, create one
  else if (curr->next == nullptr) { curr->next = new Node<Student>(s); }
  //Recursive call
  else { return insert(s, hashNum, curr->next, collisionCount + 1); }

  return nullptr;
}

//Public for manual deletion
void HashTable::del(Student* s) {

  int hashNum = hash(s);
  Node<Student>* curr = table[hashNum];

  //Head cases

  //Case: Entirely empty index
  if (curr->student == nullptr && curr->next == nullptr) { cout << "Does not exist" << endl; }

  //Case: The only node at this index matches
  else if (curr->student == s && curr->next == nullptr) { delete curr->student; }

  //Case: Head matches
  else if (curr->student == s && curr->next != nullptr) { table[hashNum] = curr->next; delete curr; }

  //Recursion
  else {

    Node<Student>* stitch = del(s, hashNum, curr->next);
    if (stitch != nullptr) {

      delete curr->next;
      curr->next = stitch;
    }
  }
}

//Private for recursion
Node<Student>* HashTable::del(Student* s, int hashNum, Node<Student>* curr) {

  if (curr->student == s) { return curr->next; }

  Node<Student>* stitch = del(s, hashNum, curr->next);
  if(stitch != nullptr) {

    delete curr->next;
    curr->next = stitch;
  }
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

    Node<Student>* curr = table[i];
    do {
      
      if (curr->student != nullptr) {
	curr->student->print();
	curr = curr->next;
      }
    } while (curr != nullptr);
  }
}
