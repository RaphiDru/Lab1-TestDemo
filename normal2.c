#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int N = 80;
    srand(time(NULL));
    int matA2[N][N];
    int matB2[N][N];
    int matC2[N][N];

    for (int a = 0; a < N; a++)
    {
        for (int b = 0; b < N; b++)
        {
            matA2[a][b] = rand() % 21;
            matB2[a][b] = rand() % 21;
        }
    }

    for (int h = 0; h < 2; h++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (h == 0)
                {
                    if (h == 0 && i == 0 && j == 0)
                    {
                        printf("MATRIX A IS : \n");
                    }
                    printf("%d", matA2[i][j]);
                    printf("  ");
                }
                else
                {
                    if (h == 1 && i == 0 && j == 0)
                    {
                        printf("MATRIX B IS : \n");
                    }
                    printf("%d", matB2[i][j]);
                    printf("  ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matC2[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                matC2[i][j] += matA2[i][k] * matB2[k][j];
            }
        }
    }
    printf("RESULTANT MATRIX IS : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d", matC2[i][j]);
            printf("  ");
        }
        printf("\n");
    }
    return 0;
}