#pragma once

#ifndef MATH_MATRIX
#define MATH_MATRIX

#include <Math/Prefix.h>
#include <Math/Algebra/Vector.h>

#include <Stringz/Utility.h>

namespace Math {
	namespace Matrix {
		template<typename T, int rows, int columns>
		class Template {
		public:
			Template( const std::initializer_list< Vector::Template<T,columns> > & list ) {
				if( list.size() != rows )
					throw std::exception("Invalid initializer list provided, size mismatch");

				int i=0;
				for(const auto & item : list) e[i++] = item;
			}

			Template(T const & u =T(1)) {
				for(int i=0;i<rows;i++){
					for(int j=0;j<columns;j++)
						e[i][j] = (i+j)%2 ? T(0) : u;
				}
			}

			~Template() {}

			int Rows() const { return rows; }
			int Columns() const { return columns; }

			bool HasDeterminant() const { return rows == columns; }
			std::string ToString() const {
				std::string string = "[";
				for(int i=0;i<rows;i++)
					string += Stringz::Strip(Row(i).ToString(), "<>") + "; ";
				return string.substr(0,string.length()-2) + "]";
			}

			typename Vector::Template<T,columns> Row(int r) const {
				Vector::Template<T,columns> row;
				for(int i=0;i<columns;i++)
					row[i] = e[r][i];
				return row;
			}

			typename Vector::Template<T,rows> Column(int c) const {
				Vector::Template<T,rows> column;
				for(int i=0;i<rows;i++)
					column[i] = e[i][c];
				return column;
			}

			typename Template<T,rows-1,columns-1> Reduced(int r, int c) const {
				Template<T,rows-1,columns-1> reduced;
				int s=0,t=0;
				for(int i=0;i<rows;i++){
					if(i == r) continue;
					for(int j=0;j<columns;j++){
						if(j == c) continue;
						else reduced[s][t++] = this->e[i][j];
					}
				}
				return reduced;
			}

			typename Vector::Template<T,columns> & operator [] (int r) { return e[r]; }
			typename const Vector::Template<T,columns> & operator [] (int r) const { return e[r]; }

			typename Vector::Template<T,columns> * operator & () { return e; }
			typename const Vector::Template<T,columns> * operator & () const { return e; }

			typename Template<T,rows,columns> & operator = (const Template<T,rows,columns> & M) {
				for(int i=0;i<rows;i++) e[i] = M[i];
				return *this;
			}

			typename Template<T,rows,columns> & operator += (const Template<T,rows,columns> & M) {
				for(int i=0;i<rows;i++) e[i] += M[i];
				return *this;
			}

			typename Template<T,rows,columns> & operator -= (const Template<T,rows,columns> & M) {
				for(int i=0;i<rows;i++) e[i] -= M[i];
				return *this;
			}

			typename Template<T,rows,columns> & operator *= (T const & r) {
				for(int i=0;i<rows;i++) e[i] *= r;
				return *this;
			}

			typename Vector::Template<T,rows> operator * ( const Vector::Template<T,columns> & u ) const {
				Vector::Template<T,rows> v;
				for(int i=0;i<rows;i++) v[i] = operator[](i)*u;
				return v;
			}
			
			typename Template<T,rows,columns> operator + (const Template<T,rows,columns> & M) const {
				Template<T,rows,columns> A = *this;
				return A += M;
			}

			typename Template<T,rows,columns> operator - (const Template<T,rows,columns> & M) const {
				Template<T,rows,columns> A = *this;
				return A -= M;
			}

			typename Template<T,rows,columns> operator * (T const & r) const {
				Template<T,rows,columns> A = *this;
				return A *= r;
			}

		protected:
			Vector::Template<T,columns> e[rows];
		};

