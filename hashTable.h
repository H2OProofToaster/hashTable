#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"
#include <vector>

class HashTable {
    Node<Student>** table;
    int size;
    bool reHash = false;
  
    bool rehash(Node<Student>** old);
    Node<Student>* del(Student* s, Node<Student>* curr);
  
public:
    HashTable(int s);
    ~HashTable();

    void setTable(Node<Student>** t);
    Node<Student>** getTable();
  
    int hash(Student* s);
    void insert(Student* s, bool bypass = false);
    void del(Student* s);
    void rehash();
    void insert(vector<Student*> sVect);
    void print();
};

#endif
