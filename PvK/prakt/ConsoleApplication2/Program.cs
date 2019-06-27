using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using BombLibrary;

namespace ConsoleApplication2
{
    class Program
    {
        static void Main(string[] args)
        {
            int pass = 0;
            string res = Bomb.defuseBomb(pass);
            while (res == "Access Denied!")
            {
                res = Bomb.defuseBomb(pass);
                pass++;
            }
            Console.WriteLine(res);
            Console.ReadKey();
        }
    }
}
