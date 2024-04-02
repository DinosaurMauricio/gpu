using namespace std;

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
        matrixSize = std::stoi(argv[1]);
    }
    int size = pow(2, matrixSize);

    printf("The size of the matrix is %dx%d \n",size,size );

    DATA_TYPE **matrix = createMatrix(size);

    initializeMatrixValues(matrix, size);

    const char* message = "Original \n";
    printMatrix(matrix,size, message);

    clock_t begin = clock();

    __builtin_assume_aligned(matrix,64);
    transposeMatrix(matrix, size);
    clock_t end = clock();

    message = "Transpose \n";
    printMatrix(matrix,size, message);

    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time measured: " << elapsed << endl;

    freeMemory(matrix, size);
}