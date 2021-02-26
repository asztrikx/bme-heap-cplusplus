#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <algorithm>
#include "../container/vector.h"
#include <assert.h>

namespace Heap {

//default is min
template <typename T>
class BinaryHeap {
	Container::Vector<T> data;
	int parentIndex(int index) const {
		return (index - 1) / 2;
	}
	int childLeftIndex(int index) const {
		return 2 * index + 1;
	}
	int childRightIndex(int index) const {
		return 2 * index + 2;
	}
	T &parent(int index) const {
		index = parentIndex(index);
		if (index >= data.length) {
			throw "BinaryHeap::parent() out of bounds";
		}
		return data[index];
	}
	T &childLeft(int index) const {
		index = childLeftIndex(index);
		if (index >= data.length) {
			throw "BinaryHeap::childLeft() out of bounds";
		}
		return data[index];
	}
	T &childRight(int index) const {
		index = childRightIndex(index);
		if (index >= data.length) {
			throw "BinaryHeap::childRight() out of bounds";
		}
		return data[index];
	}
	int minChildIndex(int index) const {
		if (childLeftIndex(index) >= data.length && childRightIndex(index) >= data.length) {
			return -1;
		}
		if (childLeftIndex(index) >= data.length) {
			return childRightIndex(index);
		}
		if (childRightIndex(index) >= data.length) {
			return childLeftIndex(index);
		}
		if (childLeft(index) < childRight(index)) {
			return childLeftIndex(index);
		}
		return childRightIndex(index);
	}
	T &minChild(int index) const {
		if (minChildIndex(index) == -1) {
			throw "idk";
		}
		return data[minChildIndex(index)];
	}

  public:
	void clear() {
		data.clear();
	}
	BinaryHeap<T> &operator=(BinaryHeap<T> const &heap) {
		data = heap.data;
		return *this;
	}
	BinaryHeap<T> &operator+=(T const &value) {
		insert(value);
		return *this;
	}
	BinaryHeap<T> &operator+=(Container::Vector<T> const &values) {
		insert(values);
		return *this;
	}
	void insert(T const &value) {
		data.pushBack(value);
		int index = data.length - 1;
		while (index != 0 && parent(index) > value) {
			data[index] = parent(index);
			index = parentIndex(index);
		}
		data[index] = value;
	}
	void insert(Container::Vector<T> const &values) {
		for (int i = 0; i < values.length; i++) {
			insert(values[i]);
		}
	}
	T top() const {
		if (empty()) {
			throw "BinaryHeap top() heap is empty";
		}
		return data[0];
	}
	T pop() {
		if (empty()) {
			throw "BinaryHeap pop() heap is empty";
		}

		T result = data[0];
		T last = data.popBack();

		if (data.length != 0) {
			int index = 0;
			while (minChildIndex(index) != -1 && minChild(index) < last) {
				data[index] = data[minChildIndex(index)];
				index = minChildIndex(index);
			}
			data[index] = last;
		}

		return result;
	}
	bool empty() const {
		return data.length == 0;
	}
	static void test() {
		BinaryHeap<int> heap;
		heap.insert(4);
		assert(heap.pop() == 4);
		assert(heap.empty());

		Container::Vector values({3, 9, 7, 2, 1, 85, 36, 6});
		heap.insert(values);
		assert(heap.pop() == 1);
		assert(heap.pop() == 2);
		assert(heap.pop() == 3);
		assert(heap.pop() == 6);
		assert(heap.pop() == 7);
		assert(heap.pop() == 9);
		assert(heap.pop() == 36);
		assert(heap.pop() == 85);
		assert(heap.empty());
	}
};

} // namespace Heap

#endif