		template<typename T>
		class Template<T,1,1> {
		public:
			Template(const T & x=T(1)) { e[0][0] = x; }
			Template(const std::initializer_list< Vector::Template<T,1> > & list){
				if( list.size() != 1 )
					throw std::exception("Initializer list has invalid length");
				e[0] = *list.begin();
			}
			~Template() {}
			typename Vector::Template<T,1> & operator [] (int i) { return e[i]; }
			typename const Vector::Template<T,1> & operator [] (int i) const { return e[i]; }
			typename Vector::Template<T,1> * operator & () {return e;}
			typename const Vector::Template<T,1> * operator & () const {return e;}
			int Rows() const { return 1; }
			int Columns() const { return 1; }
			bool HasDeterminant() const { return true; }
			typename Vector::Template<T,1> Row(int i) const { return e[i]; }
			typename Vector::Template<T,1> Column(int i) const { return e[i]; }
			typename Template<T,1,1> Reduced(int r,int c) const {return Template<T,1,1>(T(0));}
			bool operator == (const Template<T,1,1> & M) const { return e[0] == M.e[0]; }
			bool operator != (const Template<T,1,1> & M) const { return !operator==(M); }
			typename Template<T,1,1> operator = (const Template<T,1,1> & M) {
				e[0] = M.e[0];
				return *this;
			}
			typename Template<T,1,1> operator += (const Template<T,1,1> & M) {
				e[0] += M.e[0];
				return *this;
			}
			typename Template<T,1,1> operator -= (const Template<T,1,1> & M) {
				e[0] -= M.e[0];
				return *this;
			}
			typename Template<T,1,1> operator *= (T const & r) {
				e[0] *= r;
				return *this;
			}

			typename Template<T,1,1> operator + (const Template<T,1,1> & M) const {
				Template<T,1,1> A = *this;
				return A += M;
			}
			typename Template<T,1,1> operator - (const Template<T,1,1> & M) const {
				Template<T,1,1> A = *this;
				return A -= M;
			}
			typename Template<T,1,1> operator * (T const & r) const {
				Template<T,1,1> A = *this;
				return A *= r;
			}
			std::string ToString() const { return "["+Stringz::Strip(e[0].ToString(),"<>")+"]"; }
		protected:
			Vector::Template<T,1> e[1];
		};

		template<typename T, int rows>
		class Template<T,rows,1> {
		public:
			Template(const T & x=T(1)) { e[0][0] = x; }
			Template(const std::initializer_list<Vector::Template<T,1>> & list){
				if(list.size() != rows) throw std::exception("Invalid list size, must equal rows!");
				int i=0;
				for(const auto & item : list) e[i++] = item;
			}
			~Template() {}
			typename Vector::Template<T,1> & operator [] (int i) { return e[i]; }
			typename const Vector::Template<T,1> & operator [] (int i) const { return e[i]; }
			typename Vector::Template<T,1> * operator & () {return e;}
			typename const Vector::Template<T,1> * operator & () const {return e;}
			int Rows() const { return rows; }
			int Columns() const { return 1; }
			bool HasDeterminant() const { return rows == 1; }
			typename Template<T,rows,1> Reduced(int r, int c) const {return Template<T,rows,1>();}
			typename Vector::Template<T,1> Row(int i) const { return Vector::Template<T,1>(); }
			typename Vector::Template<T,rows> Column(int i) const { return Vector::Template<T,rows>(); }
			bool operator == (const Template<T,rows,1> & M) const { return true; }
			bool operator != (const Template<T,rows,1> & M) const { return false; }
			typename Template<T,rows,1> operator = (const Template<T,rows,1> & M) {return *this;}
			typename Template<T,rows,1> operator += (const Template<T,rows,1> & M) {return *this;}
			typename Template<T,rows,1> operator -= (const Template<T,rows,1> & M) {return *this;}
			typename Template<T,rows,1> operator *= (T const & r) {return *this;}
			typename Template<T,rows,1> operator + (const Template<T,rows,1> & M) const {return Template<T,rows,1>();}
			typename Template<T,rows,1> operator - (const Template<T,rows,1> & M) const {return Template<T,rows,1>();}
			typename Template<T,rows,1> operator * (T const & r) const {return Template<T,rows,1>();}
			std::string ToString() const {
				std::string string = "[";
				for(int i=0;i<rows;i++)
					string += Stringz::Strip(e[i].ToString(),"<>") + "; ";
				return string.substr(0,string.length()-2) + "]";
			}
		protected:
			Vector::Template<T,1> e[rows];
		};

