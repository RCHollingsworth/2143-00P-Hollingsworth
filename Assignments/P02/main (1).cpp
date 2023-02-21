/***********************************************
* Author:    Robert Hollingsworth
* Professor: Griffin
* Email :    roberthollingsowrthcca@gmail.com
* Label:     Program 02
* Title:     Add overrided operators to Vector class
* Course:    CMPS 2143
* Semester:  Spring 2023
*
* Description: This program takes an already established vectored link list and uses 
* overrided operators to be able to more easily manipulate the data. What this means 
* from a potential user perspective is being able to do basic arithmetic between integer
* data sets of any size. This includes integer data sets that are not the same size.
*
*
* Files:
* main.cpp  : driver program
* text.out  : output.txt (created by the program)
***********************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000  // infinity

using namespace std;

// Node struct for creating and initializing Nodes
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
/**
* MyVector
*
* Description:
*       This class is establishing a vector linked list that holds values
*       and can be manipulated by functions inside of the class either by 
*       initializing or actually changing the data. It then also establishes
*       override operators in order to be able to easily manipulate the linked 
*       list created. The override operators created are ones that use basic 
*       arithmetic such as +,-,/, and * along with the equality == and assignment =
*       operators to be able to store lists inside of each other.
*
* Private Methods:
*       A Node pointer 'head' that points to the front of the list
*       A Node pointer 'tail' that points to the rear of the list
*       An output file holder declared as static since it isn't changing
*       A size int 'size' that holds the size of the list
*       A string 'filename' that takes in the filename
*       A boolean 'sorted' that gets utilized for ordered sort
*       A function '_inorderPush' which takes in an int and pushes it onto
*       the list in descending or ascending order
*       
* Public Methods:
*       An override operator [] which allows us to find a value at an index
*       A default constructor for MyVector that uses the init function
*       A constructor for creating a MyVector with an array, 
*       which also needs the size of that array
*       A constructor that creates a MyVector using a file
*       A constructor that creates a MyVector using another member of the MyVector class
*       A void function init that minimizes code that would have been in the constructors
*       A void function inorderPush which sorts the list in asc or desc order and allows us
*       to use the private method _inorderPush
*       A void function sortList that sorts this list from smallest to largest
*       A void function pushFront which pushes value to the front of the list
*       A void overload of function pushFront that pushes lists to the front of lists
*       A void overload of the function pushRear pushes lists to the rear of lists
*       A boolean function pushAt which pushes a value at a specific location
*       A void function pushRear which pushes value onto the rear of a list
*       An override of the operator << ostream that allows to cout MyVectors
*       An override of the operator + that allows to add MyVectors
*       An override of the operator - that allows to subtract MyVectors
*       An override of the operator * that allows to multiply MyVectors
*       An override of the operator / that allows to divide MyVectors
*       An override of the operator << ofstream that allows to fout MyVectors
*
* Usage:
*       The following class is used by calling it to create a vectored linked lists in main
*       and asking it to manipulate those lists based on certain operations in main
*/
class MyVector {
private:
    Node*           head;  
    Node*           tail;
    static ofstream fout;
    int             size;
    string          fileName;
    bool            sorted;

/**
* Private: _inorderPush
* 
* Description:
*      This function creates a new node of the desired value and adds it to the
*      list in ascending or descending order based on the later function that gets
*      called, named 'inorderPush'
* 
* Params:
*      - This function passes in an integer that gets pushed onto the list
*        in the other established
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void _inorderPush(int x) {
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size
    }

    int _getSize() const {
      int count = 0;
      Node *current = head;
      while (current) {
        count++;
        current = current->next;
      }
      return count;
    }

public:
/**
* Public: override operator[]
* 
* Description:
*      This overide operator is one that overides [] to be able to
*      output a variable of our vector link list at a certain postion.
*      For example 'cout << v1[2] << endl;'
* 
* Params:
*      - This function passes in a of type integer that is the location 
*        of where the desired data is inside of the list. Similar to an 
*        array. We call this int index because it is the index which the
*        value is located at.
*
* 
* Returns:
*      - This override returns an int which is the value at the desired index
*
*/
  int& operator[](int index) {
    if (index < 0 || index >= size) {
      // Handles any out-of-bounds index
      throw out_of_range("Index out of range");
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

    int getSize() const {
        return _getSize();
    }

//Default constructor for MyVector class uses the init function to set everything to 0
    MyVector() {
        init();
    }

//Constructor for creating a MyVector with an array, which also needs the size of that array
//Utilizes the init and pushRear functions below
    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

//Constructor for creating a MyVector with a file
//Utilizes the init and pushRear functions below
    MyVector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

//Constructor for creating a MyVector with another MyVector 
//Utilizes the init and pushRear functions below
    MyVector(const MyVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

/**
* Public: init
* 
* Description:
*      This function takes alot of the similar code that would have been
*      used in all of the constructors and stores it here to save space.
*      It initializes a linked list to 0 and Null
* 
* Params:
*      This function does not pass in anything, but instead assigns 
*      already established variables and pointers for initialization
*
* 
* Returns:
*      - This function returns nothing since it is void
*
*/
    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
        sorted = 0;
    }

/**
* Public: inorderPush
* 
* Description:
*      This function uses other methods inside of out class in order
*      to sort and push data onto our list in ascending or descending order
*      It also allows us to use the private method _inorderPush
* 
* Params:
*      This function takes in an int value that we want to put in a certain order
*      in our list. If the list is already sorted or empty, it checks for it and push the 
*      int into the right spot.
*
* 
* Returns:
*      - This function returns nothing since it is void
*
*/
    void inorderPush(int x) {
        if (!sorted) {
            sortList();
        }

        if (!head) {
            pushFront(x);  // call push front for empty list (or pushRear would work) 
          return;
        } else if (x < head->data) {
            pushFront(x);  // call push front if x is less than head
        } else if (x > tail->data) {
            pushRear(x);  // call push rear if x > tail
        } else {
            _inorderPush(x);  // call private version of push in order
        }
    }

/**
* Public: sortList
* 
* Description:
*      This function sorts the list from smallest value to largest value
* 
* Params:
*      This function takes in no parameters since it is manipulating a current list
*      with pointers already established
*
* 
* Returns:
*      - This function returns nothing since it is void
*
*/  
    void sortList() {
        Node* newFront = head;
        while (newFront->next) {
            Node* smallest = newFront;
            Node* current = newFront;
            int   minimum = INF;
            while (current) {
                if (current->data < minimum) {
                    smallest = current;
                    minimum = current->data;
                }
                current = current->next;
            }
            smallest->data = newFront->data;
            newFront->data = minimum;
            newFront = newFront->next;
        }
        sorted = true;
    }

/**
* Public: pushFront
* 
* Description:
*      This function add elements to the front of a list
* 
* Params:
*      - This function passes in a of type integer that gets pushed 
*        onto a list in the front
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr;
            // otherwise adjust head pointer
        } else {
            tempPtr->next = head;
            head = tempPtr;
        }
        size++;
    }

/**
* Public: pushFront
* 
* Description:
*      This function add a list to the front of a list.
*      It gave me some issues without the pointer reverse.
* 
* Params:
*      - This function passes in an previously created list
*        of type LLVector that gets pushed onto the front of 
*        another list. 
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void pushFront(const MyVector& other) {
        Node* otherPtr = other.head;           // get copy of other lists head
        int*  tempData = new int[other.size];  // allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i;
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]);
        }
    }

/**
* Public: pushRear
* 
* Description:
*      This function add a list to the rear of a list
* 
* Params:
*      - This function passes in an previously created list
*        of type LLVector that gets pushed onto the rear of 
*        another list
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

/**
* Public: pushAt
* 
* Description:
*      This function adds a value to the specified location
*      on a list.
* Params:
*      - This function passes in an location which is an integer
*      - It also passes in an integer val which is the value 
*        that a person wants to insert at that location
* 
* Returns:
*      - This function is a boolean returns true once the value has been added 
*        at that location or returns false if it will not fit in the size
*
*/
    bool pushAt(int i, int x) {
        if(i >= size){
            return false;
        }
        
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i>0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size 
        return true;
    }

/**
* Public: pushRear
* 
* Description:
*      This function add elements to the rear of a list
* 
* Params:
*      - This function passes in a of type integer that gets pushed 
*        onto a list in the rear
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        } else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

/**
* Public: override ostream
* 
* Description:
*      This override operator is one that ostream so that the object
*      MyVector can be cout
*      For example 'cout << v1;'
* 
* Params:
*      - This function passes in an output variable and a MyVector object
*        that we want to print to the console.
*
* 
* Returns:
*      - This function returns the output variable that prints to the console
*
*/
    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << "->";
            }
            temp = temp->next;  // move to next Node
        }
        os << endl;
        return os;
    }

