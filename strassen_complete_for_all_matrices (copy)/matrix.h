#ifndef __MATRIX__
#include <stdlib.h>

void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t i,const size_t k,const size_t j);

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols);


size_t give_memory_usage();
void reset_memory_usage(size_t default_memory);
float **allocate_matrix(const size_t rows, const size_t cols);



void deallocate_matrix(float **A, const size_t rows);


float **allocate_random_matrix(const size_t rows, const size_t cols);
#endif //__MATRIX__
