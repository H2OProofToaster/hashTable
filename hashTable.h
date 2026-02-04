#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"

class HashTable {
    Node<Student>** table;
    int size;

    //Check that you don't need to rehash,
    //And fix to not do whatever this is
    Node<Student>** rehash(Node<Student>** old);
  
public:
    HashTable(int s);
    ~HashTable();

    int hash(Student* s);
    void insert(Student* s);
    void del(Student* s);
    //Maybe add a vector<Student*> overload
    void print();
};

#endif
