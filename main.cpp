#include "include/heap/binaryHeap.hpp"
#include "include/container/vector.hpp"
#include "include/algorithm/dijkstra.hpp"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "memtrace.h"

int main() {
	//unit tests
	Container::Vector<int>::Test();
	Heap::BinaryHeap<int>::Test();

	//heap sort
	std::ifstream file("test/sort.txt", std::ifstream::in);
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
	try {
		Dijkstra::Dijkstra<int> dijkstra("test/graph.txt", 0);
		for (int i = 0; i < dijkstra.length(); i++) {
			dijkstra.printPath(i);
		}
	} catch (std::exception const &e) {
		std::cout << "error: " << e.what() << std::endl;
	}

	try {
		Dijkstra::Dijkstra<int> dijkstra = Dijkstra::Dijkstra<int>("test/graphMalformed.txt", 0);
		std::cout << "error not caught" << std::endl;
	} catch (std::exception const &) {
	}

	try {
		Dijkstra::Dijkstra<float> dijkstra("test/graphFloat.txt", 0);
		for (int i = 0; i < dijkstra.length(); i++) {
			dijkstra.printPath(i);
		}
	} catch (std::exception const &e) {
		std::cout << "error: " << e.what() << std::endl;
	}

	return 0;
}