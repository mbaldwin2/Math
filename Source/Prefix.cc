#define API_EXPORT
#include <Math/Prefix.h>

namespace Math {
	API uint64_t Factorial(uint64_t n) {
		if(n==0) return 1;
		uint64_t factorial = 1;
		while(n>0) factorial *= n--;
		return factorial;
	}

	API uint64_t Choose(uint32_t n, uint32_t p) {
		if(n < p) return Choose(p,n); // to save it from returning a zero in the future //
		return Factorial(n)/(Factorial(p)*Factorial(n-p));
	}

	API uint64_t Fibonacci(uint32_t n) {
		uint64_t fib = 0, a = 0, b = 1;
		for(uint32_t i=0;i<n;i++) {
			fib = a + b;
			a = b, b = fib;
		}
		return fib;
	}
}