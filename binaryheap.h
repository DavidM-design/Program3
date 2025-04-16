/* File: binaryheap.h
 * Course: CS316
 * Program 3
 * Purpose: the declaration for the Binary Heap class, which implements the priority queue for Dijkstra's algorithm.
 *
 */

 #ifndef BINARYHEAP_H
 #define BINARYHEAP_H
 #include <iostream>
 #include <vector>
 #include <map>
 #include <string>
 #include <utility> // For std::pair
 
 using namespace std;
 
 class BinaryHeap {
     public:
         // Constructor
         BinaryHeap();
 
         // Insert a node into the heap with a given priority
         void insert(const string& node, int priority);
 
         // Extract the minimum node from the heap
         string extractMin();
 
         // Decrease the key of a node in the heap
         void decreaseKey(const string& node, int priority); 
 
         // Check if the heap is empty
         bool isEmpty();
         
         // Check if the heap contains a node
         bool contains(const string& node) const;
 
         // Print the heap for debugging
         void printHeap();
         
     private:
         vector<pair<string, int> > heap; // The heap vector - (node, priority)
         map<string, int> nodePositions; // A map to keep track of the positions of nodes in the heap
         
         // Helper methods
         void bubbleUp(int pos);
         void bubbleDown(int pos);
 };
 
 #endif // BINARYHEAP_H