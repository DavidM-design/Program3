/* File: navigator.h
 * Course: CS316
 * Program 3
 * Purpose: the declaration for the navigator class, this class will provide an interface to the user creating a more streamlined main file.
 *
 */

 #ifndef NAVIGATOR_H
 #define NAVIGATOR_H
 #include <iostream>
 #include <string>
 #include <vector>
 #include <fstream>
 #include <sstream>
 #include "graph.h"
 #include "pathfinder.h"
 
 using namespace std;
 
 class Navigator {
     public:
         // Constructor
         Navigator();
         
         // Load data from files
         bool loadData(const string& verticesFile, const string& edgesFile);
         
         // Show available locations
         void showLocations() const;
         
         // Find route between locations
         void findRoute(const string& start, const string& end, bool useDijkstra);
         
         // Compare algorithms
         void compareAlgorithms(const string& start, const string& end);
         
         // Run the navigator interface
         void run();
         
     private:
         Graph graph;
         PathFinder* pathFinder;
         
         // Helper method to load vertices
         bool loadVertices(const string& filename);
         
         // Helper method to load edges
         bool loadEdges(const string& filename);
         
         // Helper method to display a path
         void displayPath(const vector<string>& path, bool showWeights);
 };
 
 #endif // NAVIGATOR_H