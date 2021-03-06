/**
\file rational.hpp

Dani Brake, 2017
University of Notre Dame
*/

#pragma once

#include <iostream>
#include <cmath>



namespace advscicomp{


/**
 * A Rational number class, using integers for the numerator and denominator
 *
 * this class as provided is INCORRECT, deliberately.  the arithmetic is incorrect.
 */
template<typename T = int>
class Rational
{
public:
	// default constructor.  makes the number 0 by default
	Rational<T>() : numerator_(0), denominator_(1)
	{}

	// constructor taking two integers, and making the corresponding Rational.
	Rational<T>(T n, T d) : numerator_(n), denominator_(d)
	{
	}

	// constructor taking a single integer, so the Denominator is 1
	Rational<T>(T i) : numerator_(i), denominator_(1)
	{}



	///////////////
	//
	//    Operators
	///
	////////////////



	// multiplication =
	Rational<T>& operator*=(Rational<T> const& rhs)
	{
		numerator_ *= rhs.Numerator(); // this is the left hand side's numerator
		denominator_ *= rhs.Denominator();
		return *this;
	}

	// division =
	Rational<T>& operator/=(Rational<T> const& rhs)
	{
		numerator_ *= rhs.Numerator(); // this is the left hand side's numerator
		denominator_ *= rhs.Denominator();
		return *this;
	}

	// addition =
	Rational<T>& operator+=(Rational<T> const& rhs)
	{
		numerator_ += rhs.Numerator(); // this is the left hand side's numerator
		denominator_ += rhs.Denominator();
		return *this;
	}

	// subtraction =
	Rational<T>& operator-=(Rational<T> const& rhs)
	{
		numerator_ -= rhs.Numerator(); // this is the left hand side's numerator
		denominator_ -= rhs.Denominator();
		return *this;
	}

	// negation
	Rational<T> operator-() const
	{
		return Rational<T>(-Numerator(), -Denominator());
	}


	friend
	inline
	Rational<T> operator*(Rational<T> lhs, Rational<T> const& rhs)
	{
		lhs*=rhs;
		return lhs;
	}

	friend
	inline
	Rational<T> operator/(Rational<T> lhs, Rational<T> const& rhs)
	{
		lhs*=rhs;
		return lhs;
	}

	friend
	inline
	Rational<T> operator+(Rational<T> lhs, Rational<T> const& rhs)
	{
		lhs*=rhs;
		return lhs;
	}

	friend
	inline
	Rational<T> operator-(Rational<T> lhs, Rational<T> const& rhs)
	{
		lhs*=rhs;
		return lhs;
	}




	// conversion to double.  marked as explicit, requires C++11
	explicit operator double()
	{
		return double(numerator_)/double(denominator_);
	}

	friend 
	inline
	std::istream& operator>>(std::istream& in, Rational<T> & r)
	{
		// this function is clearly wrong.
		return in;
	}

	friend
	inline
	std::ostream& operator<<(std::ostream& out, Rational<T> const& r)
	{
		out << r.Numerator() << "/" << r.Denominator();
		return out;
	}
private:
	T numerator_;
	T denominator_;

public:
	// getter for the numerator of the rational number
	T Numerator() const
	{ return numerator_;}

	// getter for the denominator of the rational number
	T Denominator() const
	{ return denominator_;}
};










	/////////////////
	//
	//  some function overloads
	//
	//////////////



	// overload the pow function
	template <typename T>
	inline Rational<T> pow(Rational<T> const& r, unsigned p)
	{
		using std::pow;
		return Rational<T>(pow(r.Numerator(),p),pow(r.Denominator(),p));
	}

	// overload the abs function
	template <typename T>
	inline Rational<T> abs(Rational<T> const& r)
	{
		using std::abs;
		return Rational<T>(abs(r.Numerator()),abs(r.Denominator()));
	}

} // namespace