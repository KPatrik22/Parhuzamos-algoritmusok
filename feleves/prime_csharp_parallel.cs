using System;
using System.IO;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace Prime
{
    class Program
    {
        public static void Main(String[] args)
        {
            int n_low = 1;
            int n_high = Math.Pow(2,16);
            int n_factor = 2;
            int count = 0;
            int limit;
            
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            
            prime_number_sweep(int n_low, int n_high, int n_factor);

            stopwatch.Stop();
            TimeSpan stopwatchElapsed = stopwatch.Elapsed;
            Console.Write("\nRuntime: ");
            Console.WriteLine(stopwatchElapsed.TotalMilliseconds);

        }

        static int isprime(int num)  
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

        static void prime_number_sweep(int n_low, int n_high, int n_factor)
        {
            int limit;
            var options = new ParallelOptions()
            {
                MaxDegreeOfParallelism = 8
            };
            Parallel.For(n_low, n_high+1, options, i =>
            {
                limit = Math.Pow(2,i);
                for (int j = 2; j <= limit; j++)
                {    
                    if (isprime(j))
                    {
                        count++;
                    }
                }
                Console.WriteLine($"From 1 to 2^{i}: {count} prime numbers");
                count = 0;
            });
        }
        
    }
}