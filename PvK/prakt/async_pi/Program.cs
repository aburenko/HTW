using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace async_pi
{
    class Program
    {
        static async Task<double> calcPiAsync() {
            Task<double> t = new Task<double>(() => normal_pi());
            t.Start();
            double pi = await t;
            return pi;        }

        static async Task<double> ReadFromNetworkAsync(string url)
        {
            Console.WriteLine("loading pi...");
            var client = new WebClient();
            var sw = Stopwatch.StartNew();
            string result = await client.DownloadStringTaskAsync(url);
            result = result.Replace(".", ",");
            double pi = Double.Parse(result);
            Console.WriteLine("pi loaded in {0}s: {1}", sw.ElapsedMilliseconds / 1000f, result);
            sw.Stop();
            return Double.Parse(result);
        }

        static async Task<double> readPiAsync() {
            double result = await ReadFromNetworkAsync("https://www.angio.net/pi/digits/50.txt");
            return result;
        }
        
        static void Main(string[] args)
        {
            Task<double> c_pi = calcPiAsync();
            Task<double> r_pi = readPiAsync();
            Task.WaitAll(new Task[] {c_pi, r_pi});
            Console.WriteLine("differenz: {0}", r_pi.Result - c_pi.Result);
            Console.ReadKey();
        }

        static double normal_pi()
        {
            Console.WriteLine("berechne pi...");
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

            Console.WriteLine("pi berechnet in {0}s: {1}", stopwatch.ElapsedMilliseconds / 1000f , pi);
            return pi;
        }
    }
}
