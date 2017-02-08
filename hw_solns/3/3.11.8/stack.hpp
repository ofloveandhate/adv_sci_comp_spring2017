// the stack type for 
// problem 3.11.8 from Discovering Modern C++
//
// dani brake
// notre dame
// acms
// 2017
// danielthebrake@gmail.com

#pragma once

#include <stdexcept>
#include <memory>


namespace advscicomp{
/**
\brief A fixed-size stack

\tparam T the held type of the stack
\tparam N the size of the stack
*/
template <class T, int N = 4096>
class Stack {
public:

  // the default constructor.  takes no arguments
	Stack() : current_size_(0), entries_(std::make_unique<T[]>(N))
	{ }


	// copy constructor
	Stack(Stack const& other) : Stack() // delegate to the default constructor
	{
	  this->current_size_ = other.current_size_;
	  for (int ii=0; ii<current_size_; ++ii)
	  	entries_[ii] = other.entries_[ii];
	}


	//assignment operator
	Stack& operator=(Stack const& other)
	{
		this->current_size_ = other.current_size_;
	  for (int ii=0; ii<current_size_; ++ii)
	  	entries_[ii] = other.entries_[ii];

	  return *this;
	}


  //Destructor
	~Stack() = default;


  // Show the top element
	const T& Top() const {
		if (current_size_==0)
			throw range_error("accessing top element of empty stack!!!");
		return entries_[current_size_-1];
	}

  // Show the bottom element
	const T& Bottom() const {
		if (current_size_==0)
			throw range_error("accessing bottom element of empty stack!!!");
		return entries_[0];
	}

  //remove top element
	void Pop()
	{
		if (current_size_==0)
  		throw underflow_error("popping off empty stack");
		--current_size_;
	}


  //add new element to top of stack
  void Push(T const& t)
  {
  	if (current_size_==N)
  		throw overflow_error("pushing onto full stack");
  	entries_[current_size_++] = t;
  } 


  //delete all entries
  void Clear()
  {
  	current_size_ = 0;
  }


  //number of elements
  int Size() const {
  	return current_size_;
  }

  //whether stack is full
  bool IsFull() const {
  	return current_size_==N;
  }

  //whether stack is empty
  bool IsEmpty() const {
  	return current_size_==0;
  }

  auto MaxSize() const
  {
  	return N;
  }


  struct range_error : public std::range_error
  { 
  	template <typename ...Ts>
  	range_error(Ts ...ts) : std::range_error(ts...){};
  };

  struct overflow_error : public std::overflow_error
  {
  	template <typename ...Ts>
  	overflow_error(Ts ...ts) : std::overflow_error(ts...){}; 
  };

  struct underflow_error : public std::underflow_error
  { 
  	template <typename ...Ts>
  	underflow_error(Ts ...ts) : std::underflow_error(ts...){}; 
  };

  using value_type = T;

private:

	int current_size_; 
	std::unique_ptr<T[]> entries_;
};

} // namespace advscicomp