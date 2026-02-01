#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"

class HashTable {
    Node<Student>** table;
    int size;

    void insert(Student* s, int hashNum, Node<Student>* curr);

public:
    HashTable(int s);
    ~HashTable();

    void hash(Student* s);
};

#endif