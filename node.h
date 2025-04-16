/* File: node.h
 * Course: CS316
 * Program 3
 * Purpose: the declaration for the node class.
 *
 */

 #ifndef NODE_H
 #define NODE_H
 #include <string>
 #include <unordered_map>
 #include <iostream>
 
 using namespace std;
 
 class Node {
     public:
         // Constructors
         Node();
         Node(const string& nodeId);
         
         // Getters
         string getId() const;
         const unordered_map<string, int>& getNeighbors() const;
         
         // Neighbor operations
         void addNeighbor(const string& neighborId, int weight);
         void removeNeighbor(const string& neighborId);
         bool hasNeighbor(const string& neighborId) const;
         int getNeighborWeight(const string& neighborId) const;
 
     private:
         string id;
         unordered_map<string, int> neighbors; // Maps neighbor node IDs to weights
 };
 
 #endif // NODE_H