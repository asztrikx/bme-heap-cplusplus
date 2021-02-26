#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>
#include "container.h"

namespace Container {

template <typename T>
class Vector {
	/// Allocated memory's size
	int capacity;

	/// T[capacity]
	T *data = nullptr;

	/// @brief Changes `data`-s *allocated* size
	/// @param capacityNew `data`'s new *allocated* size
	/// @exception Container::ExceptionDataLoose capacityNew < length
	void realloc(int capacityNew) {
		if (capacityNew < length) {
			throw Container::ExceptionDataLoose;
		}

		capacity = capacityNew;
		T *dataNew = new T[capacity];
		for (int i = 0; i < length; i++) {
			dataNew[i] = data[i];
		}
		delete[] data;
		data = dataNew;
	}

  public:
	/// length is the number of used elements in `data`
	int length;

	/// @brief Clears then fills with `value`
	/// @param size number of elements to insert
	/// @param value value to be inserted
	void resize(int size, T const &value) {
		clear();
		for (int i = 0; i < size; i++) {
			pushBack(value);
		}
	}

	/// @brief Deletes data, then recreates it with `capacity` = 1
	void clear() {
		delete[] data;
		length = 0;
		capacity = 1;
		data = new T[1];
	}

	/// @brief data[length] = value. Capacity is doubled if full
	/// @param size number of elements to insert
	/// @param value value to be inserted
	void pushBack(T const &value) {
		if (capacity == length) {
			realloc(2 * capacity);
		}

		length++;
		data[length - 1] = value;
	}

	/// @brief Marks last element as garbage. Decreases capacity if needed
	/// @param size number of elements to insert
	/// @param value value to be inserted
	/// @return last element
	T popBack() {
		T result = data[length - 1];
		length--;

		if (capacity == 4 * length) {
			realloc(capacity / 2);
		}
		return result;
	}

	//operator
	Vector<T> &operator=(Vector<T> const &vector) {
		length = vector.length;
		capacity = vector.capacity;
		data = new T[vector.capacity];
		for (int i = 0; i < vector.length; i++) {
			data[i] = vector.data[i];
		}
		return *this;
	}
	T &operator[](int index) const {
		if (index >= length) {
			throw Container::ExceptionIndexOutofbounds;
		}
		return data[index];
	}
	void operator+=(T const &value) {
		pushBack(value);
	}

	//ctor, dtor
	Vector() {
		clear();
	}
	Vector(int size, T def) {
		resize(size, def);
	}
	Vector(std::initializer_list<T> const &values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}
	~Vector() {
		delete[] data;
	}
};

} // namespace Container

#endif