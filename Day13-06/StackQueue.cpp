#include<iostream>
#include<string>
#define MAX 20
#define MAX1 10

using namespace std;

class Student
{
private:
    string mName;
public:
    Student() {};
    Student(const string& name);
    ~Student();
    string getName();
};

Student::Student(const string& name)
{
    this->mName = name;
}

Student::~Student()
{
}
string Student::getName() {
    return mName;
}

class StackStudent
{
private:
    int mSize = 0;                               
    Student Stack[MAX];
public:
    StackStudent();
    ~StackStudent();
    void Push(const Student& student);
    void Pop();
    Student Peek();
    void PrintListStudent();
};

StackStudent::StackStudent()
{
    mSize = 0;
}

StackStudent::~StackStudent()
{
    mSize = 0;
}
// Adds an item in the stackStudent
void StackStudent::Push(const Student& student) {
 
    if (mSize < MAX) {
        mSize++;
        Stack[mSize-1] = student;
        cout << "Inserted to Stack" << endl;
    }
    else
        cout << "Stack full !" << endl;
}
// Removes an item from the stackStudent
void StackStudent::Pop() {
    if (mSize == 0) {
        cout << " Stack empty !" << endl;
    }
    else {
        cout << "Removed :" << Stack[mSize - 1].getName();
        mSize--;
    }
}
// Returns a stdent in the top of the stackStudent
Student StackStudent::Peek() {
        if (mSize == 0) {
            throw "Stack empty !";
        }
        else {
            return Stack[mSize-1];
        }
       
}
//Print list of student
void StackStudent::PrintListStudent() {
    for (int i = 0; i < mSize; i++) {
        cout << Stack[i].getName() << endl;
    }
}


class QueueStudent
{
private:
    Student Queue[MAX1]; 
    int mSize;      // current size of the queue

public:
    QueueStudent();
    ~QueueStudent();
    void Enqueue(const Student& student1);
    void Dequeue();
    Student Peek();
    void PrintListStudent();
};

QueueStudent::QueueStudent()
{
    mSize = 0;
}

QueueStudent::~QueueStudent()
{
}
  //adds the element Student at the end of the queueStudent
void QueueStudent::Enqueue( const Student &student1) {
    // check for queue overflow
    if (mSize == MAX1)
    {
        cout << "Queue is full" << endl;
    }
    else {
        Queue[mSize] = student1;
        mSize++;
        cout << "Inserted to Queue " << endl;
    }
}
//return and delete the first element of the queueStudent
void QueueStudent::Dequeue() {

    if (mSize == 0) {
        cout << "Queue is empty ! Can't get data" << endl;    // Queue is empty
    }

    else if (mSize == 1) {
        cout <<"Take :" << Queue[0].getName() << endl;
        mSize--;
      }

        else {
          cout << "Take :" << Queue[0].getName() << endl;
            for (int i = 0;i < mSize-1; i++) {         // Delete student from element
                Queue[i] = Queue[i+1];
            }
            mSize--;
        }
  
}
// returns a Student to the first element of the queueStudent
Student QueueStudent::Peek() {

     return Queue[0];
}
void QueueStudent::PrintListStudent() {
    for (int i = 0; i < mSize; i++) {
        cout << Queue[i].getName() << endl;
    }
}

int main() {
    
    StackStudent *list = new StackStudent;
    Student sv1("Nguyen Van A");
    Student sv2("Nguyen Van B");
    Student sv3("Nguyen Van C");
    Student sv4("Nguyen Van D");
    Student sv5("Nguyen Van E");
    Student sv6("Nguyen Van F");
    Student sv7("Nguyen Van G");
    Student sv8("Nguyen Van H");
    Student sv9("Nguyen Van K");
    Student sv10("Nguyen Van L");
    // Input 10 student to Stack
    list->Push(sv1);
    list->Push(sv2);
    list->Push(sv3);
    list->Push(sv4);
    list->Push(sv5);
    list->Push(sv6);
    list->Push(sv7);
    list->Push(sv8);
    list->Push(sv9);
    list->Push(sv10);
    // print list student
    list->PrintListStudent();
    // print and delete all student
    for (int i = 0; i < 10; i++) {
        list->Pop();
        cout << endl;
    }
    // after delete all => print stack empty
    try
    {
        cout << list->Peek().getName() << endl;
    }
    catch (const char* message)
    {
        cerr << message << endl;
    }
    cout << "========================================================" << endl;
    QueueStudent *list1 = new QueueStudent;
    // Input 10 student to Queue
    list1->Enqueue(sv1);
    list1->Enqueue(sv2);
    list1->Enqueue(sv3);
    list1->Enqueue(sv4);
    list1->Enqueue(sv5);
    list1->Enqueue(sv6);
    list1->Enqueue(sv7);
    list1->Enqueue(sv8);
    list1->Enqueue(sv9);
    list1->Enqueue(sv10);

    cout << "List Student" << endl;
    list1->PrintListStudent();

    // take 5 student
    for (int i = 0; i < 5; i++) {
        list1->Dequeue();
    }
    
    cout << "List student after Dequeue :" << endl;
    list1->PrintListStudent();

    // add 5 student
    list1->Enqueue(sv1);
    list1->Enqueue(sv2);
    list1->Enqueue(sv3);
    list1->Enqueue(sv4);
    list1->Enqueue(sv5);

    list1->PrintListStudent();
}