#include "include/heap/binaryHeap.h"
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
		heap.insert(v);
	}
	for (int i = 1; i <= 100; i++) {
		assert(heap.pop() == i);
	}
}