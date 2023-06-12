using System;
using System.Diagnostics;

namespace PrimeCountingSeq
{
    class Program
    {
        static bool IsPrime(int num)
        {
            if (num < 2)
                return false;

            int limit = (int)Math.Sqrt(num);
            for (int i = 2; i <= limit; ++i)
            {
                if (num % i == 0)
                    return false;
            }

            return true;
        }

        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            
            const int powers = 24;
            int count = 0;

            for (int i = 1; i <= (int)Math.Pow(2, powers); ++i)
            {
                if (IsPrime(i))
                    count++;
            }

            Console.WriteLine($"Primes found under {(int)Math.Pow(2, powers)}: {count}");

            stopwatch.Stop();
            TimeSpan stopwatchElapsed = stopwatch.Elapsed;

            Console.WriteLine($"Runtime: {stopwatchElapsed.TotalSeconds} sec");
        }
    }
}
