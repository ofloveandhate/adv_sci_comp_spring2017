// a driver of test functions for the stack type for 
// problem 3.11.8 from Discovering Modern C++
//
// dani brake
// notre dame
// acms
// 2017
// danielthebrake@gmail.com
#include "stack.hpp"

#include <assert.h>


using namespace advscicomp;

void test_can_construct()
{ 
	Stack<double> my_stack;
}

void test_add_three_doubles()
{
	Stack<double> my_stack;
	my_stack.Push(3.11);
	my_stack.Push(-2.00001);
	my_stack.Push(1e-10);
}

void test_push_full_stack_throws()
{
    Stack<double> my_stack;

    assert(my_stack.IsEmpty());

    for (int ii=0; ii<my_stack.MaxSize(); ++ii) // assumes MaxSize is implemented...
        my_stack.Push(0.0);

    assert(my_stack.IsFull());
    try {
        my_stack.Push(0.0); // this should throw, and the try block then proceeds to the catch block
        assert(false && "stack should have thrown overflow, so we shouldn't have gotten here!!!");
    }
    catch (Stack<double>::overflow_error & e){
        // nothing, this is supposed to happen
    }
}

void test_pop_empty_stack_throws()
{
	Stack<double> my_stack;
	try {
		my_stack.Pop();
		assert(false && "stack should have thrown underflow, so we shouldn't have gotten here!!!");
	}
	catch (Stack<double>::underflow_error & e)
	{}
}

void test_top_empty_stack_throws()
{
	Stack<double> my_stack;
	try {
		my_stack.Top();
		assert(false && "stack should have thrown range_error, so we shouldn't have gotten here!!!");
	}
	catch (Stack<double>::range_error & e)
	{}
}

void test_bottom_empty_stack_throws()
{
	Stack<double> my_stack;
	try {
		my_stack.Bottom();
		assert(false && "stack should have thrown range_error, so we shouldn't have gotten here!!!");
	}
	catch (Stack<double>::range_error & e)
	{}
}


void test_nondefault_size()
{
	Stack<double, 32> my_stack;
	assert(my_stack.MaxSize() == 32);
}

void test_copy_no_aliasing()
{
	Stack<double> s1;
	s1.Push(2.4);

	Stack<double> s2(s1);

	s2.Push(5.1);

	assert(s2.Top() == 5.1);
	assert(s1.Top() == 2.4);
	assert(s1.Size() == 1);
	assert(s2.Size() == 2);
}

void test_assign_no_aliasing()
{
	Stack<double> s1, s2;
	s1.Push(2.4);

	s2 = s1;

	s2.Push(5.1);

	assert(s2.Top() == 5.1);
	assert(s1.Top() == 2.4);
	assert(s1.Size() == 1);
	assert(s2.Size() == 2);
}



int main()
{
	test_can_construct();
	test_add_three_doubles();
	test_push_full_stack_throws();
	test_top_empty_stack_throws();
	test_bottom_empty_stack_throws();
	test_nondefault_size();
	test_copy_no_aliasing();
	test_assign_no_aliasing();
}