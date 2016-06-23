*
  OpenMP pragmas always start with:
    #pragma omp directive-name [clause [clause ...]] new-line

  3.2 Matrix Times Vector Operation
  ---------------------------------
  matrix B is the form m x n
  vector c is of length n

  1 2 3   1   1*1 + 2*2 + 3*3   14
  4 5 6 * 2 = 4*1 + 5*2 + 6*3 = 32
  7 8 9   3   7*1 + 8*2 + 9*3   50
