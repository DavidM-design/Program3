HEADERS = binaryheap.h graph.h navigator.h pathfinder.h node.h program3.h
SOURCES = binaryheap.cpp graph.cpp navigator.cpp pathfinder.cpp node.cpp program3.cpp
OBJECTS = binaryheap.o graph.o navigator.o pathfinder.o node.o program3.o 
EXEC = program3

$(EXEC): $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o $(EXEC)