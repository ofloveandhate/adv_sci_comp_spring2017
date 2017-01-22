// provides the code from p.124 Discovering Modern C++

#pragma once

#include <memory>
#include <stdexcept>

namespace advscicomp {

	template<typename T>
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

