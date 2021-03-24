#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "memtrace.h"

int main() {
	//unit tests
	Container::Vector<int>::Test();
	Heap::BinaryHeap<int>::Test();

	//heap sort
	std::ifstream file("sort.txt", std::ifstream::in);
	assert(file.good());

	Container::Vector<int> vector;
	int v;
	while (file >> v) {
		vector += v;
	}
	file.close();

	Heap::BinaryHeap<int>::Sort(vector);
	std::cout << vector << std::endl;

	//dijsktra
	Dijkstra::Dijkstra<int> dijkstra("graph.txt", 0);
	for (int i = 0; i < dijkstra.length; i++) {
		dijkstra.printPath(i);
	}

	try {
		dijkstra = Dijkstra::Dijkstra<int>("graphMalformed.txt", 0);
	} catch (const Dijkstra::Exception::Exception &e) {
		std::cout << "file malformed" << std::endl;
	}

	Dijkstra::Dijkstra<float> dijkstraFloat("graphFloat.txt", 0);
	for (int i = 0; i < dijkstraFloat.length; i++) {
		dijkstraFloat.printPath(i);
	}

	return 0;
}