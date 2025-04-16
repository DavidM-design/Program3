/* File: node.cpp
 * Course: CS316
 * Program 3
 * Purpose: the implementation of member functions for the node class.
 *
 */

 #include "node.h"

 // Constructors
 Node::Node() : id("") {}
 
 Node::Node(const string& nodeId) : id(nodeId) {}
 
 // Getters
 string Node::getId() const {
     return id;
 }
 
 const unordered_map<string, int>& Node::getNeighbors() const {
     return neighbors;
 }
 
 // Neighbor operations
 void Node::addNeighbor(const string& neighborId, int weight) {
     neighbors[neighborId] = weight;
 }
 
 void Node::removeNeighbor(const string& neighborId) {
     neighbors.erase(neighborId);
 }
 
 bool Node::hasNeighbor(const string& neighborId) const {
     return neighbors.find(neighborId) != neighbors.end();
 }
 
 int Node::getNeighborWeight(const string& neighborId) const {
    unordered_map<string, int>::const_iterator it = neighbors.find(neighborId);
     if (it == neighbors.end()) {
         // Error handling - neighbor not found
         cerr << "Error: Neighbor '" << neighborId << "' not found for node '" << id << "'" << endl;
         return -1; // Return a sentinel value to indicate error
     }
     return it->second;
 }