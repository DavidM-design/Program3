/* File: graph.h
 * Course: CS316
 * Program 3
 * Purpose: the declaration for the graph class, which collects and manages the nodes.
 *
 */

 #ifndef GRAPH_H
 #define GRAPH_H
 #include <iostream>
 #include <map>
 #include <vector>
 #include <string>
 #include "node.h"
 
 using namespace std;
 
 class Graph {
     public:
         // Constructor
         Graph();
         
         // Destructor to handle memory cleanup
         ~Graph();
 
         // Add a node to the graph
         void addNode(const string& id, Node* node);
         
         // Add a node by ID only (creates a new node)
         void addNode(const string& id);
 
         // Remove a node from the graph
         void removeNode(const string& id);
 
         // Get a node by its ID
         Node* getNode(const string& id);
         
         // Const version for read-only access
         const Node* getNode(const string& id) const;
 
         // Add a weighted edge between two nodes
         void addEdge(const string& fromNodeId, const string& toNodeId, int weight);
 
         // Remove an edge between two nodes
         void removeEdge(const string& fromNodeId, const string& toNodeId);
 
         // Get the neighbors of a node
         vector<Node*> getNeighbors(const string& nodeId);
 
         // Get all nodes in the graph
         vector<Node*> getAllNodes();
         
         // Get all node IDs in the graph
         vector<string> getAllNodeIds() const;
 
         // Get the number of nodes in the graph
         int getNumNodes() const;
 
         // Get the number of edges in the graph
         int getNumEdges() const;
 
     private:
         map<string, Node*> nodes; // A map to store nodes with their IDs as keys
         int numNodes; // The number of nodes in the graph
         int numEdges; // The number of edges in the graph
 };
 
 #endif // GRAPH_H