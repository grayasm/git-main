/* benchmarking parallel matrix multiplication.

   1 2 3       a b c     1a+2d+3g  1b+2e+3h  1c+2f+3i
   4 5 6   *   d e f  =  4a+5d+6g  4b+5e+6h  4c+5f+6i
   7 8 9       g h i     7a+8d+9g  7b+8e+9h  7c+8f+9i

   1 2 3     1 2 3     30   36   42
   4 5 6  *  4 5 6  =  66   81   96
   7 8 9     7 8 9    102  126  150

   BENCHMARK is fixed value for both programs.
   As it stands right now, this sequential version is SLOOOOWWW. :)
   Most probably because of the overhead of "fork-join"
*/

#include <stdio.h>
#include <exception>
#include <cstring>
#include <vector>


template<typename T>
class tmatrix
{
public:
	tmatrix(int row, int col)
		: m_row(row),
		  m_col(col)
	{
		if(row <=0 || row != col) throw "error: ctor";
		m_vec.resize(row*col, T(0));
	}
	~tmatrix(){}
	tmatrix& operator=(const tmatrix& tc)
	{
		if (this != &tc) m_vec = tc.m_vec;
		return *this;
	}
	tmatrix& operator*(const tmatrix& tc)
	{
		if (m_row != tc.m_row ||
		    m_col != tc.m_col)
			throw "error: operator*";

		std::vector<T> tmp;
		tmp.resize(m_row*m_col, T(0));

		int r,c,i;
#pragma omp parallel for shared(tmp) private(r,c,i)
		for (r=0; r<m_row; ++r)
		{
			for (c=0; c<m_col; ++c)
			{
				for (i=0; i<m_col; ++i)
				{
					tmp[r*m_col + c] +=
						m_vec[r*m_col + i] * tc.m_vec[i*m_col + c];
				}
			}
		}
/*-- End of omp parallel for --*/

		m_vec = tmp;
		return *this;
	}
	void set(int r, int c, T val) { m_vec[r*m_col+c] = val; }
	const T& get(int r, int c) const { return m_vec[r*m_col+c]; }
	void print() const
	{
		for(int r=0; r<m_row; ++r)
		{
			for(int c=0; c<m_col; ++c)
			{
				printf("\t%.2f", m_vec[r*m_row+c]);
			}
			printf("\n");
		}
	}
private:
	int m_row;
	int m_col;
	std::vector<T> m_vec;
}; // class

int main(int argc, char* argv[])
{
	tmatrix<double> m1(3, 3);
	tmatrix<double> m2(3, 3);

	for (int r=0; r<3; ++r)
	{
		for (int c=0; c<3; ++c)
		{
			double val = r*3 + c +1;
			m1.set(r,c, val);
			m2.set(r,c, val);
		}
	}

	printf("m1=\n");
	m1.print();
	printf("\nm2=\n");
	m2.print();

	// the benchmark, 5 mil
const int BENCHMARK=5000000;
	for(int i=0; i<BENCHMARK; ++i)
	{
		m1 = m2;
		m1*m2;
	}

	printf("\nrez=\n");
	m1.print();

	return 0;
}
