#include "binaryHeap.h"

namespace Heap {

template <typename T>
BinaryHeap<T> operator+(T const &value, BinaryHeap<T> const &binaryHeap) {
	return binaryHeap + value;
}
template <typename T>
BinaryHeap<T> operator+(Container::Vector<T> const &values, BinaryHeap<T> const &binaryHeap) {
	return binaryHeap + values;
}

} // namespace Heap