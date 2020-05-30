  size_t n2 = n/2; // This is the size of the blocks

    float ***S = (float ***)malloc(sizeof(float **) * 2);
    for (size_t i = 0; i < 2; i++) {
        S[i] = allocate_matrix(n2, n2);
    }
      float **  P = allocate_matrix(n2, n2);
    
    
    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row, B_f_col + n2,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P1 = A11 x S1
    strassen_aux(P, A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 n2);
    //C22=C22+P1
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    //C12=C12+P1
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col+n2,
                      C_f_row, C_f_col+n2,
                      0, 0,
                      n2);



    // S2 = A11 + A12
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + n2,
                      n2);


    // P2 = S2 x B22
    strassen_aux(P, (const float* const *const) S[0], B,
                 0, 0,
                 0, 0,
                 B_f_row + n2, B_f_col + n2,
                 n2);
    //C11 = C11+P2
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    //C12 = C12 + P2
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col+n2,
                      C_f_row, C_f_col+n2,
                      0, 0,
                      n2);
    // S3 = A21 + A22
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row + n2, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // P3 = S3 x B11
    strassen_aux(P, (const float* const *const) S[0], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 n2);
    //C21 = C21 +P3
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col,
                      C_f_row+n2, C_f_col,
                      0, 0,
                      n2);
    //C22 = C22 - P3         
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);    

    // S4 = B21 - B11
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row, B_f_col,
                      n2);

    // P4 = A22 x S4
    strassen_aux(P, A, (const float* const *const) S[0],
                 0, 0,
                 A_f_row + n2, A_f_col + n2,
                 0, 0,
                 n2);
    //C11 = C11+P4
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    //C21 = C21 +P4
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col,
                      C_f_row+n2, C_f_col,
                      0, 0,
                      n2);
    // S5 = A11 + A22
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S6 = B11 + B22
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P5 = S5 x S6
    strassen_aux(P, (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);
    //C11 = C11 + P5
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    //C22 = C22 +P5
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);                  
    // S7 = A12 - A22
    sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2);

    // S8 = B21 + B22
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    // P6 = S7 x S8
    strassen_aux(P, (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);
    //C11 = C11 + P6
    sub_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
    // S9 = A11 - A21
    sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2);

    // S10 = B11 + B12
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2);

    // P7 = S9 x S10
    strassen_aux(P, (const float* const *const) S[0],
                 (const float* const *const) S[1],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2);

    //C22 = C22 + P7
    sum_matrix_blocks(C, (const float* const *const) C,
                      (const float* const *const) P,
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);
    
    for (size_t i = 0; i < 2; i++) {
      deallocate_matrix(S[i], n2);
    }
    free(S);
    deallocate_matrix(P,n2);