		template<typename T, int columns>
		class Template<T,1,columns> {
		public:
			Template(const T & x=T(1)): e() {}
			Template(const std::initializer_list< Vector::Template<T,columns> > & list){
				if( list.size() != 1 ) throw std::exception("Invalid initializer list size, must be 1");
				e[0] = *list.begin();
			}
			~Template() {}
			typename Vector::Template<T,columns> operator [] (int i) { return Vector::Template<T,columns>(); }
			typename const Vector::Template<T,columns> operator [] (int i) const { return Vector::Template<T,columns>(); }
			typename Vector::Template<T,columns> * operator & () {return e;}
			typename const Vector::Template<T,columns> * operator & () const {return e;}
			int Rows() const { return 1; }
			int Columns() const { return columns; }
			bool HasDeterminant() const { return true; }
			typename Vector::Template<T,columns> Row(int i) const { return Vector::Template<T,columns>(); }
			typename Vector::Template<T,1> Column(int i) const { return Vector::Template<T,1>(); }
			typename Template<T,1,columns> Reduced(int r, int c) const { return Template<T,1,columns>(); }
			bool operator == (const Template<T,1,columns> & M) const { return e[0] == M.e[0]; }
			bool operator != (const Template<T,1,columns> & M) const { return !operator==(M); }
			typename Template<T,1,columns> operator = (const Template<T,1,columns> & M) {
				e[0] = M.e[0];
				return *this;
			}
			typename Template<T,1,columns> operator += (const Template<T,1,columns> & M) {
				e[0] += M.e[0];
				return *this;
			}
			typename Template<T,1,columns> operator -= (const Template<T,1,columns> & M) {
				e[0] -= M.e[0];
				return *this;
			}
			typename Template<T,1,columns> operator *= (T const & r) {
				e[0] *= r;
				return *this;
			}
			typename Template<T,1,columns> operator + (const Template<T,1,columns> & M) const {
				Template<T,1,columns> u = *this;
				return u += M;
			}
			typename Template<T,1,columns> operator - (const Template<T,1,columns> & M) const {
				Template<T,1,columns> u = *this;
				return u -= M;
			}
			typename Template<T,1,columns> operator * (T const & r) const {
				Template<T,1,columns> u = *this;
				return u *= r;
			}
			std::string ToString() const {
				std::string string = "[";
				string += Stringz::Strip(e[0].ToString(),"<>") + ", ";
				return string.substr(0, string.length()-2) + "]";
			}
		protected:
			Vector::Template<T,columns> e[1];
		};

		template<typename T, int N>
		T Trace(const Template<T,N,N> & M){
			T trace = T();
			for(int i=0;i<N;i++) trace += M[i][i];
			return trace;
		}

		template<typename T, int N>
		T Determinant(const Template<T,N,N> & M) {
			switch(N) {
			case 0: return T();
			case 1: return M[0][0];
			default: break;
			}

			int k=0;
			T det = T();
			for(uint32_t i=0;i<N;i++){
				k = i%2 ? -1 : 1;
				det += k*M[0][i]*Determinant( M.Reduced(0,i) );
			}
			return Abs(det) <= Epsilon<T>() ? T() : det;
		}

