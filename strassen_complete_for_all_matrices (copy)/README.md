# DSSC - Algorithmic Design - Strassen's Algorithm implementation Homework-02

27/05/2020
I started these notes before this date and they include the diary for the partial implementation of the Strassen method for all square matrices. I have choosen not to include the code for the regular Strassen algorithm and for the expanded version for all the square matrices because:

- The first code has been done in class, so no redundancy;

- The second code's improvements have been discussed in class and I have included them in the Strassen version for all matrices anyway, so it would not have  given too much more information

## Notes By Student : Nicola Domenis  

13/04/2020

At first I tried to run the code for square matrices that do not have a dimension equal to a power of two. The recursion and the base case set to $n = 32$ still made some multiplications reach the correct solution. If we want to perform the divide-et-impera paradigm we must know that by dividing in four a square matrix whose dimension is not divisible by two we get two square matrices and two non-square matrices. So the case of the general square matrices ends up into being a problem of non-square matrices recursion. This is the problem
we have then addressed.

15/04/2020

I manged to implement a naive method that can perform on non-power-of-2 square matrices. I create three bigger square matrices that have a size that is a power of 2, the smallest size that can contain the original matrix. We then copy the original matrices into these new, bigger matrices, and then we use them as parameters for the Strassen implementation that we made during the lectures. The other modifications that I made are:
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

In our case we have that $n = \lceil \frac{k}{i}\rceil$ and $m =\lceil \frac{j}{i}\rceil $ so we have the following matrices: 


$$
A=
\begin{matrix}
A_{11}&A_{12}&A_{13}&\cdots&A_{1n}
\end{matrix}
$$
$$
B=
\begin{matrix}
B_{11}&B_{12}&\cdots&B_{1m}\\
B_{21}&B_{22}&\cdots&B_{2m}\\
\cdots\\
B_{n1}&B_{n2}&\cdots&B_{nm}
\end{matrix}
$$

$$
C=
\begin{matrix}
C_{11}&C_{12}&\cdots&C_{1m}\\
\end{matrix}
$$

So our case reduces to :
$C_{1j} = (A_{11}B_{1j})+(A_{12}B_{2j})+(A_{13}B_{3j})+\cdots +(A_{1n}B_{nj})$
for m matrices $C_{1j}$ 

This is the sum I need to implement in our code.


22/04/2020

I managed to implement the sum in the code.
Now the naive implementation and the strassen implementation produce the same matrices.

We embedded the matrices A,B,C (that have dimensions $i\text{x}k$,$k\text{x}j$,$i\text{x}j$ respectively)in matrices new_A,new_B,new_C of sizes $i\text{x}\lceil\frac{k}{i}\rceil i$,$\lceil\frac{k}{i}\rceil i\text{x}\lceil\frac{j}{i}\rceil i$ and $i\text{x}\lceil\frac{j}{i}\rceil i$ respectively. Then we divided them in blocks of size $i\text{x}i$, and used the square matrices Strassen multiplication algorithm. Then we applied the above summation to calculate the wanted products and reconstruct the matrix C.

- What is the complexity now?


Then we can prove that $\lceil\frac{j}{i}\rceil i\leq j+i$

-  $\lceil\frac{j}{i}\rceil i \leq (\frac{j}{i}+1)i = j+i$

The same is for $\lceil\frac{k}{i}\rceil i\leq k+i$

The naive algorithm on the non-square matrices has a complexity $\Theta(ikj)$.
The first embedding creates matrices whose naive algorithm complexity would be $\Theta(i\lceil\frac{k}{i}\rceil i \lceil\frac{j}{i}\rceil i)  \leq \theta(i(k+i)(j+i))=\Theta(i^3)$ if k and j are fixed.

Then we focus on the improved Strassen algorithm.
The complexity for a single block would be $\Theta(i^{log_7 2})$

Then the complexity for the whole operation would be $\Theta(i^{log_7 2})\lceil\frac{k}{i}\rceil  \lceil\frac{j}{i}\rceil$(for the various sub multiplications)$+\Theta(i^2)\lfloor\frac{k}{i}\rfloor\lceil\frac{j}{i}\rceil$(for summing the various sub-matrices to reconstruct C). Note that this case counts all possible sizes i,k,j.

