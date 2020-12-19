#pragma once

#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <Math/Prefix.h>

BEGIN_C
# include <assert.h>
END_C

namespace Math {

	namespace Vector {

		template<typename T, int size>
		class Template {
		public:
			Template() {
				for(int i=0;i<size;i++)
					e[i] = T(0);
			}

			Template(const std::initializer_list<T> & list) {
				int i=0;
				if(size > 0){
					for(const auto & item : list)
						e[i++] = item;
				}
			}

			~Template() {}

			int GetSize() const { return size; }
			double GetLength() const {
				double sum = 0.0;
				for(int i=0;i<size;i++) sum += e[i]*e[i];
				return std::sqrt(sum);
			}

			double GetAngle(const Template<T,size> & u) const {
				double l = GetLength();
				double ul = u.GetLength();
				if( IsZero(l) or IsZero(ul) ) return 0.0;
				return acos(operator*(u)/(ul*l));
			}

			T & operator [] (int i) { return e[i]; }
			const T & operator [] (int i) const { return e[i]; }

			bool operator == (const Template<T,size> & u) const {
				for(int i=0;i<size;i++)
					if( e[i] != u[i] ) return false;
				return true;
			}

			bool operator != (const Template<T,size> & u) const { return !operator==(u); }
			typename Template<T,size> & operator = (const Template<T,size> & u){
				for(int i=0;i<size;i++) e[i] = u[i];
				return *this;
			}

			typename Template<T,size> & operator += (const Template<T,size> & u) {
				for(int i=0;i<size;i++) e[i] += u[i];
				return *this;
			}

			typename Template<T,size> & operator -= (const Template<T,size> & u) {
				for(int i=0;i<size;i++) e[i] = u[i];
				return *this;
			}

			typename Template<T,size> & operator *= (T r){
				for(int i=0;i<size;i++) e[i] *= r;
				return *this;
			}

			typename Template<T,size> & operator /= (T r) {
				for(int i=0;i<size;i++) e[i] /= r;
				return *this;
			}

			T operator * (const Template<T,size> & u) const {
				T sum = T(0);
				for(int i=0;i<size;i++) sum += u[i]*e[i];
				return sum;
			}

			typename Template<T,size> operator + (const Template<T,size> & u) const {
				Template<T,size> v = *this;
				return v += u;
			}

			typename Template<T,size> operator - (const Template<T,size> & u) const {
				Template<T,size> v = *this;
				return v -= u;
			}

			typename Template<T,size> operator * (T r) const {
				Template<T,size> v = *this;
				return v *= r;
			}

			typename Template<T,size> operator / (T r) const {
				Template<T,size> v = *this;
				return v /= r;
			}

			T * operator & () { return e; }
			const T * operator & () const { return e; }

			std::string ToString() const {
				std::string string = "<";
				for(int i=0;i<size;i++)
					string += std::to_string(e[i]) + ", ";
				return string.substr(0,string.length()-2) + ">";
			}

			bool IsZero() const {
				for(int i=0; i<size; i++)
					if( !Equals<T>(e,T()) ) return false;
				return true;
			}

		protected:
			T e[size];
		};

		template<typename T>
		class Template<T,0> {
		public:
			bool IsZero() const { return true; }
			std::string ToString() const { return "<>"; }
			T operator [] (int i) const {return T();}
			T * operator & () { return e; }
			const T * operator & () const { return e; }
			bool operator == (const Template<T,0> & u) const { return true; }
			bool operator != (const Template<T,0> & u) const { return false; }
			Template<T,0> & operator = (const Template<T,0> & u) { return *this; }
			Template<T,0> & operator += (const Template<T,0> & u) { return *this; }
			Template<T,0> & operator -= (const Template<T,0> & u) { return *this; }
			Template<T,0> & operator *= (const Template<T,0> & u) { return *this; }
			Template<T,0> & operator + (const Template<T,0> & u) { return Template<T,0>(); }
			Template<T,0> & operator - (const Template<T,0> & u) { return Template<T,0>(); }
			Template<T,0> & operator * (const Template<T,0> & u) { return Template<T,0>(); }
		protected:
			T e[0];
		};

		typedef Template<float,2> Dim2f;
		typedef Template<float,3> Dim3f;
		typedef Template<float,4> Dim4f;

		typedef Template<double,2> Dim2;
		typedef Template<double,3> Dim3;
		typedef Template<double,4> Dim4;

		typedef Template<int8_t,2> Dim2i8;
		typedef Template<int8_t,3> Dim3i8;
		typedef Template<int8_t,4> Dim4i8;

		typedef Template<int16_t,2> Dim2i16;
		typedef Template<int16_t,3> Dim3i16;
		typedef Template<int16_t,4> Dim4i16;

		typedef Template<int32_t,2> Dim2i32;
		typedef Template<int32_t,3> Dim3i32;
		typedef Template<int32_t,4> Dim4i32;

		typedef Template<int64_t,2> Dim2i64;
		typedef Template<int64_t,3> Dim3i64;
		typedef Template<int64_t,4> Dim4i64;

		typedef Template<uint8_t,2> Dim2ui8;
		typedef Template<uint8_t,3> Dim3ui8;
		typedef Template<uint8_t,4> Dim4ui8;

		typedef Template<uint16_t,2> Dim2ui16;
		typedef Template<uint16_t,3> Dim3ui16;
		typedef Template<uint16_t,4> Dim4ui16;

		typedef Template<int,2> Dim2ui32;
		typedef Template<int,3> Dim3ui32;
		typedef Template<int,4> Dim4ui32;

		typedef Template<uint64_t,2> Dim2ui64;
		typedef Template<uint64_t,3> Dim3ui64;
		typedef Template<uint64_t,4> Dim4ui64;


		template<typename T>
		typename Template<T,3> Cross(const Template<T,3> & A, const Template<T,3> & B) {
			Template<T,3> C;

			C[0] =  (A[1]*B[2] - A[2]*B[1]);
			C[1] = -(A[0]*B[2] - A[2]*B[0]);
			C[2] =  (A[0]*B[1] - A[1]*B[0]);
			return C;
		}

		template<typename T, int size>
		bool IsOrtho(const Template<T,size> & u, const Template<T,size> & v) {return Equals( u*v, T() );}

		template<typename T, int size>
		T Dot(const Template<T,size> & u, const Template<T,size> & v) { return u*v; }

	}

}

#endif // ending MATH_VECTOR //