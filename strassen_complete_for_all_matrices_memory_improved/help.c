#include <stdio.h>
#include <stdlib.h>
void sum( int** z,  int *const*const x, int *const*const y,size_t size){
    
    for(size_t i = 0; i<size;i++)
    for(size_t j = 0; j<size;j++)
     z[i][j] = x[i][j]+y[i][j];
}

int main(){
    int** a = (int**)malloc(sizeof(int*)*5);
    
    for (size_t i = 0;i<5;i++){
        a[i] = (int*)malloc(sizeof(int)*5);
        for (size_t j = 0;j<5;j++)
            a[i][j] = 250;  
}  
    int** b = (int**)malloc(sizeof(int*)*5);
    
    for (size_t i = 0;i<5;i++){
        b[i] = (int*)malloc(sizeof(int)*5);
        for (size_t j = 0;j<5;j++)
            b[i][j] = 15;  
}  
    int** c = (int**)malloc(sizeof(int*)*5);
    
    for (size_t i = 0;i<5;i++){
        c[i] = (int*)malloc(sizeof(int)*5);
        for (size_t j = 0;j<5;j++)
            c[i][j] = 10;  
}  
    sum(c,(int*const*const)c,(int*const*const)b,5);
    
    
    for (size_t i = 0;i<5;i++)
    for (size_t j= 0; j<5;j++)
    printf("\n%d + %d  = %d\n",a[i][j],b[i][j],c[i][j]);
    
    sum(c,(int*const*const)c,(int*const*const)b,5);
    
    
    for (size_t i = 0;i<5;i++)
    for (size_t j= 0; j<5;j++)
    printf("\n%d + %d  = %d\n",a[i][j],b[i][j],c[i][j]);
}