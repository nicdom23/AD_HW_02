#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "print_matrix.c"
#include "strassen.h"

int main(int argc, char *argv[]) {
  size_t n = 256;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  printf("MATRIX A");
  print_matrix(A,0,0,n,n);
  printf("MATRIX B");
  print_matrix(B,0,0,n,n);

  printf("n\t  Naive Alg.\t \n");
  
    size_t i = n;
    size_t k = n;
    size_t j = n;
    printf("%3.ld,%3.ld,%3.ld\t", i,k,j);
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, i,k,j));
    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, i,k,j));
    fflush(stdout);
    printf("\nresults [0][0] : %f %f\n",C0[0][0],C1[0][0]);
    printf("\nresults [end,end][end,end]: %f  %f\n",C0[i-1][j-1],C1[i-1][j-1]);
    printf("MATRIX C");
    //print_matrix(C0,0,0,i,j);
  
  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);

  return 0;
}
