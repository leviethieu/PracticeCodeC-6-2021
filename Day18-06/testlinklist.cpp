#include <iostream>
#include <list>
/*
Node
head -> [[_value][*next]] -> [_value,next] -> [_value,next] -> null;
*/
 
struct Node
{
    int _value;
    Node *next;
    Node() : next{nullptr} {}
    Node(int value) : _value{value}, next{nullptr} {}
};
 
void print(Node *list)
{
    //Node *iRun = list;
    while (list != nullptr)
    {
        std::cout << list->_value << " -> ";
        list = list->next;
    }
    std::cout << std::endl;
}
 
void remove(Node*& list, int _pos)
{
    Node* prev = nullptr;
    Node* current = list;
    int i = 1;
    while (i < _pos)
    {
        prev = current;
        current = current->next;
        i++;
    }
    prev->next = current->next;
    delete current;
    current = nullptr;
}
 
void push_front(Node*& list, int _x)
{
    Node * newNode = new Node();
    newNode->_value = _x;
    newNode->next = nullptr;
 
    if (list==nullptr)
    {
        list = newNode;
    }
    else
    {
        newNode->next = list;
        list = newNode;
    }
}
 
void insert(Node*& list, int _value, int _pos)
{
    Node* prev = nullptr;
    Node* current = list;
    int i = 1;
    while (i < _pos)
    {
        prev = current;
        current = current->next;
        i++;
    } 
    Node* newNode = new Node(_value);
    prev->next = newNode;
    newNode->next = current;
}   
 
void push_back(Node*& list, int _x)
{
    Node * newNode = new Node();
    newNode->_value = _x;
    newNode->next = nullptr;
    if (list == nullptr)
    {
        list = newNode;
        return;
    }
    Node* runList = list;
    push_back(runList->next,_x); 
}
 
int main()
{
    Node *Node1 = nullptr;
    // Node1 -> value = 0 || Node1 -> next = null;
    Node1 = new Node(3);
    Node1->next = new Node(2);
    Node1->next->next = new Node(2);
    print(Node1);
    Node *node2 = nullptr;
    push_back(node2,5);
    push_back(node2,7);
    push_back(node2,8);
    push_front(node2,2);
    insert(node2,10,3);
    print(node2);
    remove(node2,3);
    print(node2);
    Node *Node3 = nullptr;
    push_front(Node3,8);
    push_front(Node3,9);
    push_front(Node3,19);
    push_front(Node3,29);
    
    print(Node3);
    return 0;
}