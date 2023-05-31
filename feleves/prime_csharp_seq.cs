using System;
using System.IO;
using System.Diagnostics;

namespace Prime
{
    class Program
    {
        public static void Main(String[] args)
        {
            int n = Math.Pow(2,16);
            int limit;
            int count = 0;
            
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            
            for(int i = 1; i <= n; i++)
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
            }  
        
            stopwatch.Stop();
            TimeSpan stopwatchElapsed = stopwatch.Elapsed;
            Console.Write("\nRuntime: ");
            Console.WriteLine(stopwatchElapsed.TotalMilliseconds);

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
            return( prime);  
        }
        
    }
}