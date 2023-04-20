#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    double time;

    int matrix1[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};
    int matrix2[3][2] = {
        {0, 1},
        {2, 3},
        {4, 5}};


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d starting\n", rank);
    time = MPI_Wtime();
    if (rank == 0) {
        int matrixResult[2][2];
        MPI_Recv(&matrixResult[0], 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received data from process 1\n");
        MPI_Recv(&matrixResult[1], 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received data from process 2\n");

        printf("Process 0 result matrix:\n");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                printf("%d ", matrixResult[i][j]);
            }
            printf("\n");
        }

    } else if (rank <= 2) {
        int matrixLine[2];
        int row = rank - 1;

        for (int i = 0; i < 2; i++) {
            matrixLine[i] = 0;
            for (int j = 0; j < 3; j++) {
                matrixLine[i] += matrix1[row][j] * matrix2[j][i];
            }
        }

        MPI_Send(&matrixLine, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);

    } else {
        printf("Process %d is not used\n", rank);
    }
    time = MPI_Wtime() - time;
    printf("Process %d time = %g\n", rank, time);

    MPI_Finalize();
    return 0;
}
