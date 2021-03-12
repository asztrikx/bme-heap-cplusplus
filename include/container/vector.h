#ifndef VECTOR_H
#define VECTOR_H
#include "container.h"
#include <initializer_list>
#include <cassert>
#include <iostream>

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
			throw Exception::DataLoose();
		}

		capacity = capacityNew;
		T *dataNew = new T[capacity];
		for (int i = 0; i < length; i++) {
			dataNew[i] = data[i];
		}
		delete[] data;
		data = dataNew;
	}
	void copy(Vector const &vector) {
		delete[] data;
		length = vector.length;
		capacity = vector.capacity;
		data = new T[vector.capacity];
		for (int i = 0; i < vector.length; i++) {
			data[i] = vector.data[i];
		}
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
		data = new T[capacity];
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

	//operator=
	Vector<T> &operator=(Vector<T> const &vector) {
		copy(vector);
		return *this;
	}
	Vector<T> &operator=(std::initializer_list<T> const &values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}

	//operator[]
	T &operator[](int index) const {
		if (index >= length || index < 0) {
			throw Exception::IndexOutofbounds();
		}
		return data[index];
	}

	//operator+
	Vector operator+(T const &value) const {
		Vector<T> vector;
		vector.copy(*this);
		vector.pushBack(value);
		return vector;
	}
	Vector operator+(Vector<T> const &vector) const {
		Vector<T> vectorNew;
		vectorNew.copy(*this);
		for (int i = 0; i < vector.length; i++) {
			vectorNew.pushBack(vector[i]);
		}
		return vectorNew;
	}

	//operator+=
	Vector &operator+=(T const &value) {
		pushBack(value);
		return *this;
	}
	Vector &operator+=(Vector<T> const &vector) {
		for (int i = 0; i < vector.length; i++) {
			pushBack(vector[i]);
		}
		return *this;
	}

	//ctor, dtor
	Vector() {
		clear();
	}
	Vector(int size, T def) {
		resize(size, def);
	}
	~Vector() {
		delete[] data;
	}

	//copy ctor
	Vector(Vector const &vector) {
		copy(vector);
	}

	//init list ctor
	Vector(std::initializer_list<T> const &values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}

	//unit test
	static void Test() {
		//= test
		Vector<T> a;
		Vector<T> b;
		b = a;

		//copy ctor test
		Vector<T> c;
		Vector<T> d = c;

		//init list ctor test
		Vector values({1, 2, 3, 4, 5, 6});
		for (int i = 0; i < 6; i++) {
			assert(values[i] == i + 1);
		}

		//= init list test
		Vector e = {1, 2, 3, 5, 6};
		for (int i = 0; i < 6; i++) {
			assert(values[i] == i + 1);
		}

		//= misc test
		values = Vector({1, 2}) + 3 + 4 + Vector({5}) + Vector({6, 7, 8, 9, 10});
		values += {11, 12, 13};
		for (int i = 0; i < 13; i++) {
			assert(values[i] == i + 1);
		}
	}
};

template <typename T>
Vector<T> operator+(T const &value, Vector<T> const &vector) {
	return vector + value;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, Vector<T> const &vector) {
	stream << "[" << vector.length << "]";
	stream << "(";
	for (int i = 0; i < vector.length; i++) {
		stream << vector[i];
		if (i < vector.length - 1) {
			stream << ", ";
		}
	}
	stream << ")";

	return stream;
}

} // namespace Container

#endif