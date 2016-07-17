#pragma once
#ifndef PRODIGY_UTILITY_H
#define PRODIGY_UTILITY_H

// prodigy utility
// ver 1.0.0.160713a

#pragma region common_include
// ver 1.0.0.160716a
// contain some common #include macros & usings
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;
#include <string>
using std::string;

#pragma endregion

#pragma region logic_operator
// ver 1.0.0.160711a
// add more logic operators

namespace prodigy {
	bool or (const bool &left, const bool &right) {
		return left || right;
	}
	bool and(const bool &left, const bool &right) {
		return left&&right;
	}
	bool not(const bool &arg) {
		return !arg;
	}
	bool xor(const bool &left, const bool &right) {
		return left && !right || !left && right;
	}
	bool xnor(const bool &left, const bool &right) {
		return left&&right || !left && !right;
	}

}

#pragma endregion

#pragma region range
// ver 1.0.0.160713a
// just like python
#include <iterator>
#include <stdexcept>
// dependency: logic_operator 1.0.0.160711a+

namespace prodigy {
	template <typename T>
	class range_class
	{
	public:
		range_class(const T &i_start, const T &i_stop, const T &i_step)
			:start(i_start), stop(i_stop), step(i_step) {
			if (step == 0 || (step < 0 && start < stop) || (step > 0 && start > stop)) {
				throw std::invalid_argument("range step must result in termination");
			}
		}

		class iterator
		{
		public:
			typedef std::input_iterator_tag iterator_category;
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;

			iterator() = delete;
			iterator(const value_type &i_value, const range_class *i_container) :
				value(i_value), container(i_container) {}
			~iterator() = default;

			iterator &operator++() {
				value += container->step;
				if (xnor(container->step > 0, value > container->stop)) {
					value = container->stop;
				}
				return *this;
			}
			iterator operator++(int) {
				iterator ret = *this;
				++*this;
				return ret;
			}
			const reference operator*() {
				return value;
			}
			const pointer operator->() {
				return &value;
			}
			bool operator==(const iterator &right) {
				return value == container->stop;
			}
			bool operator!=(const iterator &right) {
				return !(*this == right);
			}
		
		private:
			value_type value;
			const range_class *container;
		};

		iterator begin() const {
			return iterator(start, this);
		}

		iterator end() const {
			return iterator(stop, this);
		}

	private:
		const T start;
		const T stop;
		const T step;
	};

	template <typename T>
	range_class<T> range(const T &stop) {
		return range_class<T>(T{ 0 }, stop, T{ 1 });
	}

	template <typename T>
	range_class<T> range(const T &start, const T &stop) {
		return range_class<T>(start, stop, T{ 1 });
	}

	template <typename T>
	range_class<T> range(const T &start, const T &stop, const T &step) {
		return range_class<T>(start, stop, step);
	}

}

#pragma endregion

#endif // PRODIGY_UTILITY_H