/**
* Public: override +operator
* 
* Description:
*      This override operator is one allows MyVectors to be added 
*      together
* 
* Params:
*      - This function passes in a MyVector which gets added to another
*
* 
* Returns:
*      - This function returns temp as the final product
*
*/
  MyVector operator+(const MyVector &other) {
    MyVector temp;

    Node *current = head;
    while (current) {
      temp.pushRear(current->data);
      current = current->next;
    }

    current = other.head;
    while (current) {
      temp.pushRear(current->data);
      current = current->next;
    }

    return temp;
  }

/**
* Public: override -operator
* 
* Description:
*      This override operator is one allows MyVectors to be subtracted
*      together. It also utilizes the subtract function to make it 
*      personally easier as opposed to the way we did in class
* 
* Params:
*      - This function passes in a MyVector which gets subtracted 
*        from another
*
* 
* Returns:
*      - This function returns temp as the final product
*
*/
  MyVector operator-(const MyVector &other) const {
    MyVector temp;

    Node *current = head;
    while (current) {
      temp.pushRear(current->data);
      current = current->next;
    }

    current = other.head;
    while (current) {
      temp.subtract(current->data);
      current = current->next;
    }

    return temp;
  }

/**
* Public: subtract
* 
* Description:
*      This function makes the override operator - a little bit cleaner
*      While we did it differently and probably more efficiently in class
*      I preferred this method
* 
* Params:
*      - This function passes in an int value that gets checked against 
*        the current->data
* 
* Returns:
*      - This function is void and returns nothing since it
*        is changing pointers
*
*/
  void subtract(int value) {
    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr && current->data != value) {
      prev = current;
      current = current->next;
    }

    if (current != nullptr) {
      if (prev == nullptr) {
        head = current->next;
      } else {
        prev->next = current->next;
      }
//Updating the tail
      if (current == tail) {
        tail = prev;
      }

      delete current;
      size--;
    }
  }

