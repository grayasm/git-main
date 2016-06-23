*
  OpenMP pragmas always start with:
    #pragma omp directive-name [clause [[,] clause ...]] new-line

  3.2 Matrix Times Vector Operation
  ---------------------------------
  matrix B is the form m x n
  vector c is of length n

    b(m,n) * c(n)= a(m)
    b(3,3) * c(3)= a(3)

    1 2 3     1     1*1 + 2*2 + 3*3   14
    4 5 6  *  2  =  4*1 + 5*2 + 6*3 = 32
    7 8 9     3     7*1 + 8*2 + 9*3   50

  i=m (rows), j=n (columns)

  Since no two dotproducts compute the same element of the result vector and
  since the order in which the values for the elements a(i) for i = 1,...,m are
  calculated does not affect correctness of the answer, these computations can
  be carried out independently. In other words, this problem can be parallelized
  over the index value i.

  #pragma omp parallel for default(none) shared(m,n,a,b,c) private(i,j)

  - default(none): if default is off must explicit set shared and private vars.
  - shared(m,n,a,b,c): each thread share the same copy of m,n,a,b,c
        * the result "a" must be shared, otherwise the end result would not be
          updated at the end of parallel section.
  - private(i,j): each thread has its own copy of i,j with different values obv.
