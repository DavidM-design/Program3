/* File: navigator.cpp
 * Course: CS316
 * Program 3
 * Purpose: the implementation of member functions for the Navigator class.
 *
 */

 #include "navigator.h"
 #include <algorithm>
 #include <limits>
 
 // Constructor
 Navigator::Navigator() {
     pathFinder = new PathFinder(graph);
 }
 
 // Load data from files
 bool Navigator::loadData(const string& verticesFile, const string& edgesFile) {
     // Load vertices first
     if (!loadVertices(verticesFile)) {
         cerr << "Failed to load vertices from " << verticesFile << endl;
         return false;
     }
     
     // Then load edges
     if (!loadEdges(edgesFile)) {
         cerr << "Failed to load edges from " << edgesFile << endl;
         return false;
     }
     
     cout << "Data loaded successfully: " << graph.getNumNodes() << " locations and " 
          << graph.getNumEdges() << " paths." << endl;
     return true;
 }
 
 // Helper method to load vertices
 bool Navigator::loadVertices(const string& filename) {
     ifstream file(filename);
     if (!file.is_open()) {
         cerr << "Error: Could not open file " << filename << endl;
         return false;
     }
     
     string line;
     while (getline(file, line)) {
         // Skip empty lines
         if (!line.empty()) {
             // Add node to graph
             graph.addNode(line);
         }
     }
     
     file.close();
     return true;
 }
 
 // Helper method to load edges
 bool Navigator::loadEdges(const string& filename) {
     ifstream file(filename);
     if (!file.is_open()) {
         cerr << "Error: Could not open file " << filename << endl;
         return false;
     }
     
     string line;
     while (getline(file, line)) {
         stringstream ss(line);
         string from, to, weightStr;
         
         // Parse the CSV line
         if (getline(ss, from, ',') && getline(ss, to, ',') && getline(ss, weightStr, ',')) {
             try {
                 int weight = stoi(weightStr);
                 // Add edge to graph
                 graph.addEdge(from, to, weight);
             } catch (const exception& e) {
                 cerr << "Error parsing weight '" << weightStr << "': " << e.what() << endl;
                 return false;
             }
         } else {
             cerr << "Error: Malformed edge line: " << line << endl;
             return false;
         }
     }
     
     file.close();
     return true;
 }
 
 // Show available locations
 void Navigator::showLocations() const {
     vector<string> locations = graph.getAllNodeIds();
     
     // Sort locations alphabetically
     sort(locations.begin(), locations.end());
     
     cout << "\nAvailable Locations:" << endl;
     cout << "-------------------" << endl;
     
     int column = 0;
    for (size_t i = 0; i < locations.size(); ++i) {
        cout << locations[i];
        column++;
        
        // Format into columns
        if (column % 3 == 0 || i == locations.size() - 1) {
           cout << endl;
        } else {
           cout << "\t";
        }
    }
    cout << endl;
 }
 
 // Find route between locations
 void Navigator::findRoute(const string& start, const string& end, bool useDijkstra) {
     // Check if both locations exist
     if (!graph.getNode(start)) {
         cerr << "Error: Location '" << start << "' does not exist." << endl;
         return;
     }
     
     if (!graph.getNode(end)) {
         cerr << "Error: Location '" << end << "' does not exist." << endl;
         return;
     }
     
     // Find the path
     vector<string> path;
     if (useDijkstra) {
         cout << "\nFinding route using Dijkstra's algorithm..." << endl;
         path = pathFinder->findPathDijkstra(start, end);
     } else {
         cout << "\nFinding route using BFS algorithm..." << endl;
         path = pathFinder->findPathBFS(start, end);
     }
     
     // Display the path
     displayPath(path, useDijkstra);
 }
 
 // Helper method to display a path
 void Navigator::displayPath(const vector<string>& path, bool showWeights) {
     if (path.empty()) {
         cout << "No path found!" << endl;
         return;
     }
     
     cout << "Path found with " << path.size() - 1 << " steps:" << endl;
     
     int totalWeight = 0;
     for (size_t i = 0; i < path.size(); i++) {
         cout << path[i];
         
         // Add weight if not the last node and we want to show weights
         if (i < path.size() - 1) {
             if (showWeights) {
                 Node* node = graph.getNode(path[i]);
                 int weight = node->getNeighborWeight(path[i+1]);
                 totalWeight += weight;
                 cout << " --(" << weight << ")--> ";
             } else {
                 cout << " --> ";
             }
         }
     }
     cout << endl;
     
     if (showWeights) {
         cout << "Total journey distance: " << totalWeight << endl;
     }
 }
 
 // Compare algorithms
 void Navigator::compareAlgorithms(const string& start, const string& end) {
     // Check if both locations exist
     if (!graph.getNode(start)) {
         cerr << "Error: Location '" << start << "' does not exist." << endl;
         return;
     }
     
     if (!graph.getNode(end)) {
         cerr << "Error: Location '" << end << "' does not exist." << endl;
         return;
     }
     
     // Compare algorithms
     pathFinder->compareAlgorithms(start, end);
 }
 
 // Run the navigator interface
 void Navigator::run() {
     string command;
     
     cout << "=== Middle Earth Navigator ===" << endl;
     cout << "Enter 'help' for a list of commands." << endl;
     
     while (true) {
         cout << "\nCommand: ";
         getline(cin, command);
         
         // Convert to lowercase for case-insensitive commands
         transform(command.begin(), command.end(), command.begin(), ::tolower);
         
         if (command == "exit" || command == "quit") {
             break;
         } else if (command == "help") {
             cout << "Available commands:" << endl;
             cout << "  help          - Show this help message" << endl;
             cout << "  locations     - Show all available locations" << endl;
             cout << "  bfs           - Find route using BFS algorithm" << endl;
             cout << "  dijkstra      - Find route using Dijkstra's algorithm" << endl;
             cout << "  compare       - Compare both algorithms for a route" << endl;
             cout << "  exit/quit     - Exit the program" << endl;
         } else if (command == "locations") {
             showLocations();
         } else if (command == "bfs") {
             string start, end;
             cout << "Enter start location: ";
             getline(cin, start);
             cout << "Enter end location: ";
             getline(cin, end);
             findRoute(start, end, false);
         } else if (command == "dijkstra") {
             string start, end;
             cout << "Enter start location: ";
             getline(cin, start);
             cout << "Enter end location: ";
             getline(cin, end);
             findRoute(start, end, true);
         } else if (command == "compare") {
             string start, end;
             cout << "Enter start location: ";
             getline(cin, start);
             cout << "Enter end location: ";
             getline(cin, end);
             compareAlgorithms(start, end);
         } else {
             cout << "Unknown command. Type 'help' for a list of commands." << endl;
         }
     }
     
     cout << "Thank you for using Middle Earth Navigator. Goodbye!" << endl;
 }