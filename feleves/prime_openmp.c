#include<stdio.h>  
#include<math.h>  
#include<stdlib.h>
#include<omp.h>

#define N 16

void prime_number_sweep (int n_low, int n_high, int n_factor);
int prime_number (int n);

int main()
{
    int n_low = pow(2,0);
    int n_high = pow(2,N);
    int n_factor = 2;

    omp_set_dynamic(0);
    omp_set_num_threads(8); //number of threads

    double time = omp_get_wtime();

    prime_number_sweep (n_low, n_high, n_factor);

    time = omp_get_wtime()-time;
    printf("Runtime: %f sec", time);

    return 0;
}

void prime_number_sweep (int n_low, int n_high, int n_factor )
{
    int primes;
    int count = 0;

    while (n_low <= n_high)
    {
        primes = prime_number(n_low);

        printf ( "Number of primes between 1 and 2^%d: %d \n", count, primes);
        count++;
        n_low *= n_factor;
    }

    return;
}

int prime_number (int n)
{
    int i;
    int j;
    int prime;
    int sum = 0;

# pragma omp parallel \
  shared (n) \
  private (i, j, prime)

# pragma omp for reduction (+ : sum)
    for ( i = 2; i <= n; i++ )
    {
        prime = 1;

        for ( j = 2; j < i; j++ )
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