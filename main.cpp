#include "include/heap/binaryHeap.h"
#include "include/container/vector.h"
#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <assert.h>

int main() {
	//heap sort
	std::ifstream file("sort.txt", std::ifstream::in);
	assert(file.good());

	Heap::BinaryHeap<int> heap;
	int v;
	while (file >> v) {
		heap += v;
	}
	for (int i = 1; i <= 100; i++) {
		assert(heap.pop() == i);
	}
	file.close();

	//dijsktra
	Dijkstra::Dijkstra d("graph.txt", 0);
	d.printPath(5);

	return 0;
}