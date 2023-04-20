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

    printf("Process %d starting\n", rank);
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

    int heightA = ?
    int widthA = ?
    int heightB = ?
    int widthB = ?

    if (? != ?) {
        printf("the matrices cannot be multiplied\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int heightC = ?;
    int widthC = ?;

    // ---------------------------------------------------- scatter

    int rowsPerProcess = ?;
    int rest = ?;
    if (rest) {
        printf("the number of processes must be a divisor of the number of lines\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int partMatrixA[?][?];
    int partMatrixC[?][?];

    MPI_Scatter(?);

    // ---------------------------------------------------- calculate

    //TODO

    // ---------------------------------------------------- gather

    int matrixC[?][?];

    MPI_Gather(?);

    // ---------------------------------------------------- print result

    if (rank == 0) {
        //TODO
    }

    // ----------------------------------------------------
    time = MPI_Wtime() - time;
    printf("Process %d time = %g\n", rank, time);

    MPI_Finalize();
    return 0;
}
