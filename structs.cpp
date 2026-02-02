#include <string>

using namespace std;

//Student struct
struct Student {
    string firstName = "empty first name";
    string lastName = "empty last name";
    int ID = -1;
    float GPA = -1.0f;

    bool operator==(Student& other) {

        return firstName == other.firstName && \
               lastName == other.lastName && \
               ID == other.ID && \
               GPA == other.GPA;
    }
};

//Linked list node struct
template <typename T>
struct Node {
    T* student;
    Node* next = nullptr;
    Node* tail = this;

    Node() : student(nullptr) {} //Default
    Node(T* s) : student(s) {}

    ~Node() { delete student; }
};