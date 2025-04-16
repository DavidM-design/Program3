/* File: graph.cpp
 * Course: CS316
 * Program 3
 * Purpose: the implementation of member functions for the graph class.
 *
 */

 #include "graph.h"

 // Constructor
 Graph::Graph() : numNodes(0), numEdges(0) {}
 
 // Destructor to handle memory cleanup
 Graph::~Graph() {
     // Delete all node objects
    for (map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        delete it->second;
    }
     nodes.clear();
     numNodes = 0;
     numEdges = 0;
 }
 
 // Add a node to the graph
 void Graph::addNode(const string& id, Node* node) {
     // Check if node already exists
     if (nodes.find(id) == nodes.end()) {
         nodes[id] = node;
         numNodes++;
     } else {
         // Replace existing node (delete old one first)
         delete nodes[id];
         nodes[id] = node;
     }
 }
 
 // Add a node by ID only (creates a new node)
 void Graph::addNode(const string& id) {
     // Check if node already exists
     if (nodes.find(id) == nodes.end()) {
         nodes[id] = new Node(id);
         numNodes++;
     }
 }
 
 // Remove a node from the graph
 void Graph::removeNode(const string& id) {
    map<string, Node*>::iterator it = nodes.find(id);
    if (it != nodes.end()) {
        // First, remove all edges connected to this node
        Node* nodeToRemove = it->second;
         
        // Iterate through all nodes to remove edges to the node being removed
        for (map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            Node* currentNode = it->second;
            if (currentNode->hasNeighbor(id)) {
            currentNode->removeNeighbor(id);
            numEdges--;
            }
        }
         
        // Delete the node and remove from map
        delete nodeToRemove;
        nodes.erase(it);
        numNodes--;
     }
 }
 
 // Get a node by its ID
 Node* Graph::getNode(const string& id) {
    map<string, Node*>::iterator it = nodes.find(id);
     return (it != nodes.end()) ? it->second : nullptr;
 }
 
 // Const version for read-only access
 const Node* Graph::getNode(const string& id) const {
    map<string, Node*>::const_iterator it = nodes.find(id);
    return (it != nodes.end()) ? it->second : nullptr;
 }
 
 // Add a weighted edge between two nodes
 void Graph::addEdge(const string& fromNodeId, const string& toNodeId, int weight) {
     Node* fromNode = getNode(fromNodeId);
     Node* toNode = getNode(toNodeId);
     
     if (fromNode && toNode) {
         // For undirected graph, add edges in both directions
         // Only count as one edge for numEdges
         if (!fromNode->hasNeighbor(toNodeId)) {
             fromNode->addNeighbor(toNodeId, weight);
             toNode->addNeighbor(fromNodeId, weight); // Add in opposite direction too
             numEdges++;
         }
     }
 }
 
 // Remove an edge between two nodes
 void Graph::removeEdge(const string& fromNodeId, const string& toNodeId) {
     Node* fromNode = getNode(fromNodeId);
     Node* toNode = getNode(toNodeId);
     
     if (fromNode && toNode) {
         // Remove edges in both directions
         if (fromNode->hasNeighbor(toNodeId)) {
             fromNode->removeNeighbor(toNodeId);
             toNode->removeNeighbor(fromNodeId);
             numEdges--;
         }
     }
 }
 
 // Get the neighbors of a node
 vector<Node*> Graph::getNeighbors(const string& nodeId) {
     vector<Node*> neighborNodes;
     Node* node = getNode(nodeId);
     
    if (node) {
        const unordered_map<string, int>& neighbors = node->getNeighbors();
        for (unordered_map<string, int>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
           Node* neighborNode = getNode(it->first);
           if (neighborNode) {
              neighborNodes.push_back(neighborNode);
           }
        }
    }
     
     return neighborNodes;
 }
 
 // Get all nodes in the graph
 vector<Node*> Graph::getAllNodes() {
     vector<Node*> allNodes;
     allNodes.reserve(nodes.size());
     
    for (map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = it->second;
        allNodes.push_back(node);
    }
     
     return allNodes;
 }
 
 // Get all node IDs in the graph
 vector<string> Graph::getAllNodeIds() const {
     vector<string> ids;
     ids.reserve(nodes.size());
     
    for (map<string, Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        ids.push_back(it->first);
    }
     
     return ids;
 }
 
 // Get the number of nodes in the graph
 int Graph::getNumNodes() const {
     return numNodes;
 }
 
 // Get the number of edges in the graph
 int Graph::getNumEdges() const {
     return numEdges;
 }