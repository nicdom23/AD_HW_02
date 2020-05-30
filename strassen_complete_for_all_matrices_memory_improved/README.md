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

--------------------------------------------------------
I finally completed the code, the resulted saved space is:

            nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test
            n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
            125,250,200     0.010184        0.008817        1           1561168 bytes

From 7 MB we went to 1,5 MB.

- What about the execution time? 

We try a few runs:

        nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test
        n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
        125,250,200     0.008872        0.011119        1           1561168 bytes
        125,250,200     0.009726        0.011242        1           1561168 bytes
        125,250,200     0.009225        0.018300        1           1561168 bytes
        125,250,200     0.007152        0.010678        1           1561168 bytes
        125,250,200     0.007929        0.015261        1           1561168 bytes
        125,250,200     0.010107        0.015910        1           1561168 bytes
        125,250,200     0.010544        0.013570        1           1561168 bytes
        125,250,200     0.011518        0.008482        1           1561168 bytes
        125,250,200     0.009692        0.011755        1           1561168 bytes
        125,250,200     0.013536        0.010636        1           1561168 bytes

And then we try runs with different dimensions:

        nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices_memory_improved$ ./strassen_test 
        n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
        1,1,1   0.000001        0.000000        1           84 bytes
        6,11,16 0.000006        0.000001        1           4016 bytes
        11,21,31        0.000027        0.000007        1           14368 bytes
        16,31,46        0.000035        0.000023        1           23936 bytes
        21,41,61        0.000166        0.000054        1           54224 bytes
        26,51,76        0.000233        0.000103        1           75536 bytes
        31,61,91        0.000233        0.000188        1           91456 bytes
        36,71,106       0.002397        0.000343        1           241248 bytes
        41,81,121       0.005159        0.000526        1           262768 bytes
        46,91,136       0.001717        0.000649        1           345968 bytes
        51,101,151      0.001372        0.000802        1           373088 bytes
        56,111,166      0.001367        0.001105        1           403008 bytes
        61,121,181      0.002147        0.001721        1           435728 bytes
        66,131,196      0.015185        0.004627        1           1274576 bytes
        71,141,211      0.012657        0.002304        1           1312896 bytes
        76,151,226      0.006466        0.002910        1           1354016 bytes
        81,161,241      0.013830        0.006018        1           1397936 bytes
        86,171,256      0.013232        0.004242        1           1444656 bytes
        91,181,271      0.019481        0.008142        1           1909408 bytes
        96,191,286      0.017877        0.009976        1           1961728 bytes
        
So on the long run the Strassen Algorithm that we modified is not better than the Naive one.
The original Strassen algorithm, the one of the previous exercise,can be modified to give as the output the memory as:

        nd23@nd23-VirtualBox:~/Adv_algorithms/AD_HW_02/strassen_complete_for_all_matrices (copy)$ ./strassen_test 
        n            Strassen's Alg.    Naive Alg.   Same result  , memory usage
        1,1,1   0.000003        0.000000        1           256 bytes
        6,11,16 0.000018        0.000001        1           9504 bytes
        11,21,31        0.000049        0.000007        1           33100 bytes
        16,31,46        0.000053        0.000023        1           46720 bytes
        21,41,61        0.000273        0.000053        1           122940 bytes
        26,51,76        0.000277        0.000103        1           146560 bytes
        31,61,91        0.000315        0.000189        1           175180 bytes
        36,71,106       0.004443        0.000334        1           878496 bytes
        41,81,121       0.001669        0.000480        1           917116 bytes
        46,91,136       0.001567        0.000578        1           960736 bytes
        51,101,151      0.001495        0.000807        1           1009356 bytes
        56,111,166      0.001621        0.001072        1           1062976 bytes
        61,121,181      0.001508        0.001418        1           1121596 bytes
        66,131,196      0.025343        0.002897        1           6465984 bytes
        71,141,211      0.025342        0.002830        1           6534604 bytes
        76,151,226      0.018431        0.005601        1           6608224 bytes
        81,161,241      0.022708        0.003726        1           6686844 bytes
        86,171,256      0.014903        0.010440        1           6770464 bytes
        91,181,271      0.024156        0.009439        1           6859084 bytes
        96,191,286      0.023043        0.011917        1           6952704 bytes

By comparison the execution times have improved a little, memory improvement leads to a faster code. Strassen for non-square matrices is slower than the naive algorithm, both the original and the memory improved. This could be because of the additional operations required to handle the more matrices we have to create. However we see that there is a big improvement in the memory usage after the improvement.
-----------------------------------------------------------------------------
-----------------------------------------------------------------