using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace number_pi
{
    class Program
    {
        static void Main(string[] args)
        {
            //paralel_pi();
            //normal_pi();
            //task_pi();
            //paralelfor_pi();
        }

        static void paralelfor_pi()
        {
            long n = 1000000000; ;
            double pi = 0.0;
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            Console.WriteLine("start");

            Object myLock = new Object();
            Parallel.For<double>(0,n, () => 0,
                (i,pls,pi_local) => { 
                    pi_local += 4 / (1 + ((0.5 + i) / n) * ((0.5 + i) / n));
                    return pi_local;
                },
                (pi_local) => { 
                    lock (myLock) { 
                        pi += pi_local;
                    } 
                }
            );

            pi /= n;
            stopwatch.Stop();

            Console.WriteLine("pi:{0}", pi);
            Console.WriteLine("time {0}s: ", stopwatch.ElapsedMilliseconds / 1000f);
            Console.ReadKey();
        }

        static void task_pi()
        {
            long n = 1000000000;;
            double pi = 0.0;
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            Console.WriteLine("start");

            int thread_number = 8;
            double[] pi_parts = new double[thread_number * 16];
            Task[] threads = new Task[thread_number];

            for (int i = 0; i < thread_number; i++)
            {
                int k = i;
                threads[i] = new Task(
                        () => parralel_pi_calc(ref pi_parts[k * 16], (int)(k * n / thread_number), (int)((k + 1) * n / thread_number), n)
                );
                threads[i].Start();
            }

            for (int i = 0; i < thread_number; i++)
            {
                threads[i].Wait();
            }

            for (int i = 0; i < thread_number; i++)
            {
                pi += pi_parts[i * 16];
            }

            pi /= n;

            stopwatch.Stop();

            Console.WriteLine("pi:{0}", pi);
            Console.WriteLine("time {0}s: ", stopwatch.ElapsedMilliseconds / 1000f);
            Console.ReadKey();
        }

        static void paralel_pi()
        {
            long n = 1000000000;// *1000 * 1000;
            double pi = 0.0;
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            Console.WriteLine("start");

            int thread_number = 8;
            double[] pi_parts = new double[thread_number * 16];
            Thread[] threads = new Thread[thread_number];

            for (int i = 0; i < thread_number; i++)
            {
                int k = i;
                threads[i] = new Thread(
                        () => parralel_pi_calc(ref pi_parts[k * 16], (int)(k * n / thread_number), (int)((k + 1) * n / thread_number), n)
                );
                threads[i].Start();
            }

            for (int i = 0; i < thread_number; i++)
            {
                threads[i].Join();
            }

            for (int i = 0; i < thread_number; i++)
            {
                pi += pi_parts[i * 16];
            }

            pi /= n;

            stopwatch.Stop();

            Console.WriteLine("pi:{0}", pi);
            Console.WriteLine("time {0}s: ", stopwatch.ElapsedMilliseconds / 1000f);
            Console.ReadKey();
        }

        static void parralel_pi_calc(ref double pi_part, int s, int e, long n) {
            for (int i = s; i < e; i++)
            {
                double a = (0.5 + i);
                pi_part += 4 / (1 + (a / n) * (a / n));
            }
        }


        static void normal_pi() {
            long n = 1000000000;// *1000 * 1000;
            double pi = 0.0;
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            Console.WriteLine("start");

            for (int i = 0; i < n; i++)
            {
                double a = (0.5 + i);
                pi += 4 / (1 + (a / n) * (a / n));
            }
            pi /= n;

            stopwatch.Stop();

            Console.WriteLine("pi:{0}", pi);
            Console.WriteLine("time {0}s: ", stopwatch.ElapsedMilliseconds / 1000f);
            Console.ReadKey();
        }
    }
}
