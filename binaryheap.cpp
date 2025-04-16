/* File: binaryheap.cpp
 * Course: CS316
 * Program 3
 * Purpose: the implementation of member functions for the Binary Heap class.
 *
 */

 #include "binaryheap.h"

 // Constructor
 BinaryHeap::BinaryHeap() {
     // Initialize basic element at index 0 to make indexing simpler
     heap.push_back(make_pair("", -1));
 }
 
 // Insert a node into the heap with a given priority
 void BinaryHeap::insert(const string& node, int priority) {
     // Add the node to the end of the heap
     heap.push_back(make_pair(node, priority));
     
     // Update the position map
     int pos = heap.size() - 1;
     nodePositions[node] = pos;
     
     // Bubble up
     bubbleUp(pos);
 }
 
 // Extract the minimum node from the heap
 string BinaryHeap::extractMin() {
     if (isEmpty()) {
         cout << "Error: Cannot extract from an empty heap" << endl;
         return "";
     }
     
     // The root of the heap is the minimum
     string minNode = heap[1].first;
     int minPriority = heap[1].second;
     
     // Move the last element to the root
     heap[1] = heap[heap.size() - 1];
     nodePositions[heap[1].first] = 1;
     
     // Remove the last element
     heap.pop_back();
     
     // Remove the extracted node from the position map
     nodePositions.erase(minNode);
     
     // If the heap is not empty, bubble down the new root
     if (heap.size() > 1) {
         bubbleDown(1);
     }
     
     return minNode;
 }
 
 // Decrease the key of a node in the heap
 void BinaryHeap::decreaseKey(const string& node, int newPriority) {
     // Check if the node exists in the heap
     if (nodePositions.find(node) == nodePositions.end()) {
         cout << "Error: Node not found in the heap" << endl;
         return;
     }
     
     int pos = nodePositions[node];
     
     // Only decrease if the new priority is smaller
     if (newPriority < heap[pos].second) {
         heap[pos].second = newPriority;
         bubbleUp(pos);
     }
 }
 
 // Check if the heap is empty
 bool BinaryHeap::isEmpty() {
     // Size 1 means only the dummy element is present
     return heap.size() <= 1;
 }
 
 // Check if the heap contains a node
 bool BinaryHeap::contains(const string& node) const {
     return nodePositions.find(node) != nodePositions.end();
 }
 
 // Print the heap for debugging
 void BinaryHeap::printHeap() {
     cout << "Heap contents:" << endl;
     for (size_t i = 1; i < heap.size(); i++) {
         cout << "Node: " << heap[i].first << ", Priority: " << heap[i].second << endl;
     }
 }
 
 // Helper method to bubble up a node
 void BinaryHeap::bubbleUp(int pos) {
     // Save the node that needs to be bubbled up
    pair<string, int> node = heap[pos];
     
     // While not at the root and the parent has higher priority
     int parent = pos / 2;
     while (pos > 1 && heap[parent].second > node.second) {
         // Move the parent down
         heap[pos] = heap[parent];
         nodePositions[heap[pos].first] = pos;
         
         // Move up
         pos = parent;
         parent = pos / 2;
     }
     
     // Place the node in its final position
     heap[pos] = node;
     nodePositions[node.first] = pos;
 }
 
 // Helper method to bubble down a node
 void BinaryHeap::bubbleDown(int pos) {
     int size = heap.size();
     // Save the node that needs to be bubbled down
    pair<string, int> node = heap[pos];
     
     // While there is at least a left child
     while (2 * pos < size) {
         int child = 2 * pos; // Left child
         
         // If there is a right child and it has smaller priority
         if (child + 1 < size && heap[child + 1].second < heap[child].second) {
             child++; // Use the right child
         }
         
         // If the child has smaller priority, move it up
         if (heap[child].second < node.second) {
             heap[pos] = heap[child];
             nodePositions[heap[pos].first] = pos;
             pos = child;
         } else {
             break; // We're done
         }
     }
     
     // Place the node in its final position
     heap[pos] = node;
     nodePositions[node.first] = pos;
 }