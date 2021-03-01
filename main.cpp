#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <assert.h>

int main() {
	//unit tests
	Container::Vector<int>::test();
	Heap::BinaryHeap<int>::test();

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
	for (int i = 0; i < vector.length; i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;

	//dijsktra
	Dijkstra::Dijkstra dijkstra("graph.txt", 0);
	for (int i = 0; i < dijkstra.length; i++) {
		dijkstra.printPath(i);
	}

	return 0;
}