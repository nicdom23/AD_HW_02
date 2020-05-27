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


