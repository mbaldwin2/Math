#pragma once

#ifndef MATH_COMPLEX
#define MATH_COMPLEX

#include <Math/Prefix.h>

namespace Math {
	namespace Complex {
		template<typename T>
		class Template {
		public:
			Template(T const & x=T(), T const & y=T()) {
				e[0] = x;
				e[1] = y;
			}
			~Template() {}

			T Real() const { return e[0]; }
			T Complex() const { return e[1]; }
			typename Template<T> Conjugate() const { return Template<T>(e[0],-e[1]); }
			float Magnitude() const { return sqrtf( operator*(Conjugate()) ); }
			std::string ToString() const { return std::to_string(e[0]) + " + " + std::to_string(e[1]) + "i"; }

			T & operator [] (uint32_t i) { return e[i]; }
			const T & operator [] (uint32_t i) const { return e[i]; }

			T * operator & () { return e; }
			const T * operator & () const { return e; }

			bool operator == (const Template<T> & c) const {
				return	e[0] == c.e[0]
				and	e[1] == c.e[1];
			}

			bool operator != (const Template<T> & c) const { return !operator==(c); }

			typename Template<T> & operator = (const Template<T> & c) {
				e[0] = c.e[0];
				e[1] = c.e[1];
				return *this;
			}

			typename Template<T> & operator += (const Template<T> & c) {
				e[0] += c.e[0];
				e[1] += c.e[1];
				return *this;
			}

			typename Template<T> & operator -= (const Template<T> & c) {
				e[0] -= c.e[0];
				e[1] -= c.e[1];
				return *this;
			}

			typename Template<T> & operator *= (const Template<T> & c) {
				Template<T> u = *this;
				e[0] = u[0]*c.e[0] - u[1]*c.e[1];
				e[1] = u[1]*c.e[0] + u[0]*c.e[1];
				return *this;
			}

			typename Template<T> & operator + (const Template<T> & c) const {
				Template<T> u = *this;
				return u += c;
			}

			typename Template<T> & operator - (const Template<T> & c) const {
				Template<T> u = *this;
				return u -= c;
			}

			typename Template<T> & operator * (const Template<T> & c) const {
				Template<T> u = *this;
				return u *= c;
			}
		protected:
			T e[2];
		};

		typedef Template<float> Float;
		typedef Template<double> Double;
		typedef Template<long double> LDouble;
		typedef Template<int8_t> Int8;
		typedef Template<uint8_t> UInt8;
		typedef Template<int16_t> Int16;
		typedef Template<uint16_t> UInt16;
		typedef Template<int32_t> Int32;
		typedef Template<uint32_t> UInt32;
		typedef Template<int64_t> Int64;
		typedef Template<uint64_t> UInt64;
	}
}

#endif // ending MATH_COMPLEX //