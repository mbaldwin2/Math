#pragma once

#ifndef MATH_GEOMETRY_POIspaceT
#define MATH_GEOMETRY_POIspaceT

#include <Math/Prefix.h>

namespace Math {
	namespace Geometry {

		template<typename T, uint32_t space=2>
		class Point {
		public:
			Point();
			Point(const Vector::Template<T,space> & u) {
				operator=(u);
			}
			~Point();

			float GetDistance(const Point<T,space> & u) const { return (point - u.point).GetLength(); }

			bool operator == (const Point<T,space> & u) const {
				for(uint32_t i=0;i<space;i++)
					if( u.point[i] != point[i] ) return false;
				return true;
			}

			bool operator != (const Point<T,space> & u) const { return !operator==(u); }

			typename Point<T,space> & operator = (const Point<T,space> & u) {
				for(uint32_t i=0;i<space;i++) point[i] = u.point[i];
				return *this;
			}

			typename Point<T,space> & operator += (const Point<T,space> & u) {
				for(uint32_t i=0;i<space;i++) point[i] += u.point[i];
				return *this;
			}

			typename Point<T,space> & operator -= (const Point<T,space> & u) {
				for(uint32_t i=0;i<space;i++) point[i] -= u.point[i];
				return *this;
			}

			typename Point<T,space> & operator *= (T const & r) {
				for(uint32_t i=0;i<space;i++) point[i] *= r;
				return *this;
			}

			T & operator [] (uint32_t i) { return point[i]; }
			const T & operator [] (uint32_t i) const { return point[i]; }

			T * operator & (void) { return reinterpret_cast<T *>(point); }
			const T * operator & (void) const { return reinterpret_cast<T *>(point); }
		protected:
			Vector::Template<T,space> point;
		};


		template<typename T, uint32_t space=2>
		class Line {
		public:
			Line();
			~Line();

			float GetSlope() const {
				float dy,dx;

				dy = terminal[1] - start[1];
				dx = terminal[0] - start[0];
				if( Equals<float>(dx,0.0f) ) return Infinity<float>();
				return dy/dx;
			}

			float GetLength() const { return (terminal-start).GetLength(); }
			typename Line<T,N> Scale(T const & r) const {
				Line<T,N> line;
				line.start = start*r;
				line.terminal = terminal*r;
				return line;
			}

			typename Line<T,N> GetUnit() const { return Scale( T(1)/GetLength() ); }
			typename Point<T,N> GetMidPoint() const {
				Point<T,N> mid;
				for(uint32_t i=0;i<space;i++) mid[i] = (start[i] + terminal[i])/T(2);
				return mid;
			}

			typename Point<T,space> & GetStart() { return start; }
			typename const Point<T,space> & GetStart() const { return start; }
			typename Point<T,space> & GetTerminal() { return terminal; }
			typename const Point<T,space> & GetTerminal() const { return terminal; }
		protected:
			Point<T,space> start, terminal;
		};



		template<typename T, uint32_t N, uint32_t space=2>
		class Shape {
		public:
			Shape() {}
			~Shape() {}

			virtual T GetArea() const =0;
			virtual T GetPerimeter() const =0;
			virtual Vector::Template<T,space> GetNormal() const=0;
			virtual Point<T,N> GetMidPoint() const =0;

			typename Line<T,space> & operator [] (uint32_t i) { return lines; }
			typename const Line<T,space> & operator [] const (uint32_t i) { return lines; }
		private:
			Line<T,space> lines[N];
		};


		template<typename T, uint32_t space=2>
		class Triangle {
		public:
			Triangle() {}
			~Triangle() {}
		protected:
		};
	}
}

#endif // ending MATH_GEOMETRY_POIspaceT //