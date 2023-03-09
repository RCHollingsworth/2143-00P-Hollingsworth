/***********************************************
* Author:    Robert Hollingsworth
* Professor: Griffin
* Email :    roberthollingsowrthcca@gmail.com
* Label:     Program 03
* Title:     GraphViz Class
* Course:    CMPS 2143
* Semester:  Spring 2023
*
* Description: The purpose of this program is to create code
* we can take and put into GraphViz. In using that code we 
* should be able to generate a linked list, doubly linked list,
* and a binary search tree. We do this by adding elements to
* data structures using creative class methods.
*
* Files:
* main.cpp  : driver program
* text.out  : test.out (created by the program)
***********************************************/
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
/**
* class: Attr
*
* Description: This class is the parent class for the 
* classes Node, Edge, and Graph, because each of those
* classes are ones that contain attributes. The main
* function of this class is to hold a map of strings
* used across the three classes stated before, as well
* as similar code that gets used in those classes methods.
* There is also an overload operator to print out all of the
* attributes in the same format.
*
* Private Methods:
*       A map that holds a key valued pair, both in the pair
*       being the data type string.
*
* Public Methods:
*       A default constructor that does nothing but
*       make the system happy
*       An overloaded operator of cout that allows us
*       to print out all attributes the same way
*       A void function that allows us to add attributes
*       to the map created
* Usage:
*       The following class is used to reduce the amount of
*       code across the board by grouping all of the similar
*       qualities of attributes togethor. It also allows all
*       attributes to be printed out the same.
*/
class Attr
{
protected:
map<string, string> att;
public:
  Attr() {}
//overloading the ostream operator to print all attributes the same
  friend ostream &operator<<(ostream &cout, Attr &e) {

    cout << "[";

    int i = 0;
    for (auto const &x : e.att) {
      cout << x.first << "="
         << "\"" << x.second << "\"";

      if (i < e.att.size() - 1) {
        cout << ", ";
      }
      i++;
    }
    cout << "]";

    return cout;
  }
/**
* Public: addAttr
* 
* Description:
*      This function adds an attribute by taking in a key
*      and a value that gets passed into the attribute map
* 
* Params:
*      - This function passes in an int key and an int val
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void addAttr(string key, string val) { att[key] = val; }
/**
* Public: addAttrs
* 
* Description:
*      This function adds attributes by taking in a map
*      of srings and storing it in the attribute map
* 
* Params:
*      - This function passes in a map of strings
* 
* Returns:
*      - This function is void and returns nothing
*
*/
    void addAttrs(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }
};
/**
* class: Edge
*
* Description: This is the class that establishes the 
* edge object in GraphViz, which is the object that connects
* togethor nodes. In this class we create an edge id, create
* different ways to construct an edge, and make a function
* that allows us to retrive the edge id.
*
* Private Methods:
*       A struct that holds two ints which
*       establishes the edge id
*
* Public Methods:
*       A default constructor that initializes an edge
*       A constructor that takes in and assigns the start 
*       and end of an edge
*       A constructor that takes in a map of attributes
* Usage:
*       This class is used for creating and manipulating
*       edges through an edge id, which is a pair of values
*       that identifies where an edge starts and ends.
*/
class Edge:public Attr
{
private:
  struct eid {
  int start;
  int end;
  }edgeId;
public:
//Default constructor
  Edge()
  {
  edgeId = {0,0};
  att["color"] = "black";
  att["dir"] = "forward";
  att["arrowhead"] = "normal";
  att["arrowtail"] = "normal";
  att["style"] = "normal";
  att["weight"] = "0";
  }

  Edge(int start, int end) {
  edgeId = {start,end};
  att["color"] = "black";
  att["dir"] = "forward";
  att["arrowhead"] = "normal";
  att["arrowtail"] = "normal";
  att["style"] = "normal";
  att["weight"] = "0";
  }

