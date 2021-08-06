#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Student {
private:
    string mName;
    string mDateOfBirth;
    string mClass;
    int mId;

public:
    Student() : mId{ 0 }, mName{ "" }, mDateOfBirth{ "" }, mClass{ "" } {};
    Student(int id, string name, string dateofbirth, string classofstudent) : mId{ id }, mName{ name }, mDateOfBirth{ dateofbirth }, mClass{ classofstudent } {};
    ~Student() {};
    string getName() {
        return mName;
    }
    int getId() {
        return mId;
    }
    string getDateOfBirth() {
        return mDateOfBirth;
    }
    string getClass() {
        return mClass;
    }
    Student(const Student& other) {
        this->mName = other.mName;
        this->mId = other.mId;
        this->mDateOfBirth = other.mDateOfBirth;
        this->mClass = other.mClass;
    }
    Student operator=(const Student& rhs) {
        this->mName = rhs.mName;
        this->mId = rhs.mId;
        this->mDateOfBirth = rhs.mDateOfBirth;
        this->mClass = rhs.mClass;
        return *this;
    }
    void readStudent(ifstream& filename) {
        filename >> mId;
        filename.seekg(1, 1);
        getline(filename, mName, ',');
        getline(filename, mDateOfBirth, ',');
        getline(filename, mClass);
    }

};

//create node of double linked list
class Node {
    friend class Doublelinklist;
private:
    Student mStudent;
    Node* mNext;
    Node* mPrev;

public:
    Node() : mNext{ nullptr }, mPrev{ nullptr } {};
    Node(Student student) : mStudent{ student }, mNext{ nullptr }, mPrev{ nullptr } {};
    ~Node() {};

};


class Doublelinklist {
private:
    Node* list;
public:
    Doublelinklist() : list{ nullptr } {}
    void Push_back(const Student& student);
    void Push_front(const Student& student);
    void Insert(const Student& student, const int pos);
    void Print();
    void Remove(const int& Id);
    void bubbleSort();
    void Swap(Node*& nodeA, Node*& nodeB);
    void saveStudentToFile(const string& filename);

};
void Doublelinklist::Push_back(const Student& student) {

    Node* newNode = new Node();
    Node* lastNode = list;

    newNode->mStudent = student;
    newNode->mNext = nullptr;

    if (list == nullptr) {
        newNode->mPrev = nullptr;
        list = newNode;
        return;
    }

    while (lastNode->mNext != nullptr) {
        lastNode = lastNode->mNext;
    }

    lastNode->mNext = newNode;

    newNode->mPrev = lastNode;
}
void Doublelinklist::Push_front(const Student& student) {

    Node* newNode = new Node();

    newNode->mStudent = student;

    newNode->mNext = list;
    newNode->mPrev = nullptr;

    if (list != nullptr) {
        list->mPrev = newNode;
    }
    list = newNode;
}

void Doublelinklist::Print() {
    Node* readlist = new Node();
    readlist = list;
    while (readlist != nullptr) {
        cout << " Id : " << readlist->mStudent.getId() << " - " << " Name : " << readlist->mStudent.getName() << " - " << " DateofBirth : " << readlist->mStudent.getDateOfBirth() << " - " << " Class : " << readlist->mStudent.getClass() << endl;
        readlist = readlist->mNext;
    }
}

void Doublelinklist::Remove(const int& Id) {

    Node* current = new Node();
    current = list;
    int count = 0;

    while (current != nullptr) {
        if (current->mStudent.getId() == Id) {
            count++;
            break;
        }
        current = current->mNext;
    }

    if (count == 0) {
        cout << "No suitable students for delete !" << endl;
    }

    if (list == nullptr || current == nullptr)
        return;

    if (list == current)
        list = current->mNext;

    if (current->mNext != nullptr)
        (current->mNext)->mPrev = current->mPrev;

    if (current->mPrev != nullptr)
        (current->mPrev)->mNext = current->mNext;

    delete current;
    return;
}

void Doublelinklist::bubbleSort() {
    bool swapped;
    Node* ptr1 = new Node();
    Node* lastptr = new Node();
    lastptr = nullptr;

    if (list == nullptr)
        return;

    do
    {
        swapped = false;
        ptr1 = list;

        while (ptr1->mNext != nullptr)
        {
            if (ptr1->mStudent.getId() > (ptr1->mNext)->mStudent.getId())
            {
                Swap(ptr1, ptr1->mNext);
                swapped = true;
            }
            ptr1 = ptr1->mNext;
        }
        lastptr = ptr1;
    }     while (swapped);
}
// swap data of student not swap node
void Doublelinklist::Swap(Node*& nodeA, Node*& nodeB) {
    Node* temp = new Node();
    temp->mStudent = nodeA->mStudent;
    nodeA->mStudent = nodeB->mStudent;
    nodeB->mStudent = temp->mStudent;
}
void readStudentFromFile(const string& filename, Doublelinklist*& list) {

    ifstream fileToRead;
    fileToRead.open(filename, ios_base::in);

    while (!fileToRead.eof())
    {
        Student temp;
        temp.readStudent(fileToRead);
        list->Push_back(temp);
    }
    fileToRead.close();
}

void Doublelinklist::saveStudentToFile(const string& filename) {

    ofstream fileToWrite;
    fileToWrite.open(filename, ios_base::out);
    Node* readlist = new Node();
    readlist = list;
    if (readlist == nullptr)
    {
        fileToWrite << "No Data of Student !";
        return;
    }
    while (readlist != nullptr) {
        fileToWrite << readlist->mStudent.getId() << "," << readlist->mStudent.getName() << "," << readlist->mStudent.getDateOfBirth() << "," << readlist->mStudent.getClass() << endl;
        readlist = readlist->mNext;
    }
    fileToWrite.close();
}

int main()
{
    Student* st1 = new Student(100000, "Van Hau", "11/1/1995", "classC");
    Student* st2 = new Student(100001, "Quang Hai", "12/2/1995", "classC");
    Student* st3 = new Student(101000, "Tien Linh", "13/3/1995", "classC");
    Doublelinklist* list1 = new Doublelinklist();
    readStudentFromFile("input.txt", list1);
    list1->Print();
    list1->Push_back(*st1);
    list1->Push_back(*st2);
    list1->Push_front(*st3);
    cout << "================" << endl;
    cout << "List after insert and delete student : " << endl;
    list1->Remove(100111); // delete Student tien dat
    list1->Print();
    cout << "================" << endl;
    cout << "List after sort Id of student : " << endl;
    list1->bubbleSort();
    list1->Print();
    list1->saveStudentToFile("output.txt");

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
