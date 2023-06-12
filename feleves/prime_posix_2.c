#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define MAX_THREADS 4
#define POWERS 20

typedef struct 
{
    int start;
    int end;
    int thread_id;
    int count; 
} ThreadArgs;

int is_prime(int num) 
{
    if (num < 2)
        return 0;
    
    int limit = sqrt(num);
    for (int i = 2; i <= limit; ++i) {
        if (num % i == 0)
            return 0;
    }
    
    return 1;
}

void* count_primes(void* args) 
{
    ThreadArgs* thread_args = (ThreadArgs*) args;
    int start = thread_args->start;
    int end = thread_args->end;
    int thread_id = thread_args->thread_id;
    
    printf("Thread %d counting primes from %d to %d\n", thread_id, start, end);
    
    int count = 0;
    for (int i = start; i <= end; ++i) 
    {
        if (is_prime(i))
            count++;
    }
    
    printf("Thread %d found %d prime numbers\n", thread_id, count);
    
    thread_args->count = count;

    return (void*) count;
}

int main() 
{
    clock_t time = clock();
    
    pthread_t threads[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS];
    int thread_count = 0;

    int distribution = (int)pow(2, POWERS)/MAX_THREADS;
    int total_prime_count = 0;
    
    for (int i = 0; i < MAX_THREADS; ++i) 
    {
        int start = i * distribution + 1;
        int end = (int)pow(2, POWERS)-((MAX_THREADS-i-1)*distribution);
        
        if (thread_count < MAX_THREADS) 
        {
            thread_args[thread_count].start = start;
            thread_args[thread_count].end = end;
            thread_args[thread_count].thread_id = thread_count;
            pthread_create(&threads[thread_count], NULL, count_primes, (void*) &thread_args[thread_count]);
            thread_count++;
        } 
        else 
        {
            int thread_index = 0;
            pthread_join(threads[thread_index], NULL);
            thread_args[thread_index].start = start;
            thread_args[thread_index].end = end;
            thread_args[thread_index].thread_id = thread_index;
            pthread_create(&threads[thread_index], NULL, count_primes, (void*) &thread_args[thread_index]);
        }
    }
    
    for (int i = 0; i < thread_count; ++i) 
    {
        pthread_join(threads[i], NULL);
        printf("Total primes found by thread %d: %d\n", i, thread_args[i].count);
        total_prime_count += thread_args[i].count; 
    }
    
    printf("Total prime count: %d\n", total_prime_count);

    time = clock()-time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("\nRuntime: %f sec\n", time_taken);
    
    return 0;
}