  Edge(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }
/**
* Public: getEdgeId
* 
* Description:
*      This function is used to retrive the edge id
*      so that it can be printed in the printGraph function
* 
* Params:
*      - This function passes in no parameters
* 
* Returns:
*      - This function returns a struct which is the edge id
*
*/
  eid getEdgeId() const {
    return edgeId;
  }
};
/**
* class: Node
*
* Description: This is the class that establishes the 
* node object in GraphViz, which is the object that holds
* data. In this case that data is linked togethor by edges. 
*
* Private Methods:
*       An int that holds the node id
*
* Public Methods:
*       A default constructor that initializes a node with
*       its attributes
*       A constructor that takes in a map of attributes
*
* Usage:
*       This class is used for creating and manipulating
*       nodes through an node id, which is a value
*       that identifies a grouping of attributes to a piece
*       of data.
*/
class Node:public Attr
{
private:
int nodeid;
public:
//Default constructor
  Node()
  {
  att["label"] = "Node1";
  att["color"] = "black";
  att["shape"] = "box";
  att["style"] = "filled";
  att["width"] = "1.0";
  att["height"] = "1.0";
  
  }

  Node(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }
};
/**
* class: Graph
*
* Description: This is class, in similar fashion to
* the edge and nodes classes, holds the attribute and features
* associated with the graph in GraphViz. This includes the 
* background color, label, font size, ...etc.
*
* Private Methods:
*       None
*
* Public Methods:
*       A default constructor that initializes a graph with
*       its attributes
*       A constructor that takes in a map of attributes 
*
* Usage:
*       This class is used for creating and manipulating
*       graphs, which is the back drop of GraphViz.
*/
class Graph:public Attr
{
public:
//Default constructor
  Graph()
  {
  att["bgcolor"] = "white";
  att["label"] = "Program 3";
  att["fontname"] = "Arial";
  att["fontsize"] = "15";
  }

  Graph(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }
};
/**
* class: GraphViz
*
* Description: This is the class that establishes the 
* GraphViz output we want to generate, which is the collection
* of the Node, Edge, and Graph classes. It is the main substance
* of this program and has the most functionality.
*
* Private Methods:
*       An int that holds the node id
*       A struct that holds the Edge id
*       A vector that holds objects of type Node
*       A vector that holds objects of type Edge
*       A vector that holds objects of type Graph
*       A string that holds the graph shape
*       A string that holds the graph name
*
* Public Methods:
*       A default constructor that initializes a GraphViz with
*       a node id, an edge id, and a name
*       A constructor that assigns a name and shape to the
*       GraphViz object
*       An int function that adds default Nodes
*       An int function that adds Nodes by passing in an attribute
*       map
*       An void function that updates Nodes
*       An int function that adds default Edges
*       An void function that adds Edges with a start and end
*       An void function that updates Edges
*       An int function that adds default Graphs
*       An int function that updates Graphs
*       A void function that print everything out
*
* Usage:
*       This class is used for creating and manipulating
*       objects of type GraphViz through using the classes
*       Edge, Node, and Graph. Overall it creates the syntax
*       we end up taking and putting in GraphViz.
*/
class GraphViz
{
private:
int nodeId;
struct EdgeId_
    {
    int start_;
    int end_;
    } edgeId_;
vector<Node> Nodes;
vector<Edge> Edges;
vector<Graph> Graphs;
string gShape;
string gName;

public:
//Default constructor
GraphViz()
  {
  nodeId = 0;
  edgeId_ = {0,0};
  gName = "List";
  }

