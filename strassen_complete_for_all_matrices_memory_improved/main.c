#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {
  //the custom matrix has size

  size_t i = 125;
  //for (size_t i = 9;i<15;i++){
  size_t k = 250;
  size_t j = 200;
  
  
  float **A = allocate_random_matrix(i, k);
  float **B = allocate_random_matrix(k, j);
  float **C0 = allocate_matrix(i, j);
  float **C1 = allocate_matrix(i, j);
  
  printf("n\t     Strassen's Alg.\tNaive Alg.   Same result  , memory usage\n");
 
  printf("%ld,%ld,%ld\t", i,k,j);
  fflush(stdout);
  
  printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, i,k,j));
  fflush(stdout);
  
  printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, i,k,j));
  fflush(stdout);
  
  printf("%d  \t    %ld bytes\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, i, j), give_memory_usage());
   
  printf("\n|%f-%f\n",C1[0][0],C0[0][0]);
  printf("\n|%f-%f\n",C1[100][100],C0[100][100]);
  printf("\n|%f-%f\n",C1[30][30],C0[30][30]);
  printf("\n|%f-%f\n",C1[67][67],C0[67][67]);
   printf("\n|%f-%f\n",C1[i-1][j-1],C0[i-1][j-1]);
  
  deallocate_matrix(A, i);
  deallocate_matrix(B, k);
  deallocate_matrix(C0, i);
  deallocate_matrix(C1, i);
  //}
  return 0;
}
