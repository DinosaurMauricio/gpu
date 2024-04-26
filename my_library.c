#include <iostream>
#include <math.h>

#include "my_library.h"

void printMatrix(DATA_TYPE **array, int size, const char *message) 
{
    if(size < 10)
    {
        printf(message);

        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                printf(FORMAT_SPECIFIER" ", array[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Matrix size is to big, skipping print \n");
    }
}

DATA_TYPE** createMatrix(int size){
    DATA_TYPE **matrix = (DATA_TYPE **)malloc(size * sizeof(DATA_TYPE *));
    
    // Allocate memory for each 2D array
    for (int i = 0; i < size; i++) {
        // Allocate memory for rows
        matrix[i] = (DATA_TYPE*)aligned_alloc(64, size * sizeof(DATA_TYPE));
    }
    
    return matrix;
}

void initializeMatrixValues(DATA_TYPE **matrix, int size)
{
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

void transposeMatrix(DATA_TYPE **matrix, int size)
{
    DATA_TYPE temp;
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            // we ignore the diagonal as i stays the same
            if(i != j)
            {
                __builtin_prefetch(&matrix[j][i], 0, 1);
                temp =  matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }
}

void transposeMatrix(DATA_TYPE **matrix, int size, int blockSize)
{
    DATA_TYPE temp;
    for (int i = 0; i < size; i += blockSize)
    {
        for (int j = 0; j < size; j += blockSize)
        {
            for (int k = i; k < i + blockSize; ++k)
            {
                for (int l = j; l < j + blockSize; ++l)
                {
                        // Perform transpose only for upper triangle
                        if (l > k) { 
                            __builtin_prefetch(&matrix[l][k], 0, 1);
                            temp = matrix[k][l];
                            matrix[k][l] = matrix[l][k];
                            matrix[l][k] = temp;
                    }
                }
            }
        }
    }
}

void freeMemory(DATA_TYPE ** matrix, int size)
{
    // Free memory for each row of the matrix
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }

    // Free memory for the array of pointers to rows
    free(matrix);
}

void flush_cache() {
    const int CACHE_SIZE = 39424 * 1024;  // Kilobytes to bytes
    char *cache = (char *)malloc(CACHE_SIZE);
    if (cache == NULL) {
        fprintf(stderr, "Failed to allocate memory for cache flushing\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < CACHE_SIZE; i += 4096) {
        cache[i] = 0; // Accessing each page to ensure it's loaded into cache
    }
    free(cache);
}

int calculateWork(int size) {
    // Calculate the amount of work done (number of transpositions)
    int work = size * size;
    return work;
}

double calculate_effective_bandwidth(int size, double time)
{
    const int GB_SIZE = 1073741824;

    // bytes/second
    double effective_bandwidth = (calculateWork(size) * sizeof(DATA_TYPE))/ (time);
    double effectve_bandwidth_gb_per_second = effective_bandwidth/GB_SIZE;

    // return the effective bandwidth in gb/s
    return effectve_bandwidth_gb_per_second;
}