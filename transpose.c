#include <iostream>
#include <math.h>
#include <time.h>

#include "my_library.h"

// shw
int main(int argc, char *argv[])
{


    int matrixSize = -1;

    if (argc < 2)
    {
        printf("No matrix size was provided. Defaulting to 1. \n");
        matrixSize = 1;
    }
    else
    {
        matrixSize = atoi(argv[1]);
    }
    int size = pow(2, matrixSize);

    printf("The size of the matrix is %dx%d \n",size,size );

    DATA_TYPE **matrix = createMatrix(size);

    initializeMatrixValues(matrix, size);

    const char* message = "Original \n";
    printMatrix(matrix,size, message);

    long long N = 1<<10; // number of tries
    double total_elapsed = 0.0;
    int* elapsed = (int*)malloc(N*sizeof(int));

    for (int i=0; i< N ; ++i)
    {
        flush_cache();
        clock_t begin = clock();
        
        //__builtin_assume_aligned(matrix,64);
        transposeMatrix(matrix, size);
        clock_t end = clock();

        double elapsed_temp = double(end - begin) / CLOCKS_PER_SEC;
        //printf("Time measured: %f \n", elapsed_temp);
        elapsed[i] = elapsed_temp;
        total_elapsed += elapsed_temp;
    }
    
    double average_time = total_elapsed / N;
    printf("Average time: %f\n", average_time);
    
    // To GB/s
    double effective_bandwidth = (calculateWork(size) * sizeof(DATA_TYPE))/ (average_time* pow(10, 9));

    printf("Effective bandwidth: %f\n", effective_bandwidth);

    message = "Transpose \n";
    printMatrix(matrix,size, message);

    freeMemory(matrix, size);
}