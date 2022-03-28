#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int N = 80;
    srand(time(NULL));
    int matA3[N][N][N];
    int matB3[N][N][N];
    int matC3[N][N][N];

    for (int a = 0; a < N; a++)
    {
        for (int b = 0; b < N; b++)
        {
            for (int c = 0; c < N; c++)
            {
                matA3[a][b][c] = rand() % 21;
                matB3[a][b][c] = rand() % 21;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {

                if (i == 0 && j == 0 && k == 0)
                {
                    printf("MATRIX A IS : \n");
                }
                printf("%d", matA3[i][j][k]);
                printf("  ");
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {

                if (i == 0 && j == 0 && k == 0)
                {
                    printf("MATRIX B IS : \n");
                }
                printf("%d", matB3[i][j][k]);
                printf("  ");
            }
            printf("\n");
        }
        printf("\n");
    }

    matC3[0][0][0] = 0;
    for (int a = 0; a < N; a++)
    {
        for (int i = 0; i < N; i++)
        {

            for (int j = 0; j < N; j++)
            {
                matC3[a][i][j] = 0;
                for (int k = 0; k < N; k++)
                {
                    matC3[a][i][j] += matA3[a][i][k] * matB3[a][k][j];
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {

                if (i == 0 && j == 0 && k == 0)
                {
                    printf("RESULTANT MATRIX IS : \n");
                }
                printf("%d", matC3[i][j][k]);
                printf("  ");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}