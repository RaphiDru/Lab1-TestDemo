#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void rank2TensorMultOpenMP(int i, int j, int k, int N, int matA2[][N], int matB2[][N], int matC2[][N])
{
#pragma omp for
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matC2[i][j] = 0.0;
            for (k = 0; k < N; k++)
            {
                matC2[i][j] = matC2[i][j] + matA2[i][k] * matB2[k][j];
            }
        }
    }
}

int main()
{
    int N = 80;
    int matA2[N][N];
    int matB2[N][N];
    int matC2[N][N];
    int i, j, k;
    srand(time(NULL));
    int cores_num = 4;
    omp_set_num_threads(cores_num);

#pragma omp parallel shared(matA2, matB2, matC2) private(i, j, k)
    {

#pragma omp for
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matA2[i][j] = rand() % 21;
            }
        }

#pragma omp for
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matB2[i][j] = rand() % 21;
            }
        }
        rank2TensorMultOpenMP(i, j, k, N, matA2, matB2, matC2);
    }

    printf("MATRIX A IS : \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d ", matA2[i][j]);
        printf("\n");
    }

    printf("MATRIX B IS : \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d ", matB2[i][j]);
        printf("\n");
    }

    printf("RESULTANT MATRIX IS : \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", matC2[i][j]);
            if (j == N - 1)
            {
                printf("\n");
            }
        }
    }
    return 0;
}