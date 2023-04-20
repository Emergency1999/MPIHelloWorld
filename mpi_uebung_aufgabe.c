#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int id;
    double time;

    int matrix1[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};
    int matrix2[3][2] = {
        {0, 1},
        {2, 3},
        {4, 5}};


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    printf("Process %d starting\n", id);
    time = MPI_Wtime();
    if (id == 0) {
        //TODO
    } else if (id <= 2) {
        //TODO
    } else {
        printf("Process %d is not used\n", id);
    }
    time = MPI_Wtime() - time;
    printf("Process %d time = %g\n", id, time);

    MPI_Finalize();
    return 0;
}
