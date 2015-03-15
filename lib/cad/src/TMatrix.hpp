/*
  Copyright (C) 2013 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com

*/



#ifndef __TMatrix_hpp__
#define __TMatrix_hpp__




#include "TVector.hpp"
#include "exception.hpp"
#include "string.hpp"
#include "math.hpp"
#include "strconv.hpp"




namespace cad
{

template<typename T, size_t rows, size_t columns>
class TMatrix
{
public:
	TMatrix()
	{
		if(rows == 0 || columns == 0)
			throw misc::exception(U("Invalid array size"));

		if(IsHomogenous())
			LoadIdentity();
	};


	//! explicit, avoid conversion between float to double
	template<typename T2>
	explicit TMatrix(const TMatrix<T2, rows, columns>& matrix)
	{
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] = static_cast<T>(matrix[row][col]);
			}
		}
	};

	TMatrix<T, rows, columns>& operator=(const TMatrix<T, rows, columns>& tc)
	{
		if(this != &tc)
		{
			for(size_t row=0; row < rows; ++row)
			{
				for(size_t col=0; col<columns; ++col)
				{
					m_array[row][col] = tc[row][col];
				} // for
			} // for
		} // if

		return *this;
	};

    typename cad::TVector<T, columns>& operator[](size_t row)
	{
		return m_array[row];
	};

	const typename cad::TVector<T, columns>& operator[](size_t row) const
	{
		return m_array[row];
	};

	bool operator==(const TMatrix<T, rows, columns> &tc) const
	{
		for(size_t row=0; row<rows; ++row)
		{
			for(size_t col=0; col<columns; ++col)
			{
				if(m_array[row][col] != tc[row][col])
				{
					return false;
				}
			}
		}
		return true;
	};

	bool operator!=(const TMatrix< T, rows, columns>& tc) const
	{
		return !operator==(tc);
	};

	bool IsHomogenous()
	{
		return rows == columns;
	};

	void LoadIdentity()
	{
		if(!IsHomogenous())
			throw misc::exception(U("Cannot set identity matrix"));

		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] = (row == col ? T(1) : T(0));
			}
		}
	};

	bool IsIdentity(T prec = 1e-5) const
	{
		if (!IsHomogenous())
		{
			throw misc::exception(U("Cannot test for identity matrix"));				
		}
		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				if (row==col)
				{
					if(!math::is_eq(m_array[row][col], (T)1, (T)prec))
					{
						return false;
					}
				}
				else
				{
					if(!math::is_eq(m_array[row][col], (T)0, (T)prec))
					{
						return false;
					}
				}
			}
		}
		return true;
	};

	void operator*=(const TMatrix<T, rows, columns>& other)
	{
		/*
		If A is an n�m matrix and B is an m�p matrix, the result AB 
		of their multiplication is an n�p matrix defined only if the 
		number of columns m in A is equal to the number of rows m in B.
		*/

		if (!IsHomogenous())
		{
			throw misc::exception(U("Cannot multiply the matrices"));				
		}

		TMatrix<T, rows, columns> tmp;		
		for (size_t row=0; row < rows; ++row)
		{
			for (size_t col=0; col < columns; ++col)
			{
				tmp[row][col] = m_array[row][0] * other[0][col];
				for (size_t i=1; i < columns; ++i)
				{
					tmp[row][col] += m_array[row][i] * other[i][col];
				}
			}
		}

		for (size_t row=0; row < rows; ++row)
		{
			for (size_t col=0; col < columns; ++col)
			{
				m_array[row][col] = tmp[row][col];
			}
		}
	};

	TMatrix<T, rows, columns> operator*(const TMatrix<T, rows, columns>& other) const
	{
		/*
		If A is an n�m matrix and B is an m�p matrix, the result AB 
		of their multiplication is an n�p matrix defined only if the 
		number of columns m in A is equal to the number of rows m in B.
		*/

		if (!IsHomogenous())
		{
			throw misc::exception(U("Cannot multiply the matrices"));				
		}

		TMatrix<T, rows, columns> tmp;
		
		for(size_t row=0; row < rows; ++row)
		{			
			for(size_t col=0; col < columns; ++col)
			{
				tmp[row][col] = m_array[row][0] * other[0][col];

				for(size_t i=1; i < columns; ++i)
				{
					tmp[row][col] += m_array[row][i] * other[i][col];
				}
			}
		}

		return tmp;
	};

	void operator*=(T scalar)
	{		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] *= scalar;
			}
		}
	};


	void operator/=(T scalar)
	{		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{					
				m_array[row][col] /= scalar;
			}
		}
	};


	void operator+=(const TMatrix<T, rows, columns>& other)
	{		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] += other[row][col];
			}
		}
	};


	void operator+=(T scalar)
	{		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] += scalar;
			}
		}
	};


	void operator-=(const TMatrix<T, rows, columns>& other)
	{		
		for(size_t row=0; row < rows; ++row)
		{
			for(size_t col=0; col < columns; ++col)
			{
				m_array[row][col] -= other[row][col];
			}
		}
	};


	void operator-=(T scalar)
	{
		for(size_t row=0; row < rows; ++row)
		{
			for (size_t col=0; col < columns; ++col)
			{
				m_array[row][col] -= scalar;
			}
		}
	};


	void Transpose()
	{
		if (!IsHomogenous())
		{
			throw misc::exception(U("Can do in-place transposition only for homogenous matrices"));
		}

		
		T tmpVal(0);
		for(size_t row=0; row < rows-1; ++row)
		{
			for(size_t col=row+1; col < columns; ++col)
			{
				if(row == col)	
					continue;

				tmpVal = m_array[row][col];
				m_array[row][col] = m_array[col][row];
				m_array[col][row] = tmpVal;
			}
		}
	};
	

	misc::string ToString() const
	{		
		misc::string res;
		for(size_t row=0; row < rows; ++row)
		{
			res += U("[");
			for(size_t col=0; col < columns; ++col)
			{
				res += misc::from_value(m_array[row][col], 5);
				res += U(", ");
			}
			res += U("] ");
		}
		return res;
	};

