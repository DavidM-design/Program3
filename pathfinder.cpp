
/* File: pathfinder.cpp
 * Course: CS316
 * Program 3
 * Purpose: the implementation of member functions for the PathFinder class.
 *
 */

 #include "pathfinder.h"
 #include <queue>
 #include <unordered_set>
 #include <limits>
 
 // Constructor
 PathFinder::PathFinder(Graph& g) : graph(g) {}
 
 // Manually reverse a vector instead of using algorithm's reverse
 void reverseVector(vector<string>& vec) {
     int start = 0;
     int end = vec.size() - 1;
     while (start < end) {
         string temp = vec[start];
         vec[start] = vec[end];
         vec[end] = temp;
         start++;
         end--;
     }
 }
 
 // Reconstruct the path from start to end using the predecessors map
 vector<string> PathFinder::reconstructPath(
     const string& startNode, 
     const string& endNode, 
     const unordered_map<string, string>& predecessors) {
     
     vector<string> path;
     string current = endNode;
     
     // Check if a path was found
     if (predecessors.find(endNode) == predecessors.end() && startNode != endNode) {
         return path; // Return empty path if no path exists
     }
     
     // Reconstruct the path from end to start
     while (current != startNode) {
         path.push_back(current);
         unordered_map<string, string>::const_iterator it = predecessors.find(current);
         if (it == predecessors.end()) {
             // This should never happen if the path exists
             path.clear();
             return path;
         }
         current = it->second;
     }
     
     // Add the start node
     path.push_back(startNode);
     
     // Reverse the path to get it from start to end
     reverseVector(path);
     
     return path;
 }
 
 // Find shortest path using BFS
 vector<string> PathFinder::findPathBFS(const string& startNode, const string& endNode) {
     // Check if both nodes exist
     if (!graph.getNode(startNode) || !graph.getNode(endNode)) {
         cout << "Error: Start or end node does not exist" << endl;
         return vector<string>();
     }
     
     queue<string> q;
     unordered_set<string> visited;
     unordered_map<string, string> predecessors;
     
     // Initialize BFS
     q.push(startNode);
     visited.insert(startNode);
     
     // BFS loop
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        
        // Check if we reached the destination
        if (current == endNode) {
            break;
        }
        
        // Get the current node
        Node* currentNode = graph.getNode(current);
        if (!currentNode) {
            continue;
        }
        
        // Process all neighbors
        const unordered_map<string, int>& neighbors = currentNode->getNeighbors();
        for (unordered_map<string, int>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            const string& neighborId = it->first;
            
            if (visited.find(neighborId) == visited.end()) {
                visited.insert(neighborId);
                predecessors[neighborId] = current;
                q.push(neighborId);
            }
        }
    }
     
     // Reconstruct the path
     return reconstructPath(startNode, endNode, predecessors);
 }
 
 // Find shortest path using Dijkstra's algorithm
 vector<string> PathFinder::findPathDijkstra(const string& startNode, const string& endNode) {
     // Check if both nodes exist
     if (!graph.getNode(startNode) || !graph.getNode(endNode)) {
         cout << "Error: Start or end node does not exist" << endl;
         return vector<string>();
     }
     
     // Initialize distances to infinity
     unordered_map<string, int> distances;
     unordered_map<string, string> predecessors;
     unordered_set<string> visited;
     
     // Get all nodes
     vector<string> allNodes = graph.getAllNodeIds();
     
     // Set all distances to infinity
     unordered_set<string> uniqueNodes(allNodes.begin(), allNodes.end());
    for (unordered_set<string>::iterator it = uniqueNodes.begin(); it != uniqueNodes.end(); ++it) {
        distances[*it] = numeric_limits<int>::max();
    } 
     // Distance to start is 0
     distances[startNode] = 0;
     
     // Create a priority queue
     BinaryHeap pq;
     pq.insert(startNode, 0);
     
     // Dijkstra's algorithm
    while (!pq.isEmpty()) {
        // Get the node with the smallest distance
        string current = pq.extractMin();
        
        // If we've reached the destination, we're done
        if (current == endNode) {
            break;
        }
        
        // Skip if already visited
        if (visited.find(current) != visited.end()) {
            continue;
        }
        
        // Mark as visited
        visited.insert(current);
        
        // Get the current node
        Node* currentNode = graph.getNode(current);
        if (!currentNode) {
            continue;
        }
        
        // Process all neighbors
        const unordered_map<string, int>& neighbors = currentNode->getNeighbors();
        for (unordered_map<string, int>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            const string& neighborId = it->first;
            int weight = it->second;
            
            // Skip if already visited
            if (visited.find(neighborId) != visited.end()) {
                continue;
            }
            
            // Calculate new distance
            int newDistance = distances[current] + weight;
            
            // Update if this is a shorter path
            if (newDistance < distances[neighborId]) {
                distances[neighborId] = newDistance;
                predecessors[neighborId] = current;
                
                // Update priority queue
                if (pq.contains(neighborId)) {
                    pq.decreaseKey(neighborId, newDistance);
                } else {
                    pq.insert(neighborId, newDistance);
                }
            }
        }
    }
     
     // Reconstruct the path
     return reconstructPath(startNode, endNode, predecessors);
 }
 
 // Compare the two algorithms
 void PathFinder::compareAlgorithms(const string& startNode, const string& endNode) {
     cout << "Comparing BFS and Dijkstra's algorithm for path from " << startNode << " to " << endNode << ":" << endl;
     
     // Get paths without timing
     vector<string> bfsPath = findPathBFS(startNode, endNode);
     vector<string> dijkstraPath = findPathDijkstra(startNode, endNode);
     
     // Report results for BFS
     cout << "\nBFS Results:" << endl;
     
     if (bfsPath.empty()) {
         cout << "- No path found!" << endl;
     } else {
         cout << "- Path found (" << bfsPath.size() - 1 << " steps): ";
         for (size_t i = 0; i < bfsPath.size(); i++) {
             cout << bfsPath[i];
             if (i < bfsPath.size() - 1) {
                 cout << " -> ";
             }
         }
         cout << endl;
     }
     
     // Report results for Dijkstra's
     cout << "\nDijkstra Results:" << endl;
     
     if (dijkstraPath.empty()) {
         cout << "- No path found!" << endl;
     } else {
         int totalWeight = 0;
         cout << "- Path found (" << dijkstraPath.size() - 1 << " steps): ";
         for (size_t i = 0; i < dijkstraPath.size(); i++) {
             cout << dijkstraPath[i];
             if (i < dijkstraPath.size() - 1) {
                 Node* node = graph.getNode(dijkstraPath[i]);
                 int weight = node->getNeighborWeight(dijkstraPath[i+1]);
                 totalWeight += weight;
                 cout << " -> ";
             }
         }
         cout << endl;
         cout << "- Total path weight: " << totalWeight << endl;
     }
     
     // Compare the results
     cout << "\nComparison:" << endl;
     if (bfsPath.size() == dijkstraPath.size() && !bfsPath.empty()) {
         bool sameNodes = true;
         for (size_t i = 0; i < bfsPath.size(); i++) {
             if (bfsPath[i] != dijkstraPath[i]) {
                 sameNodes = false;
                 break;
             }
         }
         
         if (sameNodes) {
             cout << "Both algorithms found the same path." << endl;
         } else {
             cout << "Both algorithms found paths with the same number of steps, but different nodes." << endl;
         }
     } else if (!bfsPath.empty() && !dijkstraPath.empty()) {
         if (bfsPath.size() < dijkstraPath.size()) {
             cout << "BFS found a shorter path (fewer steps)." << endl;
         } else {
             cout << "Dijkstra's found a shorter path (fewer steps)." << endl;
         }
     }
     
     // Without timing, we can't compare execution time
     cout << "Time comparison not available (chrono library removed)." << endl;
 }