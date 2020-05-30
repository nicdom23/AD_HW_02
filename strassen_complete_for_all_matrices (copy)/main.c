#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {
  
printf("n\t     Strassen's Alg.\tNaive Alg.   Same result  , memory usage\n");  

for (size_t i=1,k=1,j = 1; i<300 && k<300 && j<300; i += 5,k+= 10,j+= 15)

{
  
  float **A = allocate_random_matrix(i, k);
  float **B = allocate_random_matrix(k, j);
  float **C0 = allocate_matrix(i, j);
  float **C1 = allocate_matrix(i, j);
  size_t fixed_memory_usage = give_memory_usage();
  

  
 
      printf("%ld,%ld,%ld\t", i,k,j);
      fflush(stdout);
  
      printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, i,k,j));
      fflush(stdout);
  
      printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, i,k,j));
      fflush(stdout);
  
      printf("%d  \t    %ld bytes\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1, i, j), give_memory_usage());
      
  
  deallocate_matrix(A, i);
  deallocate_matrix(B, k);
  deallocate_matrix(C0, i);
  deallocate_matrix(C1, i);
  reset_memory_usage(0);
 
}
  return 0;
}
