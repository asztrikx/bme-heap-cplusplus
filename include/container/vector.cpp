#include "vector.h"

namespace Container {

template <typename T>
Vector<T> operator+(T const &value, Vector<T> const &vector) {
	return vector + value;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, Vector<T> const &vector) {
	stream << "[" << vector.length() << "]";
	stream << "(";
	for (int i = 0; i < vector.length(); i++) {
		stream << vector[i];
		if (i < vector.length() - 1) {
			stream << ", ";
		}
	}
	stream << ")";

	return stream;
}

} // namespace Container