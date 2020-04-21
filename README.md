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

Now we have that the non-power-of-2 square matrices of size n become matrices of size $ l = 2 ^ {\lceil\log_2(n)\rceil} $.

It can be easily proven that $ 2 ^ {\lceil\log_2(n)\rceil} \leq 2n$
- $2 ^ {\lceil\log_2(n)\rceil} \leq 2^{\log_2(n)+1} = 2n$

So the asymptotic complexity of this method is :
- $\Theta(l^{\log_2 7}) = \Theta((2n)^{\log_2 7})=\Theta(n^{\log_2 7})$
So it remains unchanged.

21/04/2020

Now I am trying to change the code in order to multiply non-square matrices.
I am using the advice of the Q&A session of yesteday.
- I changed the main.c, test.c files and their headers in order to accustom a triplet on sizes of the matrices: i = rows of A = rows of C, k= columns of A= rows of B, j=columns of B=columns 0f C

-Now strassen's algorithm applies the non-power-of-2 square matrix multiplication to square submatrices of A and B of the same size i.

What are the matrices to multiply and then sum in order to obtain C?

The general rule states that, if A is divided into n square matrices along its rows :$C_{ij} = (A_{i1}B_{1j})+(A_{i2}B_{2j})+(A_{i3}B_{3j})+\cdots +(A_{in}B_{nj})$ 

In our case we have that $n = \lceil \frac{k}{i}\rceil$ and $m =\lceil \frac{j}{i}\rceil $: 



A=
\begin{matrix}
A_{11}&A_{12}&A_{13}&\cdots&A_{1n}
\end{matrix}

B=
\begin{matrix}
B_{11}&B_{12}&\cdots&B_{1m}\\
B_{21}&B_{22}&\cdots&B_{2m}\\
\cdots\\
B_{n1}&B_{n2}&\cdots&B_{nm}
\end{matrix}

C=
\begin{matrix}
C_{11}&C_{12}&\cdots&C_{1m}\\
\end{matrix}


So our case reduces to :
$C_{1j} = (A_{11}B_{1j})+(A_{12}B_{2j})+(A_{13}B_{3j})+\cdots +(A_{1n}B_{nj})$
for m matrices $C_{1j}$ 

This is the sum we need to implement in our code.
