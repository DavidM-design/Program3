/* File: main.cpp
 * Course: CS316
 * Program 3
 * Purpose: the main function to test the Middle Earth navigator.
 * Author: David Marquez
 */

 #include "navigator.h"
 #include <iostream>
 
 using namespace std;
 
 int main() {
     Navigator navigator;
     
     // Load the data
     if (!navigator.loadData("Data/MiddleEarthVertices.txt", "Data/MiddleEarthEdges.txt")) {
         cout << "Failed to load data. Exiting." << endl;
         return 1;
     }
     
     // Run the navigator
     navigator.run();
     
     return 0;
 }