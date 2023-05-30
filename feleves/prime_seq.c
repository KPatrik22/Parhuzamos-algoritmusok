#include<stdio.h>  
#include<math.h>  
#include<stdlib.h>
#include<time.h>

#define N 20

int isprime(int num);
  
int main()  
{  
	int limit;
    int count = 0;
    clock_t time = clock();	

    for (int i = 1; i <= N; i++)
    {
        limit = pow(2,i);
        for (int j = 2; j <= limit; j++)
        {    
            if (isprime(j)){
                count++;
			}
        }
        printf("From 1 to 2^%d: %d prime numbers\n",i, count);
        count = 0;
    }  
    time = clock()-time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
	printf("\n Runtime: %f sec", time_taken);
  
    return 0;  
}

int isprime(int num)  
{  
    int prime = 1;
    int limit = sqrt(num);
  
    for(int i = 2; i <= limit; i++)  
    {  
         if(num % i == 0)  
         {  
            prime = 0;  
            break;  
         }  
    }  
  
    return(prime);  
}