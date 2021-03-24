#ifndef CONTAINER_H
#define CONTAINER_H

namespace Container {

namespace Exception {
	class Exception {};
	class IndexOutofbounds {};
	class DataLoose {};
} // namespace Exception

template <typename T>
class Container {
  public:
	virtual ~Container() {
	}

	int length;
	virtual void resize(int size, T const &value) = 0;
	virtual void clear() = 0;
	virtual void pushBack(T const &value) = 0;
	virtual T popBack() = 0;

	virtual Container<T> &operator=(Container<T> const &Container) = 0;
	virtual Container<T> &operator=(std::initializer_list<T> const &values) = 0;
	virtual T &operator[](int index) const = 0;
	virtual Container<T> operator+(T const &value) const = 0;
	virtual Container<T> operator+(Container<T> const &Container) const = 0;
	virtual Container<T> &operator+=(T const &value) = 0;
	virtual Container &operator+=(Container<T> const &Container) = 0;
};

} // namespace Container

#endif