- $\Theta(i^{log_7 2})\lceil\frac{k}{i}\rceil  \lceil\frac{j}{i}\rceil+\Theta(i^2)\lfloor\frac{k}{i}\rfloor\lceil\frac{j}{i}\rceil \leq 
\Theta(i^{log_7 2})(\frac{k}{i}+1)  (\frac{j}{i})+\Theta(i^2)(\frac{k}{i})(\frac{j}{i}+1) = \Theta(i^{log_7 2})$ if k and j are fixed.

So the result is still better than the naive one.

27/05/2020

I proofread this text, I have tested the code, there are no memory leaks.
The results are



            $ ./strassen_test 
            n	     Strassen's Alg.	  Naive Alg.	Same result
        1,  1,  1 	    0.000003	      0.000000	       1
        6, 11,  9 	    0.000011	      0.000001	       1
        11, 21, 17 	    0.000032	      0.000003	       1
        16, 31, 25 	    0.000034	      0.000010	       1
        21, 41, 33 	    0.000149	      0.000023	       1
        26, 51, 41 	    0.000142	      0.000043	       1
        31, 61, 49 	    0.000148	      0.000079	       1
        36, 71, 57 	    0.001035          0.000130	       1
        41, 81, 65 	    0.001020	      0.000221	       1
        46, 91, 73 	    0.000996	      0.000306	       1
        51,101, 81 	    0.001008	      0.000433	       1
        56,111, 89      0.001013	      0.000701	       1
        61,121, 97 	    0.007952	      0.000794	       1
        66,131,105 	    0.015965	      0.000985	       1
        71,141,113 	    0.016809	      0.001222	       1
        76,151,121 	    0.014980	      0.004602	       1
        81,161,129 	    0.019365	      0.001821	       1
        86,171,137 	    0.016117	      0.002323	       1
        91,181,145 	    0.013396	      0.002655	       1
        96,191,153 	    0.016441	      0.003179	       1
        101,201,161   	0.013946       	  0.003652	       1
        106,211,169 	0.014052   	      0.007328	       1
        111,221,177 	0.011934	      0.008956	       1
        116,231,185 	0.018902	      0.005551	       1
        121,241,193 	0.013174       	  0.019338	       1
        126,251,201 	0.012777       	  0.013913	       1
              
. 
- Strassen's algorithm is slower than the naive one, I assume it's because of memory allocation times;

- The matrix multiplication gives however the same result in both cases, so the code makes a correct multiplication;

Having said that I conclude the exercise 1. and I will pass to the next one, where I will discuss the memory issues.
---------------------------------------------------------
29/05/2020

By studying the next exercise I found out that the output is not correct when $i = k= j = 256$. I will try now to solve this problem, since it seems to have affected the second exercise as well.

-  the output is correct when $i = k = j =128$
-  the only error is the element $c_{i,j} $ that should be 39048576 but instead is 39048524. NOTE: the implemented Strassen algorithm gives instead the correct answer. So the issue is of the naive implementation.
- There is in fact a logical error in the function ''naive_matrix_multiplication''

####The error has been found

In order to study the actual output matrix of the multiplication I modified the code to create a deterministic matrix in lieu of a random matrix.
I modified the function 'allocate_random_matrix' in the file 'matrix.c' as follows:

        float **allocate_random_matrix(const size_t rows, const size_t cols) {
  
        float **A = allocate_matrix(rows, cols);
  
        srand(10);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
              A[i][j] = i+j+1;//<---
            }
        }

            return A;
        }

At first it was very helpful but then the output matrices were different. I also used MATLAB to verify. After a few discarded hypotheses I came up to what was the real problem. 

My idea is that the floating point arithmetics scrambles the calculations of the naive matrix multiplication. I tried to substitute every 'float' with 'size_t' but to no benefit.
So then the solution must be that the calculations of the naive method are not correct for large cell elements. The Strassen method is however still correct.


Correcting this makes the code work. Now I will correct the formatting and remove the debug addenda.

-------------------------------------------------------------------
