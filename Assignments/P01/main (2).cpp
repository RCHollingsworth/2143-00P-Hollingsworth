/***********************************************
* Author:    Professor Griffin
* Commentor: Robert Hollingsworth
* Email :    roberthollingsowrthcca@gmail.com
* Label:     Program 01
* Title:     Add clean comments to given code
* Course:    CMPS 2143
* Semester:  Spring 2023
*
* Description: This program assignment was to create a linked list based vector class that has a 
* variety of functionality in terms what can be added, subtracted, searched, and initialized. The 
* point of the program was to show that we have the knowledge to be able to more in depth use 
* classes as well as show our comfterability with manipulating data sets using vector linked 
* lists.  Below are the files I used.
*
* Files:
* main.cpp  : driver program
* input.dat : input file
* text.out  : output file
***********************************************/
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ofstream ofile;
ifstream infile;
/**
* LLVector
*
* Description:
*       This class is establishing a vector linked list that holds values
*       and can be manipulated by functions inside of the class either by 
*       initializing or actually changing the data.
*
* Private Methods:
*       A size value of type integer for keeping the size of the list
*       A Node of type struct that includes a vaule of type integer, 
*       a pointer of that points to the next value, and another pointer 
*       that be used to traverse data in reverse.
*       An initializer that initializes Node to 0 and nullptr
*       An initializer that initializes Node to a value
*       The pointers for the begining and end of the list
*       
* Public Methods:
*       A default constructor that initializes LLVector to 0 and nullptr
*       A constructor that initializes LLVector to be used by arrays
*       when one is passed in
*       A constructor that initializes LLVector to be used by files
*       when one is passed in
*       A void function pushRear that pushes values to the end of a list
*       A void function pushRear that pushes other lists to the end of a list
*       A void function pushFront that pushes values to the front of a list
*       A void function pushFront that pushes other lists to the front of a list
*       A void function printLL that prints a list out to the console and an output file
*       A void function pussARR that pushes an array onto the back of a list
*       A void function pushPos that pushes a value at a certain position
*       A void function popPos that pops a value at a certain position
*       An integer function popRear that pops a value off of the rear of a list
*       An integer function popFront that pops a value off of the front of a list
*       An integer function findPos that finds the location position of a value on a list
*
* Usage:
*       The following class is used by creating 
*/
class LLVector 
{
private:
  int size;
  struct Node 
  {
    int value;
    Node *next;
    Node *reverse;

    Node() 
    {
      value = 0;
      next = nullptr;
      reverse = nullptr;
    }

    Node(int x) 
    {
      value = x;
      next = nullptr;
      reverse = nullptr;
    }
  };
  Node *start;
  Node *end;

public:
  LLVector() 
  {
    start = nullptr;
    size = 0;
  }

  LLVector(int arr[], int size)
  {
    start = nullptr;
    this->size = 0;
    passARR(arr, size);
  }

  LLVector(string infile) 
  {
    int read;
    start = nullptr;
    this->size = 0;
    ifstream file(infile);
    while (file >> read) 
    {
      pushRear(read);
    }
  }

