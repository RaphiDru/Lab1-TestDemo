#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
// Each thread computes single element in the resultant matrix
void *rank3TensorMultPThread(void *arg)
{ 
    int *data = (int *)arg;
    int k = 0, i = 0;
    int x = data[0];
    for (i = 1; i <= x; i++)
        k += data[i] * data[i + x];

    int *p = (int *)malloc(sizeof(int));
    *p = k;
    // Used to terminate a thread and the return value is passed as a pointer
    pthread_exit(p);
}

int main()
{
    int N = 30;
    srand(time(NULL));
    int matA3[N][N][N];
    int matB3[N][N][N];

    // Generating random values between 0 and 20 in matA2
    for (int h = 0; h < N; h++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                matA3[h][i][j] = rand() % 21;

    // Generating random values between 0 and 20 in matB2
    for (int h = 0; h < N; h++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                matB3[h][i][j] = rand() % 21;

    // Displaying matA2
    printf("MATRIX A IS : \n");
    for (int h = 0; h < N; h++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%d ", matA3[h][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    // Displaying matB2
    printf("MATRIX B IS : \n");
    for (int h = 0; h < N; h++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%d ", matB3[h][i][j]);
            printf("\n");
        }
        printf("\n");
    }

    int value = N * N * N;
    // declaring array of threads of size N*N*N
    pthread_t *threads;
    threads = (pthread_t *)malloc(value * sizeof(pthread_t));

    int count = 0;
    int *data = NULL;
    int counter = 0;
    for (int h = 0; h < N; h++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                // storing row and column elements in data
                data = (int *)malloc((20) * sizeof(int));
                data[0] = N;
                for (int k = 0; k < N; k++)
                    data[k + 1] = matA3[h][i][k];

                for (int k = 0; k < N; k++)
                    data[k + N + 1] = matB3[h][k][j];

                if (pthread_create(&threads[count++], NULL, rank3TensorMultPThread, (void *)(data)) != 0)
                {
                    return 1;
                }
                // printf("Thread %d has started\n", counter++); //used for debuging purposes
            }
    printf("RESULTANT MATRIX IS : \n");
    int track = 0;
    for (int i = 0; i < value; i++)
    {
        void *k;
        // Joining all threads and collecting return value
        if (pthread_join(threads[i], &k) != 0)
        {
            return 2;
        }
        // printf("Thread %d has ended\n", i);//used for debuging purposes
        int *p = (int *)k;
        printf("%d ", *p);
        if ((i + 1) % N == 0)
            printf(" \n");
        track++;
        if (track == N * N)
        {
            printf("\n");
            track = 0;
        }
    }
    printf("\n");
    return 0;
}