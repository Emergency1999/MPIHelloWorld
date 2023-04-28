#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    double time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Rank %d starting\n", rank);
    time = MPI_Wtime();
    // ----------------------------------------------------

    int matrixA[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {0, 1, 2}};
    int matrixB[3][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};

    int heightA = (sizeof matrixA) / (sizeof matrixA[0]);
    int widthA = (sizeof matrixA[0]) / (sizeof matrixA[0][0]);
    int heightB = (sizeof matrixB) / (sizeof matrixB[0]);
    int widthB = (sizeof matrixB[0]) / (sizeof matrixB[0][0]);

    if (widthA != heightB) {
        printf("the matrices cannot be multiplied\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int heightC = heightA;
    int widthC = widthB;

    // ---------------------------------------------------- scatter

    int rowsPerProcess = heightC / size;
    int rest = heightC % size;
    if (rest) {
        printf("the number of processes must be a divisor of the number of lines\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int partMatrixA[rowsPerProcess][widthA];
    int partMatrixC[rowsPerProcess][widthC];

    MPI_Scatter(matrixA, rowsPerProcess * widthA, MPI_INT, partMatrixA, rowsPerProcess * widthA, MPI_INT, 0, MPI_COMM_WORLD);

    //* DEBUG print partMatrixA
    for (int y = 0; y < rowsPerProcess; y++) {
        for (int x = 0; x < widthA; x++) {
            if (rank == 0) printf("Rank %d partMatrixA[%d][%d] = %d\n", rank, y, x, partMatrixA[y][x]);
        }
    }

    // ---------------------------------------------------- calculate

    for (int y = 0; y < widthC; y++) {
        for (int r = 0; r < rowsPerProcess; r++) {
            partMatrixC[r][y] = 0;
            for (int x = 0; x < widthA; x++) {
                partMatrixC[r][y] += partMatrixA[r][x] * matrixB[x][y];
            }
        }
    }

    //* DEBUG print partMatrixC
    for (int y = 0; y < rowsPerProcess; y++) {
        for (int x = 0; x < widthC; x++) {
            if (rank == 0) printf("Rank %d partMatrixC[%d][%d] = %d\n", rank, y, x, partMatrixC[y][x]);
        }
    }

    // ---------------------------------------------------- gather

    int matrixC[heightC][widthC];

    MPI_Gather(partMatrixC, rowsPerProcess * widthC, MPI_INT, matrixC, rowsPerProcess * widthC, MPI_INT, 0, MPI_COMM_WORLD);

    // ---------------------------------------------------- print result

    if (rank == 0) {
        printf("\nRank 0 result matrix:\n");
        for (int y = 0; y < heightC; y++) {
            for (int x = 0; x < widthC; x++) {
                printf("%d ", matrixC[y][x]);
            }
            printf("\n");
        }
    }

    // ----------------------------------------------------
    time = MPI_Wtime() - time;
    printf("Rank %d time = %g\n", rank, time);

    MPI_Finalize();
    return 0;
}
