/* File: pathfinder.h
 * Course: CS316
 * Program 3
 * Purpose: the declaration for the pathfinder class, which provides the algorithm implementations
 *
 */

 #ifndef PATHFINDER_H
 #define PATHFINDER_H
 #include <iostream>
 #include <vector>
 #include <string>
 #include <unordered_map>
 #include "graph.h"
 #include "binaryheap.h"
 
 using namespace std;
 
 class PathFinder {
     public:
         // Constructor
         PathFinder(Graph& g);
         
         // Find shortest path using BFS
         vector<string> findPathBFS(const string& startNode, const string& endNode);
         
         // Find shortest path using Dijkstra's algorithm
         vector<string> findPathDijkstra(const string& startNode, const string& endNode);
         
         // Compare the two algorithms
         void compareAlgorithms(const string& startNode, const string& endNode);
         
     private:
         Graph& graph;
         
         // Helper function to reconstruct the path
         vector<string> reconstructPath(
             const string& startNode, 
             const string& endNode, 
             const unordered_map<string, string>& predecessors);
 };
 
 #endif // PATHFINDER_H