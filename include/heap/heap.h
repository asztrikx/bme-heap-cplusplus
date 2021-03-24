#ifndef HEAP_H
#define HEAP_H

namespace Heap {

namespace Exception {
	class Exception {};
	class IndexOutofbounds : public Exception {};
	class Empty : public Exception {};
} // namespace Exception

template <typename T>
class Heap {
  public:
	virtual ~Heap() {
	}

	virtual void clear() = 0;
	virtual void insert(T const &value) = 0;
	virtual void insert(Container::Container<T> const &values) = 0;
	virtual T top() const = 0;
	virtual T pop() = 0;
	virtual bool empty() const = 0;
	virtual int length() const = 0;
};

} // namespace Heap

#endif