#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {
  size_t n = (1 << 8);

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);


  printf("n\tStrassen's Alg.\tNaive Alg.\tSame result\n");
  for (size_t i = 1,k=1,j=1; i<=j&&k<= n&&j <= n ; i +=5,k +=10,j += 10) { //I changed the code here to still perform with non powers of 2

    printf("%ld,%ld,%ld\t", i,k,j);
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, i,k,j));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, i,k,j));
    fflush(stdout);
  
    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, i, j));
  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);

  return 0;
}
