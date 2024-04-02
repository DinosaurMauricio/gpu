#include <iostream>
#ifndef DATA_TYPE
#define DATA_TYPE int
#endif

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%d"
#endif

void printMatrix(DATA_TYPE **array, int size, const char *message);
void initializeMatrixValues(DATA_TYPE **matrix, int size);
void transposeMatrix(DATA_TYPE **matrix, int size);
void freeMemory(DATA_TYPE **matrix, int size);
DATA_TYPE** createMatrix(int size);

