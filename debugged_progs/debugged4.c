/******************************************************************************
* ЗАДАНИЕ: bugged4.c
* ОПИСАНИЕ:
*   Очень простая программа с segmentation fault.
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define N 500
//при параметре 100 выделяет довольно много памяти mmap2(NULL, 8392704, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0xb7520000
//очевидно при 1048 этот mmap вызовет SIGSEGV (на 32-битной машине) 

int main (int argc, char *argv[]) 
{
    int nthreads, tid, i, j;
    
    #pragma omp parallel shared(nthreads) private(i, j, tid)
    {
		double a[N][N];
       tid = omp_get_thread_num();
       if (tid == 0) 
       {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
       }
       printf("Thread %d starting...\n", tid);      

        for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
                a[i][j] = tid + i + j;

        printf("Thread %d done. Last element= %f\n", tid, a[N-1][N-1]);
    } 
}
