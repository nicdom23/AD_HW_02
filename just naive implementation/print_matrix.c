#include <stdio.h>
const void print_matrix(float ** A, const size_t first_row,const size_t first_col,const size_t rows,const size_t cols){
    printf("\nfirst elem  %f\n",A[first_row][first_col]);
    /*
    for(size_t l =0;l <rows;l++){
        printf(">");
        for(size_t f = 0; f <cols; f++){ 
              printf("|%f",A[first_row+l][first_col+f]);
        }
        printf("\n");
        }
        printf("\n");*/
    }
