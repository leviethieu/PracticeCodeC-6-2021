#include <iostream>
#include <string>

using namespace std;

class Student{
    private:
        string mName;
        int mId;            //Student ID is unique and has the form 1*****

    public:
        Student() : mName{""}, mId{0}{};
        Student(string name , int id) : mName{name} , mId{id} {} ;
        ~Student(){};
        string getName(){
            return mName;
        }
        int getId(){ 
            return mId;
        }
        Student(const Student &other){
            this->mName = other.mName;
            this->mId   = other.mId;
        }
        Student operator=(const Student &rhs){
            this->mName = rhs.mName;
            this->mId   = rhs.mId;
            return *this;
        }
};

//create node of double linked list
class Node{
    friend class Doublelinklist;

    private: 
        Student mStudent;
        Node *mNext;
        Node *mPrev;

    public:
        Node() : mNext {nullptr}, mPrev{nullptr} {};
        Node(Student student) : mStudent{student}, mNext {nullptr}, mPrev{nullptr} {};
        ~Node(){};

};


class Doublelinklist {
    private:
        Node *list; 
    public:
        Doublelinklist() : list{nullptr} {}
        void Push_back(const Student &student);
        void Push_front(const Student &student);
        void Insert(const Student &student,const int pos);
        void Print();
        void Search(const string &name);
        void Search(const int &Id);
        void Remove(const int &Id);

        // function of exam2
        void bubbleSort();
        void Swap(Node *&nodeA ,Node *&nodeB);

        //function of exam3
        Node* middle(Node* Nodestart, Node* Nodelast);
        Node* binarySearch(const int &Id);

};
void Doublelinklist::Push_back( const Student &student){
    
    Node *newNode = new Node();
    Node *lastNode = list;

    newNode->mStudent = student;
    newNode->mNext = nullptr;

    if(list == nullptr){
        newNode->mPrev = nullptr;
        list = newNode;
        return;
    }

    while (lastNode->mNext != nullptr){
        lastNode = lastNode->mNext;
    }

    lastNode->mNext = newNode;

    newNode->mPrev = lastNode;
}
void Doublelinklist::Push_front( const Student &student){

    Node *newNode = new Node();

    newNode->mStudent = student;

    newNode->mNext = list;
    newNode->mPrev = nullptr;

    if(list != nullptr){
        list->mPrev = newNode; 
    }
    list = newNode; 
}

