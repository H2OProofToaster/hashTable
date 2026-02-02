#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"

class HashTable {
    Node<Student>** table;
    int size;

    Node<Student>* insert(Student* s, int hashNum, Node<Student>* curr, int collisionCount);
    Node<Student>* del(Student* s, int hashNum, Node<Student>* curr);
    Node<Student>** rehash(Node<Student>** old);

public:
    HashTable(int s);
    ~HashTable();

    int hash(Student* s);
    void insert(Student* s);
    //Maybe add a vector<Student*> overload
    void del(Student* s);
};

#endif