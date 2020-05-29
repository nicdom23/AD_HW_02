#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t i,const size_t k,const size_t j) 
{
  for (size_t y = 0; y < i; y++) {
    for (size_t x = 0; x < j; x++) {
      float value = 0.0;
      for (size_t z = 0; z < k; z++) {
        value += A[y][z]*B[z][x];
      }
      C[y][x] = value;
    }
  }
}

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (A[i][j] != B[i][j]) {
        printf("|false");
        return 0;
      }else{
          //printf("|true ");

      }
      //printf("\n");
    }
  }

  return 1;
}
static size_t memory_usage = 0;
float **allocate_matrix(const size_t rows, const size_t cols) {
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)malloc(sizeof(float) * cols);
  }
  for(size_t i = 0; i < rows; i++){
    for(size_t j = 0; j < cols; j++){
      M[i][j] = 0;
    }
   

  }
  memory_usage = memory_usage + sizeof(float*) * rows + rows*sizeof(float) * cols;
  return M;
}

size_t give_memory_usage(){

  return memory_usage;
}

void deallocate_matrix(float **A, const size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(A[i]);
  }

  free(A);
}

float **allocate_random_matrix(const size_t rows, const size_t cols) {
  
  float **A = allocate_matrix(rows, cols);
  
  srand(10);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      A[i][j] = i+j+1;//(rand() - RAND_MAX / 2) % 5;
    }
  }

  return A;
}

