#include "hashTable.h"

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

void HashTable::hash(Student *s) {

  int hashNum = 0.0f;
  hashNum += (int)(s->firstName[0]);
  hashNum += (int)(s->lastName[0]);
  hashNum += (int)(s->GPA);
  hashNum *= 67;

  hashNum %= size;

  insert(s, hashNum, *table);
}

void HashTable::insert(Student* s, int hashNum, Node<Student>* curr) {

  //First thing
  if (curr->student == nullptr) { curr->student = s; }
  else if (curr->next == nullptr) { curr->next = new Node<Student>; }
  else { insert(s, hashNum, curr->next); }
}
