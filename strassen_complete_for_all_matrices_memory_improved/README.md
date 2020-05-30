# DSSC - Algorithmic Design - Strassen's Algorithm implementation Homework-02

## Notes By Student : Nicola Domenis  

27/05/2020

Here I will collect all the process for improving the code from the memory point of view, then I will report the comparison with the unmodified code. I will improve the final version of the Strassen method, the one who multiplites all types of matrices. I will try to correct here the naivity of my implementation and maybe I will learn new solutions to memory problems. I admit that at first I did not have much clues on how to improve the code, but now I will try to see how.

-------------------------------------------------


So to test our memory usage improvement I will choose an arbitrary triplet of matrix sizes to perform the multiplication.

- $A_{i,k}xB_{k,j} = C_{i,j}$ where $i = 125$, $k= 250$ and $j = 200$

We will modify 'main.c' to perform on only this matrix and to show the memory usage during the multiplication.

- We choose to use a custom static variable to store the memory usage

Valgrind still memorizes other heap usages like the buffer for the 'printf' function and other constant memory allocations. It is still useful but we want to focus only on the memory usage of the matrices, which can still be improved.

The test result is:

            nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test
            n            Strassen's Alg.    Naive Alg.   Same result   memory usage
            125,250,200     0.020915        0.015301        1           7251300 bytes

The memory usage is around 7 MB. We implemented a lot of matrices during every step of the matrix multiplication, so there is room for improvement. The goal is now to reduce this number.

---------------------------------

The matrices are allocated at three points:

- To embed A and B into matrices made of blocks of dimension ixi
- To embed the blocks of dimension ixi of the previous point into blocks whose dimensions are powers of two
- To memorize the S and P matrices to compute Strassen's method

We will assume that the input matrices are given: an even better approach would be possible if the creation of the matrices A and B was made by receiving their dimension as an input at the execution. We could directly create A and B to be already viable for the original Strassen method. But this is unrealistic so we will assume that the matrices A and B are already present in memory and of course C will be created of the dimensions that are defined by the product and must be present in memory at the end of the matrix multiplication.

- So it is unavoidable to allocate A, B and C

Since the Strassen algorithm works on matrices, then matrices must be its input, and as we saw on Exercise 1. they must be square and have dimension equal to a power of 2.

- We need at least to allocate two other matrices to embed A and B in order to operate the Strassen algorithm

We could combine the first and second point above to create three matrices that embed A, B and C that are directly made of blocks that are square blocks and have dimension that is a power of 2.

--------------------------------------------------------------
29/05/2020 
I have made the correction explained in the previous README.
The code has been tested, I made a correction for when k and j are multiples of n_row_A.
Now to see how much memory we have saved.
The result is:

        nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test
        n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
        125,250,200     0.016631        0.009019        1           4345424 bytes

30/05/2020
A little modification saved more space:

        nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test
        n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
        123,250,200      0.018793        0.012832        1           4213328 bytes
