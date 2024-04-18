#include <iostream>
#include "my_library.h"

#define CACHE_SIZE 39424 * 1024  // Kilobytes to bytes

void printMatrix(DATA_TYPE **array, int size, const char *message) 
{
    if(size < 5)
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
        //matrix[i] = (DATA_TYPE*)aligned_alloc(64, size * sizeof(DATA_TYPE));
        matrix[i] = (DATA_TYPE*)malloc( size * sizeof(DATA_TYPE));
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
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            //__builtin_prefetch(&matrix[j][i], 0, 1);
            DATA_TYPE temp =  matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
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