private:
	cad::TVector<T, columns>	m_array[rows];
}; // class




template<typename T, size_t rows, size_t columns > inline
const TVector<T, columns> operator*(const TMatrix<T, rows, columns>& mat, const TVector<T, columns>& vec)
{
	TVector< T, columns > tmp;	
	for(size_t row = 0; row < rows; ++row)
	{
		tmp[row] = mat[row][0] * vec[0];
		for (size_t col = 1; col < columns; ++col)
		{
			tmp[row] += mat[row][col] * vec[col];
		}
	}

	return tmp;
};


template<typename T, size_t rows, size_t columns> inline
const cad::TMatrix<T, rows, columns>
operator*( const TMatrix<T, rows, columns>& mat, const T& scalar)
{
	TMatrix< T, rows, columns > tmp;	
	for(size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] * scalar;
		}
	}
	return tmp;
};


template<typename T, size_t rows, size_t columns> inline
const cad::TMatrix< T, rows, columns>
operator/(const TMatrix<T, rows, columns>& mat, const T& scalar)
{
	TMatrix<T, rows, columns> tmp;
	for(size_t row = 0; row < rows; ++row)
	{
		for(size_t col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] / scalar;
		}
	}
	return tmp;
};


template <typename T, size_t rows, size_t columns> inline
const cad::TMatrix<T, rows, columns>
operator+(const TMatrix< T, rows, columns >& mat, const T &scalar)
{
	TMatrix<T, rows, columns> tmp;	
	for(size_t row = 0; row < rows; ++row)
	{
		for(size_t col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] + scalar;
		}
	}
	return tmp;
};


template<typename T, size_t rows, size_t columns> inline
const cad::TMatrix<T, rows, columns>
operator-(const TMatrix< T, rows, columns >& mat, const T &scalar)
{
	TMatrix<T, rows, columns> tmp;	
	for(size_t row = 0; row < rows; ++row)
	{
		for(size_t col = 0; col < columns; ++col)
		{
			tmp[row][col] = mat[row][col] - scalar;
		}
	}
	return tmp;
}


//!  operator! (...) computes matrix inverse
template<typename T, size_t rows, size_t columns> inline
const TMatrix<T, columns, rows> operator!(const TMatrix<T, rows, columns>& mat)
{
	if (!mat.IsHomogenous())
	{
		throw misc::exception(U("Can find determinant only for homogenous matrices"));			
	}

	T det = ~mat;
	if (det == 0)
	{
		throw misc::exception(U("Can compute inverse only for nonsingular matrices (det != 0)"));			
	}

	TMatrix<T, columns, rows> inverted;	
	size_t sign = 1;
	for(size_t row = 0; row < rows; ++row)
	{
		for(size_t col = 0; col < columns; ++col)
		{
			sign = (row + col) % 2 ? -1 : 1;
			inverted[row][col] = sign * ~GetMinorMatrix(mat, row, col) / det;
		}
	}

	return Transpose(inverted);
};


//! Transposition
template<typename T, size_t rows, size_t columns> inline
const TMatrix<T, columns, rows> Transpose(const TMatrix<T, rows, columns>& mat)
{
	TMatrix<T, columns, rows> transpmat;	
	for(size_t row = 0; row < rows; ++row)
	{
		for(size_t col = 0; col < columns; ++col)
		{
			transpmat[col][row] = mat[row][col];
		}
	}

	return transpmat;
};


//! operator~(...) computes matrix determinant
template<typename T, size_t rows, size_t columns> inline
T operator~(const TMatrix<T, rows, columns>& mat)
{	
	if (!mat.IsHomogenous())
	{
		throw misc::exception(U("Can find determinant only for homogenous matrices"));
	}
	
	size_t sign = 1;
	T det = 0;
	for(size_t col = 0; col < columns; ++col++)
	{
		det += sign * mat[0][col] * ~GetMinorMatrix(mat, 0, col);
		sign = -sign;
	}

	return det;
};


//! specialization for rows=1 and columns=1
template<typename T>
inline T operator~(const TMatrix<T, 1, 1>& mat)
{
	return mat[0][0];
};




template< class T, int rows, int columns > inline
const TMatrix<T, rows - 1, columns - 1> GetMinorMatrix(
	const TMatrix<T, rows, columns>& mat, int minorRow, int minorColumn)
{
	if (!mat.IsHomogenous())
	{
		throw misc::exception(U("Can get minor matrix only for homogenous matrices"));
	}

	TMatrix<T, rows - 1, columns - 1> minormat;
	size_t minorrow = 0, minorcol=0;
	for(size_t row = 0; row < rows; ++row)
	{
		minorcol = 0;
		if (row == minorRow) 
			continue;

		for(size_t col = 0; col < columns; ++col)
		{
			if (col == minorColumn)	
				continue;

			minormat[minorrow][minorcol] = mat[row][col];
			minorcol++;
		}

		minorrow++;
	}
	return minormat;
};


}; // namespace


#endif // __TMatrix_hpp__




