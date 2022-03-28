#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *rank2TensorMultPThread(void *arg)
{
    int *newArr = (int *)arg;
    int hold = 0, i = 0, x = newArr[0];
    for (i = 1; i <= x; i++)
        hold += newArr[i] * newArr[i + x];

    int *memoryalloc = (int *)malloc(sizeof(int));
    *memoryalloc = hold;
    pthread_exit(memoryalloc);
}

int main()
{
    int N = 80;
    srand(time(NULL));
    int matA2[N][N];
    int matB2[N][N];
    int value = N * N;
    pthread_t *P_Thread;
    P_Thread = (pthread_t *)malloc(value * sizeof(pthread_t));
    int counter = 0;
    int *newArr = NULL;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matA2[i][j] = rand() % 21;
            matB2[i][j] = rand() % 21;
        }
    }

    printf("MATRIX A IS : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", matA2[i][j]);
        printf("\n");
    }

    printf("MATRIX B IS : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", matB2[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            newArr = (int *)malloc(value * sizeof(int));
            newArr[0] = N;
            for (int k = 0; k < N; k++)
            {
                newArr[k + 1] = matA2[i][k];
                newArr[k + N + 1] = matB2[k][j];
            }

            if (pthread_create(&P_Thread[counter++], NULL,
                               rank2TensorMultPThread, (void *)(newArr)) != 0)
            {
                return 1;
            }
        }

    printf("RESULTANT MATRIX IS : \n");
    for (int i = 0; i < value; i++)
    {
        void *k;
        if (pthread_join(P_Thread[i], &k) != 0)
        {
            return 2;
        }

        int *p = (int *)k;
        printf("%d ", *p);
        if ((i + 1) % N == 0)
            printf("\n");
    }
    return 0;
}