void Doublelinklist::Print(){
    Node *readlist = new Node();
    readlist = list; 
    while (readlist != nullptr){
        cout << "Name of Student : " << readlist->mStudent.getName() << " ---" << " Id of Student : " << readlist->mStudent.getId() << endl;
        readlist = readlist->mNext;
    }
}
void Doublelinklist::Search(const int &Id){
    Node *readlist = new Node();
    readlist = list;
    int count = 0;
    while (readlist != nullptr){
        if(readlist->mStudent.getId() == Id){
            cout << "Name of Student : " << readlist->mStudent.getName() << " ---" << " Id of Student : " << readlist->mStudent.getId() << endl;
            count++;
        }
        readlist = readlist->mNext;
    }
    if(count == 0){
        cout << "No suitable students !" << endl;
    }
}
void Doublelinklist::Search(const string &name){
    Node *readlist = new Node();
    readlist = list;
    int count = 0;
    while (readlist != nullptr){
        if(readlist->mStudent.getName() == name){
            cout << "Name of Student : " << readlist->mStudent.getName() << " ---" << " Id of Student : " << readlist->mStudent.getId() << endl;
            count++;
        }
        readlist = readlist->mNext;
    }
    if(count == 0){
        cout << "No suitable students !" << endl;
    }
}
void Doublelinklist::Remove(const int &Id){

    Node *current = new Node();
    current = list;
    int count = 0;

    while (current != nullptr){
        if(current->mStudent.getId() == Id){
            count++;
            break;
        }
       current = current->mNext;
    }

    if(count == 0){
        cout <<"No suitable students for delete !" << endl;
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

void Doublelinklist::bubbleSort(){
     bool swapped;
     Node *ptr1 = new Node();
     Node *lastptr = new Node();
     lastptr = nullptr;

    /* Checking for empty list */
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
    }
    while (swapped);
}

// swap data of student not swap node
void Doublelinklist::Swap(Node *&nodeA ,Node *&nodeB){
    Node* temp = new Node();
    temp->mStudent  = nodeA->mStudent;
    nodeA->mStudent = nodeB->mStudent;
    nodeB->mStudent = temp->mStudent;
}
// find node middle for binary search
Node* Doublelinklist::middle(Node* start, Node* last)
{
    if (start == nullptr)
        return nullptr;

    // tao 2 node nodeslow jump 1  thi node fast jump 2 => node fast to last  => node slow to mid 
    Node* Nodejumpslow = new Node();
    Node* Nodejumpfast = new Node();

    Nodejumpslow = start;
    Nodejumpfast = start -> mNext;
 
    while (Nodejumpfast != last)
    {
        Nodejumpfast = Nodejumpfast -> mNext;
        if (Nodejumpfast != last)
        {
            Nodejumpslow = Nodejumpslow -> mNext;
            Nodejumpfast = Nodejumpfast -> mNext;
        }
    }
    // return node middle is node slow
    return Nodejumpslow;
}
Node* Doublelinklist::binarySearch (const int &Id)
{
    Node* start = list;
    Node* last  = nullptr;
 
    do
    {
        // Find middle
        Node* mid = middle(start, last);
 
        // If middle is empty
        if (mid == nullptr)
            return nullptr;
 
        // If value is present at middle
        if (mid->mStudent.getId() == Id)
            return mid;
 
        // If value is more than mid
        else if (mid->mStudent.getId() < Id)
            start = mid->mNext;
 
        // If the value is less than mid.
        else
            last = mid;
 
    } while (last == nullptr || last != start);
 
    // value not present
    return nullptr;
}

bool checkFullName(const string& fullName)
{
    for (unsigned int i = 0; i < fullName.length(); ++i)
    {
        if (!((fullName[i] >= 65 && fullName[i] <= 90) || (fullName[i] >= 97 && fullName[i] <= 122) || fullName[i] == 32))
        {
            return false;
        }
    }
    return true;
}
//Student ID is unique and has the form 1xxxxx
bool checkId(const int &id){
    if(id <200000 && id > 99999){
        return true;
    } return false;
}
int main()
{   
    int var;
    Student *st1 = new Student("Marry", 100010);
    Student *st2 = new Student("Henry", 102100);
    Student *st3 = new Student("Lucy", 130098);
    Student *st4 = new Student("Luke", 112000);
    Student *st5 = new Student("Mike", 100500);
    Doublelinklist *list1 = new Doublelinklist();
    list1->Push_back(*st1);
    list1->Push_back(*st2);
    list1->Push_back(*st3);
    list1->Push_back(*st4);
    list1->Push_back(*st5);
    do {
		system("cls");
		cout << "    The application uses double linkslist to manage students    " << endl;
		cout << "------------------------------------------" << endl;
		cout << "1.Add student to links list." << endl;
		cout << "2.Search for students by Student ID ." << endl;
		cout << "3.Search students by student name ." << endl;
		cout << "4.Print the list of students to the console ." << endl;
		cout << "0.Exit application ." << endl;
		cout << "Select the action you want to perform : ";cin >> var;
        while(cin.fail()) {
        cout << "Error ! Reselect : " << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> var;
        }
		cout << "------------------------------------------" << endl;
		switch (var)
		{
		case 1:
		{
			cout << "1.Add student to links list." << endl;
            string name;
            do{ 
                cout << "Enter Name of student" << endl;
                getline(cin,name);
            }
            while(!checkFullName(name));
            int id;
            cin >> id;
            while(cin.fail() == false && checkId(id) == false) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> id;
            }
			system("pause");
			break;
		}
		case 2:
		{   
			
			system("pause");
			break;
		}
		case 3:
		{
			
			system("pause");
			break;
		}

		case 4:
		{   
			
			system("pause");
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			cout << "You choose wrong. May I choose again " << endl;
			break;
		}

		}



	} while (var != 0);
}
