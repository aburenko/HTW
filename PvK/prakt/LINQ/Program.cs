using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Bruch;

namespace LINQ
{
    class Program
    {
        public static IEnumerable<int> hexToNumber() {
            string hexNumbers = "D3A";
            var queryA = from hexNumber in hexNumbers select int.Parse(char.ToString(hexNumber), System.Globalization.NumberStyles.HexNumber);
            // LINQ
            foreach (var item in queryA)
            {
                Console.WriteLine(item); // Gibt 13,3,10 aus
            }
            return queryA;
        }

        public static void NumberToWord(IEnumerable<int> queryA) { 
            var digits = new System.Collections.Generic.Dictionary<int, string>();
            digits[0] = "null"; digits[1] = "eins"; digits[2] = "zwei";
            digits[3] = "drei"; digits[4] = "vier"; digits[5] = "fünf";
            digits[6] = "sechs"; digits[7] = "sieben"; digits[8] = "acht";
            digits[9] = "neun"; digits[10] = "zehn"; digits[11] = "elf";
            digits[12] = "zwölf"; digits[13] = "dreizehn"; digits[14] = "vierzehn";
            digits[15] = "fünfzehn";

            //var queryB = from a in queryA where a > 5 select digits[a];
            var queryB = from a in queryA.Where(x => x > 5) select digits[a];
            // LINQ
            foreach (var item in queryB) {
                // Gibt dreizehn, drei, zehn für "D3A" -> 13,3,10 aus queryA aus
                Console.WriteLine(item);
            }
        }

        public static void NumberToWordBig(IEnumerable<int> queryA)
        {
            var digits = new System.Collections.Generic.Dictionary<int, string>();
            digits[0] = "null"; digits[1] = "eins"; digits[2] = "zwei";
            digits[3] = "drei"; digits[4] = "vier"; digits[5] = "fünf";
            digits[6] = "sechs"; digits[7] = "sieben"; digits[8] = "acht";
            digits[9] = "neun"; digits[10] = "zehn"; digits[11] = "elf";
            digits[12] = "zwölf"; digits[13] = "dreizehn"; digits[14] = "vierzehn";
            digits[15] = "fünfzehn";

            var queryB = from a in queryA select a < 6 ? digits[a] : digits[a].ToUpper();
            // LINQ
            foreach (var item in queryB)
            {
                // Gibt dreizehn, drei, zehn für "D3A" -> 13,3,10 aus queryA aus
                Console.WriteLine(item);
            }
        }
        public static void BruchSpass()
        {
            Bruch.Bruch[] brüche = {
                new Bruch.Bruch(1, 2), new Bruch.Bruch(1, 3), new Bruch.Bruch(1, 4),
                new Bruch.Bruch(1, 5), new Bruch.Bruch(1, 6)
            };            var b = from b1 in brüche from b2 in brüche
                    select new { bruch1 = b1, bruch2 = b2, mult = new Bruch.Bruch(b1.top*b2.top, b1.bot*b2.bot)};
                    
            foreach (var item in b) {
                // Gibt z.B. aus 1/2 * 1/2 = 1/4
                Console.WriteLine("{0} * {1} = {2}",item.bruch1, item.bruch2, item.mult);
            }
        }
        public static void BruchSpassSortiert()
        {
            Bruch.Bruch[] brüche = {
                new Bruch.Bruch(1, 2), new Bruch.Bruch(1, 3), new Bruch.Bruch(1, 4),
                new Bruch.Bruch(1, 5), new Bruch.Bruch(1, 6)
            };

            var b = from b1 in brüche
                    from b2 in brüche
                    orderby new Bruch.Bruch(b1.top * b2.top, b1.bot * b2.bot)
                    select new { bruch1 = b1, bruch2 = b2, mult = new Bruch.Bruch(b1.top * b2.top, b1.bot * b2.bot) };

            foreach (var item in b)
            {
                // Gibt z.B. aus 1/2 * 1/2 = 1/4
                Console.WriteLine("{0} * {1} = {2}", item.bruch1, item.bruch2, item.mult);
            }
        }

        static void Main(string[] args)
        {
            //NumberToWord(hexToNumber());
            //NumberToWordBig(hexToNumber());
            //BruchSpass();
            BruchSpassSortiert();

            Console.ReadKey();
        }
    }
}
