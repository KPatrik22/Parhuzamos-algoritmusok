using System;
using System.Threading;
using System.Diagnostics;

namespace PrimeCountingParallel
{
    class Program
    {
        struct ThreadArgs
        {
            public int start;
            public int end;
            public int threadId;
        }

        static class Globals
        {
        public static int total;
        }

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

            Globals.total++;
            return true;
        }

        static void CountPrimes(object args)
        {
            ThreadArgs threadArgs = (ThreadArgs)args;
            int start = threadArgs.start;
            int end = threadArgs.end;
            int threadId = threadArgs.threadId;

            Console.WriteLine($"Thread {threadId} counting primes from {start} to {end}");

            int count = 0;
            for (int i = start; i <= end; ++i)
            {
                if (IsPrime(i))
                    count++;
            }

            Console.WriteLine($"Thread {threadId} found {count} prime numbers");
        }

        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            
            Globals.total = 0;
            
            const int MAX_THREADS = 4;
            const int powers = 20;
            int distribution = (int)Math.Pow(2, powers)/MAX_THREADS;

            Thread[] threads = new Thread[MAX_THREADS];
            ThreadArgs[] threadArgs = new ThreadArgs[MAX_THREADS];
            int threadCount = 0;

            for (int i = 0; i < MAX_THREADS; ++i)
            {
                int start = i * distribution + 1;
                int end = (int)Math.Pow(2, powers)-((MAX_THREADS-i-1)*distribution);

                if (threadCount < MAX_THREADS)
                {
                    threadArgs[threadCount].start = start;
                    threadArgs[threadCount].end = end;
                    threadArgs[threadCount].threadId = threadCount;
                    threads[threadCount] = new Thread(CountPrimes);
                    threads[threadCount].Start(threadArgs[threadCount]);
                    threadCount++;
                }
                else
                {
                    int threadIndex = 0;
                    threads[threadIndex].Join();
                    threadArgs[threadIndex].start = start;
                    threadArgs[threadIndex].end = end;
                    threadArgs[threadIndex].threadId = threadIndex;
                    threads[threadIndex] = new Thread(CountPrimes);
                    threads[threadIndex].Start(threadArgs[threadIndex]);
                }
            }

            for (int i = 0; i < threadCount; ++i)
            {
                threads[i].Join();
            }

            Console.WriteLine($"Primes found under {(int)Math.Pow(2, powers)}: {Globals.total}");
            stopwatch.Stop();
            TimeSpan stopwatchElapsed = stopwatch.Elapsed;
            Console.WriteLine($"Runtime: {stopwatchElapsed.TotalSeconds} sec");
        }
    }
}
