#pragma once

#ifndef MATH_PREFIX
#define MATH_PREFIX

#include <OS/Prefix.h>
#include <iostream>

BEGIN_C
# include <stdint.h>
# include <math.h>
END_C

#ifndef TAYLOR_LIMIT
# define TAYLOR_LIMIT 25
#else
# undef TAYLOR_LIMIT
# define TAYLOR_LIMIT 25
#endif

namespace Math {

	API uint64_t Factorial(uint64_t);
	API uint64_t Choose(uint32_t, uint32_t);
	API uint64_t Fibonacci(uint32_t);

	template<typename T>
	T Infinity() { return std::numeric_limits<T>::infinity; }

	template<typename T>
	bool IsSigned() {
		if( std::is_same<T,int>::value ) return true;
		if( std::is_same<T,char>::value ) return true;
		if( std::is_same<T,short>::value ) return true;
		if( std::is_same<T,long>::value ) return true;
		if( std::is_same<T,long long>::value ) return true;
		return false;
	}

	template<typename T>
	bool IsFloatingPoint() {
		if( std::is_same<T,float>::value ) return true;
		if( std::is_same<T,double>::value ) return true;
		if( std::is_same<T,long double>::value ) return true;
		return false;
	}



	template<typename T>
	T Epsilon() {
		if(std::is_same<T,float>::value) return 1.0e-15f;
		if(std::is_same<T,double>::value) return 1.0e-15;
		if(std::is_same<T,long double>::value) return 1.0e-15;
		else return 0;
	}

	template<typename T>
	T Pi() {
		if(std::is_same<T,float>::value) return 3.14159265358979323846f;
		if(std::is_same<T,double>::value) return 3.14159265358979323846;
		else return 3;
	}

	template<typename T>
	T Pow(T const & x, T const & p) {
		if( std::is_same<float,T>::value ) return std::powf(x,p);
		if( std::is_same<double,T>::value ) return std::pow(x,p);
		if( std::is_same<long double,T>::value ) return std::powl(x,p);
		T X = T(1);
		for(int i=0;i<p;i++) X *= x;
		return X;
	}

	template<typename T>
	T DoubleFactorial(T const & n) {
		if( IsFloatingPoint<T>() ) throw std::exception("Floating point values generally are not able to become factorials");
		T factorial = T(1);
		for(T i = n;(i > 0) and (i <= n); i-=2) factorial *= i;
		return factorial;
	}

	template<typename T>
	T Euler(T const & x =T(1)) {
		T e = T(0);
		for(int i=0;i<TAYLOR_LIMIT;i++) e += Pow<T>(x,i)/Factorial(i);
		return e;
	}

	template<typename T>
	T Abs(const T & a) { return a<0 ? -a : a; }

	template<typename T>
	T Max(const T & a, const T & b) { return a > b ? a : b; }

	template<typename T>
	T Min(const T & a, const T & b) { return a < b ? a : b; }

	template<typename T>
	bool Equals(const T & a, const T & b) {
		if( std::is_same<T,float>::value ) return Abs<T>(a-b) <= Epsilon<T>();
		else return a == b;
	}

	template<typename T>
	T AutoCorrect(T & r) {
		if( IsFloatingPoint<T>() ){
			if( Abs(r - std::floor(r)) <= Epsilon<T>() )
				r = std::floor(r);
			else if( Abs(r - std::ceil(r)) <= Epsilon<T>() )
				r = std::ceil(r);
		}

		if( ( Abs(r - T(0)) <= Epsilon<T>() ) and (IsSigned<T>() or IsFloatingPoint<T>()) ) r = T(0);
		return r;
	}

	template<typename T>
	T Log(T const & x, T const & b=Euler<T>()){ return AutoCorrect(log(x))/AutoCorrect(log(b)); }

	template<typename T>
	T DegsToRads(T degs) { return AutoCorrect(degs*Math::Pi<T>()/T(180)); }

	template<typename T>
	T RadsToDegs(T rads) { return AutoCorrect(rads*T(180)/Math::Pi<T>()); }

	template<typename T>
	T Sin(T const & angle) {
		T c;
		if( std::is_same<T,float>::value ) c = sinf(angle);
		if( std::is_same<T,double>::value ) c = sin(angle);
		if( std::is_same<T,long double>::value ) c = sinl(angle);
		else c = static_cast<T>(sin(angle));
		AutoCorrect(c);
		return c;
	}

	template<typename T>
	T Csc(T const & angle) { return T(1)/Sin(angle); }

	template<typename T>
	T Cos(T const & angle) {
		T c;
		if( std::is_same<T,float>::value ) c = cosf(angle);
		if( std::is_same<T,double>::value ) c = cos(angle);
		if( std::is_same<T,long double>::value ) c = cosl(angle);
		else c = static_cast<T>(cos(angle));
		AutoCorrect(c);
		return c;
	}

	template<typename T>
	T Sec(T const & angle) { return T(1)/Cos(angle); }

	template<typename T>
	T Tan(T const & angle) { return Sin(angle)/Cos(angle); }

	template<typename T>
	T Cot(T const & angle) { return T(1)/Tan(angle); }

	template<typename T>
	T ArcSin(T const & y) {
		T c;
		if( std::is_same<T,float>::value ) c = asinf(y);
		if( std::is_same<T,double>::value ) c = asin(y);
		if( std::is_same<T,long double>::value ) c = asinl(y);
		else c = static_cast<T>( asin(y));
		AutoCorrect(c);
		return c;
	}

	template<typename T>
	T ArcCos(T const & y) {
		T c;
		if( std::is_same<T,float>::value ) c = acosf(y);
		if( std::is_same<T,double>::value ) c = acos(y);
		if( std::is_same<T,long double>::value ) c = acosl(y);
		else c = static_cast<T>( acos(y));
		AutoCorrect(c);
		return c;
	}

	template<typename T>
	T ArcTan(T const & y) {
		T c;
		if( std::is_same<T,float>::value ) c = atanf(y);
		if( std::is_same<T,double>::value ) c = atan(y);
		if( std::is_same<T,long double>::value ) c = atanl(y);
		else c = static_cast<T>( atanf(y));
		AutoCorrect(c);
		return c;
	}
}

#endif // ending MATH_PREFIX //