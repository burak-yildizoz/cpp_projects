#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <queue>

template <class T>
class Average
{
	std::queue<T> _list;
	const size_t _N;
	T _avg;

public:

	Average(size_t N);
	const T& ortalama = _avg;

	void add(T x);
	void reset();
};

// template class needs an explicit instantation of the template
// when a source file is used
// instead, source code is moved to the header

#include <cassert>

template <class T>
Average<T>::Average(size_t N) : _N(N), _avg(0)
{
	assert(N > 0);
}

template <class T>
void Average<T>::add(T x)
{
	_avg = (_avg * _list.size() + x) / (_list.size() + 1);
	_list.push(x);

	if (_list.size() > _N)
	{
		_avg = (_avg * _list.size() - _list.front()) / (_list.size() - 1);
		_list.pop();
	}
}

template <class T>
void Average<T>::reset()
{
	_list = std::queue<T>();
	_avg = 0;
}

#endif // AVERAGE_HPP
