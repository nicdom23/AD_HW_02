#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "print_matrix.c"
#include "strassen.h"

int main(int argc, char *argv[]) {
  size_t n = (1 << 8);

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);


  printf("n\t  Strassen's Alg.\t  Naive Alg.\tSame result\n");
  for (size_t i = 1,k=1,j=1; i<=j&&k<= n&&j <= n ; i +=5,k +=10,j += 8) { //I changed the code here to still perform with non powers of 2
    i = 256;
    k = 256;
    j = 256;
    printf("%3.ld,%3.ld,%3.ld\t", i,k,j);
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, i,k,j));
    fflush(stdout);
    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, i,k,j));
    fflush(stdout);
   
    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, i, j));
 
    printf("\nresults [0][0] : %f %f\n",C0[0][0],C1[0][0]);
    printf("\nresults [end,end][end,end]: %f %f\n",C0[i-1][j-1],C1[i-1][j-1]);
    printf("MATRIX C");
    print_matrix(C0,0,0,i,j);
  }
  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);

  return 0;
}