/**
* Public: override *operator
* 
* Description:
*      This override operator is one allows MyVectors to be multiplied 
*      together
* 
* Params:
*      - This function passes in a MyVector which gets multiplied to another
*
* 
* Returns:
*      - This function returns temp as the final product
*
*/
MyVector operator* (const MyVector& other) const {
  MyVector temp;
  Node *current = head;
  Node *current_ = other.head;
  
  // Determine the length of the shorter vector
  int length = min(getSize(), other.getSize());
  
  // Multiply the values up to the length of the shorter vector
  for (int i = 0; i < length; i++) {
    temp.pushRear(current->data * current_->data);
    current = current->next;
    current_ = current_->next;
  }
  
  // If the current vector is longer, append the remaining values to the result
  while (current) {
    temp.pushRear(current->data);
    current = current->next;
  }
  
  // If the other vector is longer, append the remaining values to the result
  while (current_) {
    temp.pushRear(current_->data);
    current_ = current_->next;
  }
  
  return temp;
}

/**
* Public: override /operator
* 
* Description:
*      This override operator is one allows MyVectors to be divided 
*      by one another
* 
* Params:
*      - This function passes in a MyVector which gets divide by another
*
* 
* Returns:
*      - This function returns temp as the final product
*
*/
MyVector operator/ (const MyVector& other) const {
  MyVector temp;
  Node *current = head;
  Node *current_ = other.head;
  while (current && current_) {
    if (current_->data == 0) {
      temp.pushRear(0);
    } else {
      temp.pushRear(current->data / current_->data);
    }
    current = current->next;
    current_ = current_->next;
  }
  while (current) {
    temp.pushRear(current->data);
    current = current->next;
  }
  while (current_) {
    temp.pushRear(current_->data);
    current_ = current_->next;
  }
  return temp;
}

