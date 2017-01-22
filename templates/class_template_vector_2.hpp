// provides the code from p.125 Discovering Modern C++

#pragma once

#include <memory>
#include <stdexcept>

namespace advscicomp {


	struct col_major
	{ };
	struct row_major
	{ };

	struct stack
	{ };
	struct heap
	{ };


	/**
	\brief This custom vector class is far from complete, but shows default template parameters, etc
	*/
	template<typename T = double, typename Orientation = col_major, typename Where = heap>
	class vector
	{
public: 
		explicit vector(int size) : size_(size), data_(new T[size_])
		{}

		vector(const vector& other) :
			size_(other.size_), data_(new T[size_])
		{
			std::copy(&other.data_[0], other.data_[other.size_], &data_[0]);
		}


		int size() const 
		{
			return size_;
		}

		const T& operator[](int i) const
		{
			check_index(i);
			return data_[i];
		}

		void check_index(int i) const
		{
			if (i >= size_ || i < 0)
				throw std::runtime_error("trying to access index out of range");
		}

private: 
		int size_;
		std::unique_ptr<T[]> data_;
	};

}