		template<typename T, int rows, int columns>
		typename Template<T,columns,rows> Transpose(const Template<T,rows,columns> & M) {
			Template<T,columns,rows> transpose;
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					transpose[j][i] = M[i][j];
				}
			}
			return transpose;
		}

		template<typename T, int rows, int common, int columns>
		typename Template<T,rows,columns> Transform(const Template<T,rows,common> & A, const Template<T,common,columns> & B){
			Template<T,rows,columns> C;
			Template<T,columns,common> Bt = Transpose(B);
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					C[i][j] = A[i]*Bt[j];
					AutoCorrect(C[i][j]);
				}
			}
			return C;
		}

		template<typename T, int N>
		typename Template<T,N,N> Identity() {
			Template<T,N,N> ident;
			for(int i=0;i<N;i++) for(int j=0;j<N;j++) ident[i][j] = i==j ? T(1) : T(0);
			return ident;
		}

		template<typename T, int rows, int columns>
		typename Template<T,rows,columns> Zero() { return Template<T,rows,columns>(T(0)); }

		template<typename T, int N, int columns>
		typename Template<T,N,N> Inverse(const Template<T,N,columns> & master) {
			Template<T,N,N> inverse;
			T det = Determinant(master);
			int k=0;
			if( Equals<T>(det,T()) ) throw std::exception("Unable to invert dependant matrix");
			switch(N){
			case 1: inverse[0][0] = 1/master[0][0];
				break;
			default:
				for(int i=0;i<N;i++) {
					for(int j=0;j<N;j++) {
						k = (i+j)%2 ? -1 : 1;
						auto & index = inverse[i][j];
						index = k*Determinant(master.Reduced(i,j))/det;
						AutoCorrect(index);
					}
				}
				break;
			}
			return Transpose(inverse);
		}

		namespace Rotate {

			template<typename T>
			typename Matrix::Template<T,2,2> Dim2 (T const & angle) {
				Matrix::Template<T,2,2> R;
				R[0][0] = Cos(angle), R[0][1] = -Sin(angle);
				R[1][0] = Sin(angle), R[1][1] = Cos(angle);
				return R;
			}

			template<typename T>
			typename Matrix::Template<T,3,3> X(T const & angle){
				Matrix::Template<T,3,3> R(T(0));
				R[0][0] = T(1);
				R[1][1] = Cos(angle), R[1][2] = -Sin(angle);
				R[2][1] = Sin(angle), R[2][2] = Cos(angle);
				return R;
			}

			template<typename T>
			typename Matrix::Template<T,3,3> Y(T const & angle){
				Matrix::Template<T,3,3> R(T(0));
				R[0][0] = Cos(angle), R[0][2] = Sin(angle);
				R[1][1] = T(1);
				R[2][0] = -Sin(angle), R[2][2] = Cos(angle);
				return R;
			}

			template<typename T>
			typename Matrix::Template<T,3,3> Z(T const & angle) {
				Matrix::Template<T,3,3> R(T(0));
				R[0][0] = Cos(angle), R[0][1] = -Sin(angle);
				R[1][0] = Sin(angle), R[1][1] = Cos(angle);
				R[2][2] = T(1);
				return R;
			}

		}

#define MatrixDefine(t,T) \
		typedef Template<t,1,1> T##1x1; \
		typedef Template<t,1,2> T##1x2;\
		typedef Template<t,1,3> T##1x3;\
		typedef Template<t,1,4> T##1x4;\
\
		typedef Template<t,2,1> T##2x1;\
		typedef Template<t,2,2> T##2x2;\
		typedef Template<t,2,3> T##2x3;\
		typedef Template<t,2,4> T##2x4;\
\
		typedef Template<t,3,1> T##3x1;\
		typedef Template<t,3,2> T##3x2;\
		typedef Template<t,3,3> T##3x3;\
		typedef Template<t,3,4> T##3x4;\
\
		typedef Template<t,4,1> T##4x1;\
		typedef Template<t,4,2> T##4x2;\
		typedef Template<t,4,3> T##4x3;\
		typedef Template<t,4,4> T##4x4

		MatrixDefine(float,Float);
		MatrixDefine(double,Double);
		MatrixDefine(long double,LDouble);
		MatrixDefine(int8_t, Byte);
		MatrixDefine(uint8_t, UByte);
		MatrixDefine(int16_t, Word);
		MatrixDefine(uint16_t, UWord);
		MatrixDefine(int32_t, Int);
		MatrixDefine(uint32_t, UInt);
		MatrixDefine(int64_t, Long);
		MatrixDefine(uint64_t, ULong);

	}
}

#endif // ending MATH_MATRIX //