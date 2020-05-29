#include "matrix.h"
#include <stdio.h>
/*
 * this function performs the element-wise
 * subtraction of B from A and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sub_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++) {
      for (size_t x = 0; x < n; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function performs the element-wise
 * sum of A and B and put the resulting
 * sub-matrix in C. The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++) {
      for (size_t x = 0; x < n; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
      }
    }
}

/*
 * this function implements the naive algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void naive_aux(float **C, float const *const *const A,
               float const *const * const B,
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < n; x++) {
      float value = 0.0;
      for (size_t z = 0; z < n; z++) {
        value += A[y + A_f_row][z + A_f_col]*B[z + B_f_row][x + B_f_col];
      }
      C[y + C_f_row][x + C_f_col] = value;
    }
  }
}

/*
 * This function implements the Strassen's algorithm
 * for matrix multiplication between sub-matrixes.
 * The result is placed in the sub-matrix C.
 * The parameters *_f_row and *_f_col
 * represents the first row and the first column,
 * respectively, of the sub-matrix we want to deal with.
 */
void strassen_aux(float **C, float const *const *const A,
                  float const *const * const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t n)
{
    if (n <= (1<<5)) {//(1<<5)
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  n);

        return;
    }

    size_t n2 = n/2; // This is the size of the blocks

    float ***S = (float ***)malloc(sizeof(float **) * 10);
    for (size_t i = 0; i < 10; i++) {
        S[i] = allocate_matrix(n2, n2);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(n2, n2);
    }

    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row, B_f_col + n2,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P1 = A11 x S1
    strassen_aux(P[0], A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 n2);

    // S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + n2,
                      n2);


    // P2 = S2 x B22
    strassen_aux(P[1], (const float* const *const) S[1], B,
                 0, 0,
                 0, 0,
                 B_f_row + n2, B_f_col + n2,
                 n2);

    // S3 = A21 + A22
    sum_matrix_blocks(S[2], A, A,
                      0, 0,
                      A_f_row + n2, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // P3 = S3 x B11
    strassen_aux(P[2], (const float* const *const) S[2], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 n2);

    // S4 = B21 - B11
    sub_matrix_blocks(S[3], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row, B_f_col,
                      n2);

    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float* const *const) S[3],
                 0, 0,
                 A_f_row + n2, A_f_col + n2,
                 0, 0,
                 n2);

    // S5 = A11 + A22
    sum_matrix_blocks(S[4], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[5], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P5 = S5 x S6
    strassen_aux(P[4], (const float* const *const) S[4],
                 (const float* const *const) S[5],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // S7 = A12 - A22
    sub_matrix_blocks(S[6], A, A,
                      0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[7], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P6 = S7 x S8
    strassen_aux(P[5], (const float* const *const) S[6],
                 (const float* const *const) S[7],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // S9 = A11 - A21
    sub_matrix_blocks(S[8], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[9], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2);

    // P7 = S9 x S10
    strassen_aux(P[6], (const float* const *const) S[8],
                 (const float* const *const) S[9],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);

    // C12 = P1 + P2
    sum_matrix_blocks(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);

    // C21 = P3 + P4
    sum_matrix_blocks(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+n2, C_f_col,
                      0, 0,
                      0, 0,
                      n2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    
    for (size_t i = 0; i < 10; i++) {
      deallocate_matrix(S[i], n2);
    }
    free(S);
    
    for (size_t i = 0; i < 7; i++) {
      deallocate_matrix(P[i], n2);
    }
    free(P);   
}


/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t i,size_t k, size_t j)
 {
  
  
  //printf("i : %ld, k = %ld, j = %ld\n",i,k,j);
  size_t n_row_A = 1;
  while(n_row_A<i) n_row_A = n_row_A*2;
  size_t n_col_A = (k/n_row_A+1)*n_row_A;
  if (k == n_row_A*(k/n_row_A)){
      n_col_A = n_row_A*(k/n_row_A);
  }
    printf("result: %ld %ld\n",(k/n_row_A+1),(k/n_row_A+1)*n_row_A);
    printf("rows = %ld, columns = %ld \n",n_row_A,n_col_A);
    size_t n_row_B = n_col_A;
    size_t n_col_B = (j/n_row_A+1)*n_row_A;
    if (j == n_row_A*(j/n_row_A))
      n_col_B = n_row_A*(j/n_row_A);
    
    printf("result: %ld %ld\n",j/n_row_A,(j/n_row_A)*n_row_A);
    printf("rows = %ld, columns = %ld \n",n_row_B,n_col_B);

  size_t n_row_C = n_row_A;
  size_t n_col_C = n_col_B;

  //create new matrices
  
  float ** new_C = allocate_matrix(n_row_A, n_row_A);
  float ** new_C_2 = allocate_matrix(n_row_C, n_col_C);
  
  float ** new_A = allocate_matrix(n_row_A, n_col_A);
  float ** new_B =  allocate_matrix(n_row_B, n_col_B);

 //embed A and B into bigger matrices
  
    //printf("g = %ld",g);
    for(size_t l =0;l <i;l++){
        for(size_t f = 0; f <k; f++){ 
            new_A[l][f] = A[l][f];
        }
    }
  /*
  //embed A and B into bigger matrices
  for(size_t g = 0;g<(k/i+1);g++){
    //printf("g = %ld",g);
    for(size_t l =0;l <i;l++){
      if(i<k)
        for(size_t f = 0; f <i; f++){ 
            if(f+g*i<k)
            new_A[l][g*n_row_A+f] = A[l][f+g*i];
        }
      else
        for(size_t f = 0; f <k; f++){
            if(f+g*i<k) 
            new_A[l][g*n_row_A+f] = A[l][f+g*i];
        }
     
    }
  }
  */
 /*
     printf("\n MATRIX A \n");
    for(size_t l =0;l <n_row_A;l++){
      printf(">");
      for(size_t f = 0; f <n_col_A; f++){ 
          printf("|%f",new_A[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    */
  /*
  for(size_t h = 0;h<(j/i+1);h++){
    //printf("\n h = %ld,..,%ld\n",h,j/i+1);
    for(size_t g = 0;g<(k/i+1);g++){
          //printf("\n g = %ld,...,%ld\n",g,(k/i+1));
          if (i<=k && i<=j){
            printf("\nCASE 1\n");
            for(size_t l =0;l <i;l++){
              for(size_t f = 0; f <i; f++){
                if(l+g*i<k && f+h*i<j)
                  new_B[l+g*n_row_A][f+h*n_row_A] = B[l+g*i][f+h*i];
                }
              }
          }else if(k<=i && j<=i){
            printf("\nCASE 2\n");
              for(size_t l =0;l <k;l++){
                  for(size_t f = 0; f <j; f++){
                    if(l+g*i<k && f+h*i<j)
                      new_B[l+g*n_row_A][f+h*n_row_A]= B[l+g*i][f+h*i];
                  }
                }

          }else if(i<=k && j<=i){
            printf("\nCASE 3\n");
            for(size_t l =0;l <i;l++){
                  for(size_t f = 0; f <j; f++){
                    if(l+g*i<k && f+h*i<j)
                      new_B[l+g*n_row_A][f+h*n_row_A]= B[l+g*i][f+h*i];
                  }
                }

          }else if(k<=i && i<=j){
            printf("\nCASE 4\n");
            for(size_t l =0;l <k;l++){
                  for(size_t f = 0; f <i; f++){
                    if(l+g*i<k && f+h*i<j)
                      new_B[l+g*n_row_A][f+h*n_row_A]= B[l+g*i][f+h*i];
                  }
                }

          }else{printf("NO CODE");}
          
    }
  }
   */
  /*
    for(size_t l =0;l <k;l++){
        for(size_t f = 0; f <j; f++){ 
            new_B[l][f] = B[l][f];
        }
    }
  


     printf("\n MATRIX B \n");
    for(size_t l =0;l <n_row_B;l++){
      printf(">");
      for(size_t f = 0; f <n_col_B; f++){ 
          printf("|%f",new_B[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    


  
  

 //Perform the matrix multiplications between square matrices                              
  for (size_t f = 0 ;f<(j/n_row_A+1); f++){
    for (size_t l = 0;l<(k/n_row_A+1); l++){
      printf ("iteration: %ld  %ld",f,l);
      strassen_aux(new_C,(float const *const *const)  new_A,(float const *const *const)  new_B,
               0, 0,
               0, l*n_row_A,
               l*n_row_A, f*n_row_A,
               n_row_A);
*/
      /*
      for(size_t g =0 ;g<i;g++){
       for(size_t h = 0; h <i; h++){
          if(f*n_row_A+h<j){
           //float v =  new_C[g][h];
           float v = 1;}
             //C[g][f*n_row_A+h] = C[g][f*i + h] + new_C[g][f];//we perform there the summation to obtain the complete C, so we can perform more operations on the same matrix C_{1j}
            
      }
    
      }
      */
     /*
    for(size_t g =0 ;g<i;g++){
       for(size_t h = 0; h <j; h++){
          if(f*i + h < j)
           C[g][f*i + h] = C[g][f*i + h] + new_C[g][h];//we perform there the summation to obtain the complete C, so we can perform more operations on the same matrix C_{1j}
      }
    
      }*/
      /*
      for(size_t g =0 ;g<n_row_C;g++){
       for(size_t h = 0; h <n_row_C; h++){
      
           new_C_2[g][f*n_row_A + h] = new_C_2[g][f*n_row_A + h] + new_C[g][h];//we perform there the summation to obtain the complete C, so we can perform more operations on the same matrix C_{1j}
      }
    
      }
    }
  } 
    */ 
  //retrieve C 
    
    /*          
  for(size_t l =0 ;l<i;l++){
    for(size_t f = 0; f <j; f++){
      C[l][f] = new_C[l][f]; 
    }
  }
   */
  /*
  printf("MATRIX C");
    for(size_t l =0;l <n_row_C;l++){
      printf(">");
      for(size_t f = 0; f <n_col_C; f++){ 
          printf("|%f",new_C_2[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    //extract C
    for(size_t g = 0; g<i;g++){
      for (size_t h = 0; h<j;h++){
          C[g][h] = new_C_2[g][h];

      }

    }*/
  /*
  printf("MATRIX C");
    for(size_t l =0;l <i;l++){
      printf(">");
      for(size_t f = 0; f <j; f++){ 
          printf("|%f",C[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    */
   /*
   for(size_t l =0;l <i;l++){
      printf(">");
      for(size_t f = 0; f <k; f++){ 
          printf("|%f",A[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    
   for(size_t l =0;l <k;l++){
      printf(">");
      for(size_t f = 0; f <j; f++){ 
          printf("|%f",B[l][f]);
       }
       printf("\n");
    }
    printf("\n");*/
    //printf("\n i = %ld , C(1,1) = %f \n",i,C[0][0]);
    /*
    for(size_t l =0;l <n_row_C;l++){
      printf(">");
      for(size_t f = 0; f <n_col_C; f++){ 
          printf("|%f",new_C_2[l][f]);
       }
       printf("\n");
    }
    printf("\n");
    */
  //free the memory
  deallocate_matrix(new_A, n_row_A);
  deallocate_matrix(new_B, n_row_B);
  deallocate_matrix(new_C, n_row_A);
  deallocate_matrix(new_C_2, n_row_C);
 
 }                                   
                                    
                                    
                                    
