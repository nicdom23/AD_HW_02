# DSSC - Algorithmic Design - Strassen's Algorithm implementation Homework-02

## Notes By Student : Nicola Domenis  

27/05/2020

Here I will collect all the process for improving the code from the memory point of view, then I will report the comparison with the unmodified code. I will improve the final version of the Strassen method, the one who multiplites all types of matrices. I will try to correct here the naivity of my implementation and maybe I will learn new solutions to memory problems. I admit that at first I did not have much clues on how to improve the code, but now I will try to see how.


So to test our memory usage improvement I will choose an arbitrary triplet of matrix sizes to perform the multiplication.

- $A_{i,k}xB_{k,j} = C_{i,j}$ where $i = 125$, $k= 250$ and $j = 200$

We will modify 'main.c' to perform on only this matrix and to show the memory usage during the multiplication.