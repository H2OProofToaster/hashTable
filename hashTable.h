#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"
#include <vector>

class HashTable {
    Node<Student>** table;
    int size;
    Node<Student>* del(Student* s, Node<Student>* curr);
  
public:
    HashTable(int s);
    ~HashTable();

    void setTable(Node<Student>** t);
    Node<Student>** getTable();
  
    int hash(Student* s);
    bool insert(Student* s, bool inRehash = false);
    void del(Student* s);
    void insert(vector<Student*> sVect);
    void print();
    bool rehash();
};

#endif
