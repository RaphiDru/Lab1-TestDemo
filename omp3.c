#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void rank3TensorMultOpenMP(int h, int i, int j, int k, int N, int matA3[][N][N], int matB3[][N][N], int matC3[][N][N])
{
#pragma omp for
    for (h = 0; h < N; h++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matC3[h][i][j] = 0.0;
                for (k = 0; k < N; k++)
                {
                    matC3[h][i][j] = matC3[h][i][j] + matA3[h][i][k] * matB3[h][k][j];
                }
            }
        }
    }
}

int main()
{
    int N = 10;
    int matA3[N][N][N];
    int matB3[N][N][N];
    int matC3[N][N][N];
    int h, i, j, k;
    srand(time(NULL));
    int cores_num = 4;
    omp_set_num_threads(cores_num);

#pragma omp parallel shared(matA3, matB3, matC3) private(i, j, k)
    {
#pragma omp for
        for (h = 0; h < N; h++)
        {
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    matA3[h][i][j] = rand() % 21;
                }
            }
        }
#pragma omp for
        for (h = 0; h < N; h++)
        {
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    matB3[h][i][j] = rand() % 21;
                }
            }
        }
        rank3TensorMultOpenMP(h, i, j, k, N, matA3, matB3, matC3);
    }
    printf("MATRIX A IS : \n");
    for (h = 0; h < N; h++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
                printf("%d ", matA3[h][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    printf("MATRIX B IS : \n");
    for (h = 0; h < N; h++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
                printf("%d ", matB3[h][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    printf("RESULTANT MATRIX IS : \n");
    for (h = 0; h < N; h++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                printf("%d ", matC3[h][i][j]);
                if (j == N - 1)
                {
                    printf("\n");
                }
            }
        }
        printf("\n");
    }
    return 0;
}