  GraphViz(string gname, string gshape) {
    edgeId_ = {0,0};
    nodeId = 0;
    gName = gname;
    gShape = gshape;
  }
/**
* Public: addNode
* 
* Description:
*      This function adds a Node by pushing a default Node
*      onto the vector of Nodes established in this class
* 
* Params:
*      - This function passes in no parameters
* 
* Returns:
*      - This function returns the vector size -1
*
*/
  int addNode() 
  {
    Nodes.push_back(Node());
    return Nodes.size() - 1;
  }
/**
* Public: addNode
* 
* Description:
*      This function adds a Node by pushing a map of strings
*      onto the vector of Nodes established in this class
* 
* Params:
*      - This function passes in a map of strings
* 
* Returns:
*      - This function returns the vector size -1
*
*/
  int addNode(map<string, string> atts) 
  {
    Nodes.push_back(Node(atts));

    return Nodes.size() - 1;
  }
/**
* Public: updateNode
* 
* Description:
*      This function updates an established Node by changing
*      a value at a specific id and key. 
* 
* Params:
*      - This function passes in an int which is an id of
*        the node we want to update, a string which is the key
*        and a string which is the value
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void updateNode(int id, string key, string value)
  {
    Nodes[id].addAttr(key, value);
  }
/**
* Public: addEdge
* 
* Description:
*      This function adds a Edge by pushing a default Edge
*      onto the vector of Edges established in this class
* 
* Params:
*      - This function passes in no parameters
* 
* Returns:
*      - This function returns the vector size -1
*
*/
  int addEdge() 
  {
    Edges.push_back(Edge());
    return Edges.size() - 1;
  }
/**
* Public: addEdge
* 
* Description:
*      This function adds a Edge by pushing a map of strings
*      onto the vector of Edges established in this class
* 
* Params:
*      - This function passes an int which is the start of an
*        edge and an int which is the end of an edge
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void addEdge(int start, int end) 
  { Edges.push_back(Edge(start, end)); 
    }
/**
* Public: updateEdge
* 
* Description:
*      This function updates an established Edge by changing
*      a value at a specific id and key. 
* 
* Params:
*      - This function passes in an int which is an id of
*        the edge we want to update, a string which is the key
*        and a string which is the value
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void updateEdge(int id, string key, string value) {
    Edges[id].addAttr(key, value);
  }
/**
* Public: addGraph
* 
* Description:
*      This function adds a Graph by pushing a default Graph
*      onto the vector of Graphs established in this class
* 
* Params:
*      - This function passes in no parameters
* 
* Returns:
*      - This function returns the vector size -1
*
*/
  int addGraph() 
  {
    Graphs.push_back(Graph());
    return Graphs.size() - 1;
  }
/**
* Public: updateGraph
* 
* Description:
*      This function updates an establish Graph by taking a
*      map of strings and adding those attributes onto graph
* 
* Params:
*      - This function passes in a map of strings which
*        hold the attribute qualities
* 
* Returns:
*      - This function returns the Graphs vector size -1
*
*/
  int updateGraph(map<string, string> atts) 
  {
    Graphs.push_back(Graph(atts));

    return Graphs.size() - 1;
  }
/**
* Public: printGraph
* 
* Description:
*      This function prints out the GraphViz class in the
*      syntax where we can take it and plug the output directly
*      into GraphViz
* 
* Params:
*      - This function passes the location of the file we want
*        to output to, and the graph name that we want to print out
* 
* Returns:
*      - This function is void and returns nothing
*
*/
  void printGraph(ofstream& fout, string graphName = "") 
  {
//Checking if the graph name is empty and
//Giving it a name if it is
    if (graphName.size() == 0)
      graphName = this->gName;
//Initial print out statements
    cout << "digraph " << gName << "\n{\n";
    fout << "digraph " << gName << "\n{\n";
    cout << "rankdir=LR\n";
    fout << "rankdir=LR\n";
//Looping over and printing out what is in Graphs
    for (int i = 0; i < Graphs.size(); i++) 
    {
    cout << "graph" << " " << Graphs[i] << endl;
    fout << "graph" << " " << Graphs[i] << endl;
    }
//Looping over and printing out what is in Nodes   
    for (int i = 0; i < Nodes.size(); i++) 
    {
    cout << i << " " << Nodes[i] << endl;
    fout << i << " " << Nodes[i] << endl;
    }
//Looping over and printing out what is in Edges
//Using getEdgeId to get the start and end of each edge
    for (int i = 0; i < Edges.size(); i++) {
    cout << Edges[i].getEdgeId().start << " -> " 
      << Edges[i].getEdgeId().end << Edges[i] << endl;
    fout << Edges[i].getEdgeId().start << " -> " 
      << Edges[i].getEdgeId().end << Edges[i] << endl;
  }
    cout << "}\n\n";
    fout << "}\n\n";
  }
};
int main()
{
//Creating 3 objects, one a linked list, one a doubly linked
//list, and finally the binary search tree
GraphViz G("LinkedList", "LL");
GraphViz D("DoublyLL", "DLL");
GraphViz B("BinaryST", "BST");
//Four Node Shapes
  map<string, string> Box;
  map<string, string> Folder;
  map<string, string> Egg;
  map<string, string> Record;
//Graph change
  map<string, string> Graph_;
//Adding random nodes, edges, and graph attributes
//through creating members of the attribute class
//and adding them to each list, as well as using
//update functions. 
  Attr A;
  Box["shape"] = "box";
  Box["color"] = "blue";
  Box["height"] = "3.0";
  Box["style"] = "filled";
  A.addAttrs(Box);
  int nodeId1 = G.addNode(Box);
  int nodeId2 = D.addNode(Box);
  int nodeId3 = B.addNode(Box);
  
  Folder["shape"] = "folder";
  Folder["color"] = "pink";
  Folder["height"] = "1.0";
  Folder["style"] = "filled";
  A.addAttrs(Folder);
  int nodeId4 = G.addNode(Folder);
  int nodeId5 = D.addNode(Folder);
  int nodeId6 = B.addNode(Folder);
  
  Egg["shape"] = "egg";
  Egg["color"] = "orange";
  Egg["height"] = "1.5";
  Egg["style"] = "filled";
  A.addAttrs(Egg);
  int nodeId7 = G.addNode(Egg);
  int nodeId8 = D.addNode(Egg);
  int nodeId9 = B.addNode(Egg);
  
  Record["shape"] = "record";
  Record["color"] = "red";
  Record["height"] = "2.0";
  Record["style"] = "filled";
  A.addAttrs(Record);
  int nodeId10 = G.addNode(Record);
  int nodeId11 = D.addNode(Record);
  int nodeId12 = B.addNode(Record);
  
  Graph_["fontsize"] = "20";
  Graph_["bgcolor"] = "yellow";
  A.addAttrs(Graph_);
  int graphId = G.updateGraph(Graph_);

  Graph_["fontsize"] = "15";
  Graph_["bgcolor"] = "pink";
  A.addAttrs(Graph_);
  int graphId2 = B.updateGraph(Graph_);


  G.addNode();
  G.addNode();
  G.addEdge(0,1);
  G.addEdge(1,2);
  G.addEdge(2,3);
  G.addEdge(3,4);
  G.addEdge(4,5);
  G.updateEdge(0,"arrowhead","dot");
  G.updateEdge(2,"arrowhead","icurve");
  G.updateEdge(3,"arrowhead","inv");
  G.updateEdge(4,"arrowhead","vee");
  G.updateEdge(0,"color","brown");
  G.updateEdge(2,"dir","none");
  
  D.addGraph();
  D.addEdge(0,1);
  D.addEdge(1,0);
  D.addEdge(1,2);
  D.addEdge(2,1);
  D.addEdge(2,3);
  D.addEdge(3,2);
  D.addEdge(3,4);
  D.addEdge(4,3);
  D.addEdge(4,5);
  D.addEdge(5,4);
  D.updateEdge(0,"arrowhead","dot");
  D.updateEdge(2,"arrowhead","icurve");
  D.updateEdge(3,"arrowhead","inv");
  D.updateEdge(4,"arrowhead","vee");
  D.updateEdge(0,"color","purple");
  D.updateEdge(2,"color","purple");
  D.updateEdge(2,"dir","back");
  D.updateEdge(3,"dir","none");

  B.addNode();
  B.addEdge();
  B.addEdge(0,1);
  B.addEdge(0,2);
  B.addEdge(1,3);
  B.addEdge(1,4);
  B.addEdge(2,5);
  B.addEdge(2,6);
  B.addEdge(5,7);
  B.updateEdge(0,"arrowhead","dot");
  B.updateEdge(2,"arrowhead","icurve");
  B.updateEdge(3,"arrowhead","inv");
  B.updateEdge(4,"arrowhead","vee");
  B.updateEdge(3,"color","red");
  B.updateEdge(3,"dir","none");
//Opening the file test.out to print out to
  ofstream fout("test.out");
  fout << "Robert Hollingsworth\n";
  fout << "3/9/2023\n";
  fout << "Spring 2143\n\n";
  G.printGraph(fout);
  D.printGraph(fout);
  B.printGraph(fout);
//Closing all files opened
  fout.close();
}