#include <iostream>
#include <math.h>
#include <time.h>

#include "my_library.h"

// shw
int main(int argc, char *argv[])
{


    int matrixSize = -1;
    int numberOfTests = -1;
    int blockSize = -1;

    if (argc < 2)
    {
        printf("No matrix size was provided. Defaulting to 1. \n");
        matrixSize = 1;
    }
    else
    {
        matrixSize = atoi(argv[1]);
        numberOfTests = atoi(argv[2]);
        if (argc >= 4) 
        {
            blockSize = atoi(argv[3]);
        }
    }
    int size = pow(2, matrixSize);

    printf("The size of the matrix is %dx%d \n",size,size );

    if(blockSize == -1)
    {
        printf("No block size was provided. Will work with full matrix \n");
    }
    else 
    {
        printf("Block size is %d \n", blockSize);
    }

    if (size % blockSize != 0) {
        printf("Block size must be a multiple of the matrix size.\n");
        exit(1);
    }

    DATA_TYPE **matrix = createMatrix(size);

    initializeMatrixValues(matrix, size);

    const char* message = "Original \n";
    printMatrix(matrix,size, message);

    double total_elapsed = 0.0;

    printf("Effective bandwidth (gbps) / Elapsed Time: \n");
    for (int i=0; i< numberOfTests ; ++i)
    {
        flush_cache();
        clock_t begin = clock();
        
        __builtin_assume_aligned(matrix,64);

        if(blockSize == -1)
        {
            transposeMatrix(matrix, size);
        }
        else 
        {
            transposeMatrix(matrix, size, blockSize);
        }
        clock_t end = clock();

        double elapsed_temp = double(end - begin) / CLOCKS_PER_SEC;

        printf("%f, %f\n", calculate_effective_bandwidth(size, elapsed_temp), elapsed_temp);

        total_elapsed +=  elapsed_temp;
    }
    
    printf("\n");

    double average_time = total_elapsed/numberOfTests;
    // we calculate the average effective bandwidth
    double effective_bandwidth = calculate_effective_bandwidth(size, average_time);

    printf("Average Effective bandwidth gb/sec: %f\n", effective_bandwidth);
    printf("Average time: %f\n", average_time);

    message = "Transpose \n";
    printMatrix(matrix,size, message);

    freeMemory(matrix, size);
}

