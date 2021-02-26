#ifndef CONTAINER_GUARD
#define CONTAINER_GUARD
#include <initializer_list>

namespace Container {

template <typename T>
class Vector {
	int capacity;
	T *data;

	void realloc(int length, int capacityNew) {
		if (capacityNew < length) {
			throw "Vector realloc loosing data";
		}

		T *dataNew = new T[capacityNew];
		for (int i = 0; i < length; i++) {
			dataNew[i] = data[i];
		}
		delete[] data;
		data = dataNew;
	}

  public:
	int length;
	Vector() {
		length = 0;
		capacity = 1;
		data = new T[1];
	}
	Vector(std::initializer_list<T> values) {
		length = 0;
		capacity = 1;
		data = new T[1];
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}
	~Vector() {
		delete[] data;
	}
	T &operator[](int index) {
		if (index >= length) {
			throw "Vector[] out of bounds";
		}
		return data[index];
	}
	void pushBack(T value) {
		if (capacity == length) {
			capacity *= 2;
			realloc(length, capacity);
		}

		data[length] = value;
		length++;
	}
	T popBack() {
		T result = data[length - 1];
		length--;

		if (length * 4 == capacity) {
			capacity /= 2;
			realloc(length, capacity);
		}
		return result;
	}
};

} // namespace Container

#endif