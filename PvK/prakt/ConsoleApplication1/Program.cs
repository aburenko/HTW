using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            Console.Write("Kapital:");
            double kapital = double.Parse(Console.ReadLine());

            Console.Write("Jahren:");
            int jears = int.Parse(Console.ReadLine());

            Console.Write("Zinsen:");
            double fee = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine(fee);

            for (int i = 0; i < jears; i++)
            {
                kapital += (double)(kapital * fee);
                Console.WriteLine("Jahr {0}: {1:c2}", i, kapital);
            }
            // TODO
            Console.WriteLine("Das Endkapital beträgt {0:c4} bei einem Zinssatz von {1}",
                Math.Pow(kapital, 0), fee);

            Console.ReadKey();
        }
    }
}