  LLVector(const vector<int> &vector) 
  {
    start = nullptr;
    this->size = 0;
    for (int value : vector) 
    {
      pushRear(value);
    }
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
  void pushRear(int a) 
  {
    Node *travel = new Node(a);
    if (start == nullptr)
      start = end = travel;
    else 
    {
      end->next = travel;
      travel->reverse = end;
      end = travel;
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
  void pushRear(LLVector vector)
  {
    Node *travel = vector.start;
    while (travel != nullptr) 
    {
      pushRear(travel->value);
      travel = travel->next;
      ;
    }
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
  void pushFront(int a) 
  {
    Node *travel = new Node(a);
    if (start == nullptr)
      start = end = travel;
    else 
    {
      travel->next = start;
      start = travel;
    }
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
  void pushFront(LLVector vector) 
  {
    Node *travel = vector.end;
    while (travel != nullptr) 
    {
      pushFront(travel->value);
      travel = travel->reverse;
    }
  }

  void printLL() 
  {
    Node *travel = start;
    while (travel != nullptr) 
    {
      cout << travel->value;
      ofile << travel->value;

      if (travel->next != nullptr)
      {
        cout << "->";
        ofile << "->";
      }
      travel = travel->next;
    }
    cout << endl;
    ofile << endl;
  }
/**
* Public: passARR
* 
* Description:
*      This function adds an array to the rear of a list
*      that has used the constructor LLVector (arr,value)
* Params:
*      - This function passes in an array of integers 
*      - It also passes in an integer size which is the size 
*        of the array being passed in
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void passARR(int arr[], int size) 
  {
    for (int i = 0; i < size; i++) 
    {
      pushRear(arr[i]);
    }
  }
/**
* Public: pushPos
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
*      - This function is void and returns nothing
*
*/
  void pushPos(int loc, int val) 
  {
    int count = 0;
    Node *travel = start;
    if (loc == 0) 
    {
      Node *temp = new Node;
      temp->value = val;
      temp->next = start;
      start = temp;
    } 
    else 
    {
      while (travel->next != nullptr) 
      {
        count++;
        if (count == loc)
        {
          Node *newNode = new Node;
          newNode->value = val;
          newNode->next = travel->next;
          travel->next = newNode;
          break;
        }
        travel = travel->next;
      }
    }
  }
/**
* Public: popPos
* 
* Description:
*      This function subtratcs a value from the specified location
*      on a list.
* Params:
*      - This function passes in an location which is an integer
*        marking the location a person wants a value removed at
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void popPos(int loc) 
  {
    int count = 0;
    Node *travel = start;
    if (loc == 0) 
    {
      start = start->next;
      delete travel;
    } 
    else 
    {
      while (travel->next != nullptr) 
      {
        count++;
        if (count == loc)
        {
          Node *temp = travel->next->next;
          delete travel->next;
          travel->next = temp;
          break;
        }
        travel = travel->next;
      }
    }
  }
/**
* Public: popRear
* 
* Description:
*      This function subtacts elements from the rear of a list.
* 
* Params:
*      - This function does not pass any parameters in.
* 
* Returns:
*      - This function is returns the value popped from the list
*        of type integer value.
*
*/
  int popRear() 
  {
    int popped = 0;
    if (start == nullptr)
      cout << "Cannot pop an empty list\n";

    if (start->next == nullptr)
    {
      popped = start->value;
      delete start;
      start = nullptr;
    } 
    else 
    {
      Node *travel = start;
      while (travel->next->next != nullptr) 
      {
        travel = travel->next;
      }
      popped = travel->next->value;
      delete travel->next;
      travel->next = nullptr;
    }
    return popped;
  }
/**
* Public: popFront
* 
* Description:
*      This function subtacts elements from the front of a list.
* 
* Params:
*      - This function does not pass any parameters in.
* 
* Returns:
*      - This function is returns the value popped from the list
*        of type integer value
*
*/
  int popFront() 
  {
    int popped;
    if (start == nullptr)
      cout << "Cannot pop an empty list\n";

    if (start->next == nullptr) 
    {
      popped = start->value;
      delete start;
      start = nullptr;
    } 
    else
    {
      popped = start->value;
      Node *temp = start->next;
      delete start;
      start = temp;
    }
    return popped;
  }
/**
* Public: findPos
* 
* Description:
*      This function locates a what position a value is at.
* 
* Params:
*      - This function passes in the value of type integer
*        that a person is trying to locate in a list.
* 
* Returns:
*      - This function is returns the location of the value
*        searched for as a type integer
*
*/
  int findPos(int val) 
  {
    int pos = 0;
    Node *travel = start;
    while (travel != nullptr) 
    {
      if (travel->value == val)
      {
        cout << val << " Is at position: " << pos << endl;
        ofile << val << " Is at position: " << pos << endl;
        return pos;
      }
      pos++;
      travel = travel->next;
    }
    return -1;
  }
};

int main() 
{
  infile.open("infile.dat");
  ofile.open("test.out");
  cout << "Robert Hollingsworth\n";
  cout << "CMPS 2413-201\n";
  cout << "2/7/2023\n";
  ofile << "Robert Hollingsworth\n";
  ofile << "CMPS 2413-201\n";
  ofile << "2/7/2023\n";
int x = 0;

LLVector v1;
v1.pushFront(18);
v1.pushFront(20);
v1.pushFront(25);
v1.pushRear(18);
v1.pushRear(20);
v1.pushRear(25);
v1.printLL();
// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};
LLVector v2(A,5);
v2.printLL();
// [11, 25, 33, 47, 51]

v2.pushFront(9);
//v2.inOrderPush(27);
v2.pushRear(63);
v2.printLL();
// [9, 11, 25, 33, 47, 51, 63]

v1.pushRear(v2);
v1.printLL();
// [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

x = v1.popFront();
x = v1.popFront();
x = v1.popFront();
v1.printLL();
// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
cout<<x<<endl;
// 18

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.printLL();
// [18, 20, 25, 9, 11, 25, 27, 33]
cout<<x<<endl;
// 47

v2.popPos(3);
v2.printLL();
// [9, 11, 25, 33, 47, 51, 63]
// 27

x = v2.findPos(51);
// 5

x = v2.findPos(99);
cout<<x<<endl;
// -1

LLVector v3(v1);
v3.printLL();
// [18, 20, 25, 9, 11, 25, 27, 33]

v3.pushFront(v2);
v3.printLL();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

LLVector v4("input.dat");
v4.pushRear(v3);
v4.printLL();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
  infile.close();
  ofile.close();
}