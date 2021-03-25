#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <algorithm>
#include "../container/vector.h"
#include <assert.h>
#include "heap.h"

#include "../../memtrace.h"

namespace Heap {

//default is min
template <typename T>
class BinaryHeap {
  protected:
	Container::Vector<T> data;

  private:
	/// @brief Parent's index in data if exists
	/// @param index Node's index whose parent we want
	int parentIndex(int index) const {
		return (index - 1) / 2;
	}
	/// @brief Left child's index in data if exists
	/// @param index Node's index whose child we want
	int childLeftIndex(int index) const {
		return 2 * index + 1;
	}
	/// @brief Right child's index in data if exists
	/// @param index Node's index whose child we want
	int childRightIndex(int index) const {
		return 2 * index + 2;
	}

	/// @brief Parent's value in data
	/// @param index Node's index whose parent we want
	/// @exception Heap::ExceptionIndexOutofbounds
	T &parent(int index) const {
		index = parentIndex(index);
		if (index >= data.length()) {
			throw Exception::IndexOutofbounds();
		}
		return data[index];
	}
	/// @brief Left child's value in data
	/// @param index Node's index whose child we want
	/// @exception Heap::ExceptionIndexOutofbounds
	T &childLeft(int index) const {
		index = childLeftIndex(index);
		if (index >= data.length()) {
			throw Exception::IndexOutofbounds();
		}
		return data[index];
	}
	/// @brief Right child's value in data
	/// @param index Node's index whose child we want
	/// @exception Heap::ExceptionIndexOutofbounds
	T &childRight(int index) const {
		index = childRightIndex(index);
		if (index >= data.length()) {
			throw Exception::IndexOutofbounds();
		}
		return data[index];
	}

	/// @brief Child's index with lesser value
	/// @param index Node's index whose child we want
	/// @return -1 if lead node
	int minChildIndex(int index) const {
		if (childLeftIndex(index) >= data.length() && childRightIndex(index) >= data.length()) {
			return -1;
		}
		if (childLeftIndex(index) >= data.length()) {
			return childRightIndex(index);
		}
		if (childRightIndex(index) >= data.length()) {
			return childLeftIndex(index);
		}
		if (childLeft(index) < childRight(index)) {
			return childLeftIndex(index);
		}
		return childRightIndex(index);
	}
	/// @brief Child with lesser value
	/// @param index Node's index whose child we want
	/// @exception Heap::ExceptionIndexOutofbounds
	T &minChild(int index) const {
		if (minChildIndex(index) == -1) {
			throw Exception::IndexOutofbounds();
		}
		return data[minChildIndex(index)];
	}

  public:
	/// @brief Clears heap
	virtual void clear() {
		data.clear();
	}

	/// @brief Inserts value into heap
	/// @param value Value to be inserted
	virtual void insert(T const &value) {
		data.pushBack(value);

		//fix heap
		int index = data.length() - 1;
		while (index != 0 && value < parent(index)) {
			data[index] = parent(index);
			index = parentIndex(index);
		}
		data[index] = value;
	}

	/// @brief Inserts Container::Vector of values into heap
	/// @param values Container::Vector of values to be inserted
	virtual void insert(Container::Vector<T> const &values) {
		for (int i = 0; i < values.length(); i++) {
			insert(values[i]);
		}
	}

	/// @brief Peek the lowest element
	/// @return Lowest element
	/// @exception Heap::ExceptionEmpty
	virtual T top() const {
		if (empty()) {
			throw Exception::Empty();
		}
		return data[0];
	}

	/// @brief Remove the lowest element
	/// @return Lowest element
	/// @exception Heap::ExceptionEmpty
	virtual T pop() {
		if (empty()) {
			throw Exception::Empty();
		}

		T result = data[0];

		//fix heap
		T last = data.popBack();
		//if it was the last item we can not move it back again
		if (data.length() != 0) {
			int index = 0;
			while (minChildIndex(index) != -1 && minChild(index) < last) {
				data[index] = minChild(index);
				index = minChildIndex(index);
			}
			data[index] = last;
		}

		return result;
	}

	/// @brief Is heap empty
	virtual bool empty() const {
		return data.length() == 0;
	}

	/// @brief Number of element in heap
	virtual int length() const {
		return data.length();
	}

	/// @brief Sorts the given vector
	/// @param vector vector to be sorted
	static void Sort(Container::Vector<T> const &vector) {
		BinaryHeap<T> heap;
		for (int i = 0; i < vector.length(); i++) {
			heap += vector[i];
		}

		for (int i = 0; i < vector.length(); i++) {
			vector[i] = heap.pop();
		}
	}

	//ctor
	BinaryHeap() {
	}
	BinaryHeap(Container::Vector<T> const &vector) {
		for (int i = 0; i < vector.length(); i++) {
			insert(vector[i]);
		}
	}

	//dtor
	virtual ~BinaryHeap() {
	}

	//operator+
	virtual BinaryHeap<T> operator+(T const &value) {
		BinaryHeap<T> binaryHeap;
		binaryHeap.insert(value);
		return binaryHeap;
	}
	virtual BinaryHeap<T> operator+(Container::Vector<T> const &values) {
		BinaryHeap<T> binaryHeap;
		binaryHeap.insert(values);
		return binaryHeap;
	}

	//operator+=
	virtual BinaryHeap<T> &operator+=(T const &value) {
		insert(value);
		return *this;
	}
	virtual BinaryHeap<T> &operator+=(Container::Vector<T> const &values) {
		insert(values);
		return *this;
	}

	//unit test
	static void Test() {
		BinaryHeap<int> heap;

		//insert test
		heap.insert(4);
		assert(heap.pop() == 4);
		assert(heap.empty());

		//+= vector test
		Container::Vector values = {3, 9, 7, 2, 2, 85, 36, 6};
		heap += values;
		assert(heap.pop() == 2);
		assert(heap.pop() == 2);
		assert(heap.pop() == 3);
		assert(heap.pop() == 6);
		assert(heap.pop() == 7);
		assert(heap.pop() == 9);
		assert(heap.pop() == 36);
		assert(heap.pop() == 85);
		assert(heap.empty());

		//+= misc test
		heap += Container::Vector({5, 2, 1}) + 9 + Container::Vector({3, 6, 0});
		assert(heap.pop() == 0);
		assert(heap.pop() == 1);
		assert(heap.pop() == 2);
		assert(heap.pop() == 3);
		assert(heap.pop() == 5);
		assert(heap.pop() == 6);
		assert(heap.pop() == 9);
		assert(heap.empty());

		//= test
		BinaryHeap<int> a;
		BinaryHeap<int> b;
		a = b;

		//copy ctor test
		BinaryHeap<int> c;
		BinaryHeap<int> d = c;

		//vector ctor test
		BinaryHeap<int> e({3, 1, 99, 1});
		assert(e.pop() == 1);
		assert(e.pop() == 1);
		assert(e.pop() == 3);
		assert(e.pop() == 99);
		assert(e.empty());
	}
};

template <typename T>
BinaryHeap<T> operator+(T const &value, BinaryHeap<T> const &binaryHeap) {
	return binaryHeap + value;
}
template <typename T>
BinaryHeap<T> operator+(Container::Vector<T> const &values, BinaryHeap<T> const &binaryHeap) {
	return binaryHeap + values;
}

} // namespace Heap

#endif