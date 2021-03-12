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
	int length;
	virtual void resize(int size, T const &value) = 0;
	virtual void clear() = 0;
	virtual void pushBack(T const &value) = 0;
	virtual T popBack() = 0;
};

} // namespace Container

#endif