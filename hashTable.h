#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.cpp"
#include <vector>

class HashTable {
    Node<Student>** table;
    int size;
    bool doRehash = false;
    Node<Student>* del(Student* s, Node<Student>* curr);
  
public:
    HashTable(int s);
    ~HashTable();

    void setTable(Node<Student>** t);
    Node<Student>** getTable();

    bool getDoRehash();
  
    int hash(Student* s);
    void insert(Student* s);
    void del(Student* s);
    void insert(vector<Student*> sVect);
    void print();
    void checkRehash();
};

#endif
