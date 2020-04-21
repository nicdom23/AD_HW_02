# DSSC - Algorithmic Design - Strassen's Algorithm
This repository contains some code to simplify the implementation and the testing of the Strassen's algorithm for matrix multiplication.

In order to test the differences in term of execution-time between the naive algorithm and the Strassen's algorithm, you need to implement both the algorithms. The former must be implementated by the function `naive_matrix_multiplication` in the file [matrix.c](matrix.c) and the latter by the function `strassen_matrix_multiplication` in the file [strassen.c](strassen.c).

A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:
```bash
./strassen_test 
n Naive Alg.  Strassen's Alg. Same result
1	0.000000	0.000000	1
2	0.000000	0.000000	1
4	0.000000	0.000000	1
8	0.000000	0.000000	1
16	0.000000	0.000000	1
32	0.000000	0.000000	1
64	0.000000	0.000000	1
128	0.000000	0.000000	1
256	0.000000	0.000000	1
512	0.000000	0.000000	1
1024	0.000000	0.000000	1
2048	0.000000	0.000000	1
4096	0.000000	0.000000	1
```

The first column in the output report the number of the rows and columns in the tested matrixes. 

The second and third columns in the output reports the execution-time in seconds of the implementations of the naive algorithm and of the Strassen's algorithm, respectively. Since the two algorithms are not implemented in the repository, `strassen_test` initially reports 0 seconds for both of them. 

Finally, the last column, which is excusively meant to validate the implementations, contains the value 1 if and only if the result of the naive algorithm and that of the Strassen's algorithm are the same.

## Notes By Student : Nicola Domenis  13/04/2020

At first I tried to run the code for square matrices that have not a dimension equal to a power of two. The recursion and the base case set to n=32 still made some multiplications to go to the correct solution. If we still want to perform the divide-et-impera paradigm we must know that by dividing in four a suqare matrix whose dimension is not divisible by two we get two square matrices and two non-square matrices. So the case of the general square matrices ends up into being a problem of non-square matrices recursion. This is the problem
we have then addressed.

15/04/2020
I manged to implement a naive method to perform the method on non-power-of-2 square matrices. I create three bigger square matrices that have a size that is a power of 2, the smallest size that can contain the original matrix. We then copy the original matrices into these new, bigger matrices, and then we use them as parameters for the Strassen implementation that we made during the lectures. The other modifications that I made are:
-   In `main.c` I rewrote the for-cycle that iterates among the different matrices in order to test even non-power of 2 matrices;
-  Now the `allocate_matrix` function initializes the matrices to be zero matrices;

Now we have that the non-power-of-2 square matrices of size n become matrices of size 

$ 2 ^ \ceil{\log_2(n)} $

$2^n$

