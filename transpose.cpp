#include <iostream>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "my_library.h"


void printProgressBar(int progress, int total) {
    const int barWidth = 50;
    float progressRatio = (float)progress / total;
    int progressBarLength = progressRatio * barWidth;

    printf("[");
    for (int i = 0; i < progressBarLength; ++i) {
        printf("=");
    }
    for (int i = progressBarLength; i < barWidth; ++i) {
        printf(" ");
    }
    printf("] %d%%\r", (int)(progressRatio * 100));
    fflush(stdout); // Flush output to ensure the progress bar is displayed immediately
}


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
        //transposeMatrix(matrix, size);
        clock_t end = clock();

        double elapsed_temp = double(end - begin) / CLOCKS_PER_SEC;
        //printf("Time measured: %f \n", elapsed_temp);
        printProgressBar(i + 1, N);
        elapsed[i] = elapsed_temp;
        total_elapsed += elapsed_temp;
    }
    
    printf("\n");
    double average_time = total_elapsed / N;
    printf("Average time: %f\n", average_time);
    
    // bytes/second
    double effective_bandwidth = (calculateWork(size) * sizeof(DATA_TYPE))/ (average_time);

    int gb_size = 1073741824;
    double effectve_bandwidth_gb_per_second = effective_bandwidth/gb_size;

    printf("Effective bandwidth gb/sec: %f\n", effectve_bandwidth_gb_per_second);

    message = "Transpose \n";
    printMatrix(matrix,size, message);

    freeMemory(matrix, size);
}

