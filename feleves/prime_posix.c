#include<stdio.h>  
#include<math.h>  
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

const int THREADS = 8;

int n_low = pow(2,0);
int n_high = pow(2,16);
int n_factor = 2;

int isprime(int num);
void * runner(void *param);
  
int main()  
{  
	pthread_t thread[THREADS];
	
    printf("\nN threads\n");

    clock_t time = clock();
	
    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&thread[i], NULL, runner, (void *)i);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    time = clock()-time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("\nRuntime: %f\n", time_taken);
	
    return 0;  
}

int prime_number (int n)
{
    int prime;
    int sum = 0;
    for (int i = 2; i <= n; i++ )
    {
        prime = 1;
        for (int j = 2; j < i; j++ )
        {
            if ( i % j == 0 )
            {
                prime = 0;
                break;
            }
        }
        sum += prime;
    }
    return sum;
}

void * runner(void *param) 
{
    int something = atoi(param); // ???
    int primes;
    int count = 0;
 
    while (n_low <= n_high)
    {
        primes = prime_number(n_low);
        printf ("Number of primes between 1 and 2^%d: %d \n", count, primes);
        count++;
        n_low *= n_factor;
    }
}