/**
* Public: override ofstream
* 
* Description:
*      This override operator is one that ofstream so that the object
*      MyVector can be fout
*      For example 'fout << v1;'
* 
* Params:
*      - This function passes in an output variable and a MyVector object
*        that we want to print to the output file.
*
* 
* Returns:
*      - This function returns the output variable that prints to the console
*
*/
  friend ofstream &operator<<(ofstream &of, const MyVector &rhs) {
    Node *temp = rhs.head; // temp pointer copies head

    while (temp) {

      of << temp->data; // print data from Node
      if (temp->next) {
        of << "->";
      }
      temp = temp->next; // move to next Node
    }
    of << endl;
    return of;
  }

/**
* Public: override =operator
* 
* Description:
*      This override operator is one allows MyVectors to be assigned 
*      the value of another MyVector 
* 
* Params:
*      - This function passes in a MyVector which gets reassigned
*
* 
* Returns:
*      - This function returns the MyVector we are copying the data from
*        and storing it in the one we want to assign to
*
*/
MyVector& operator=(const MyVector& other) {
  if (this == &other) {  // self assignment check
    return *this;
  }

  // Deletes current elements
  while (head) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;

  // Copies elements from other
  Node *otherCurrent = other.head;
  while (otherCurrent) {
    pushRear(otherCurrent->data);
    otherCurrent = otherCurrent->next;
  }

  return *this;
}

/**
* Public: override ==operator
* 
* Description:
*      This override operator simply checks if two MyVectors are equal
* 
* Params:
*      - This function passes in a MyVector and compares it to another
*
* 
* Returns:
*      - This function returns true if the two are equal and false if they
*        are not
*
*/
bool operator==(const MyVector& other) const {
  if (getSize() != other.getSize()) {
    return false;
  }

  Node *current = head;
  Node *otherCurrent = other.head;
  while (current) {
    if (current->data != otherCurrent->data) {
      return false;
    }
    current = current->next;
    otherCurrent = otherCurrent->next;
  }

  return true;
}

//This is the clean up crew and deletes the memory that has been allocated
    ~MyVector() {
        Node* curr = head;
        Node* prev = head;

        while(curr){
            prev = curr;
            curr = curr->next;
            //cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }



};

int main() {
ofstream fout;
fout.open("output.txt");
cout << "Robert Hollingsworth\n";
fout << "Robert Hollingsworth\n";
cout << "CMPS 2413-201\n";
fout << "CMPS 2413-201\n";
cout << "2-21-2023\n";
fout << "2-21-2023\n";
cout << "Console Output:\n";
fout << "File Output:\n";
int a1[] = { 1, 2, 3, 4, 5 };
int a2[] = { 10, 20, 30 };

MyVector v1(a1,5);
MyVector v2(a2,3);

cout << v1[2] << endl;
// writes out 3

v1[4] = 9;
// v1 now = [1,2,3,4,9]

cout << v1 << endl;
// writes out [1,2,3,4,9] to console.

fout << v1 << endl;
// writes out [1,2,3,4,9] to your output file.

MyVector v3 = v1 + v2;
cout << v3 << endl;
// writes out [11,22,33,4,9] to console.

v3 = v1 - v2;
cout << v3 << endl;
// writes out [-9,-18,-27,4,9] to console.

v3 = v2 - v1;
cout << v3 << endl;
// writes out [9,18,27,4,9] to console.

v3 = v2 * v1;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

v3 = v1 * v2;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

v3 = v1 / v2;
cout << v3 << endl;
// writes out [0,0,0,4,9] to console.

v3 = v2 / v1;
cout << v3 << endl;
// writes out [10,10,10,4,9] to console.

if(v2 == v1)
  cout << 1 << endl;
else
  cout << 0 << endl;
// writes 0 to console (false) .

MyVector v4 = v1;
if(v4 == v1)
  cout << 1 << endl;
else
  cout << 0 << endl;
// writes 1 to console (true) 
  
}