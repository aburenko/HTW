using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bruch
{
    class Program
    {
        static void Main(string[] args)
        {
            Bruch b1 = new Bruch(1, -2);
            Bruch b2 = new Bruch(1, 3);
            Console.WriteLine("{0} < {1} = {2}", b1, b2, b1 < b2);
            Console.WriteLine("{0} > {1} = {2}", b1, b2, b1 > b2);

            Console.ReadKey();
        }
    }
}
