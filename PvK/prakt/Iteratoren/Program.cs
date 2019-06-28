using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Iteratoren
{
    class Program
    {
        static void Main(string[] args)
        {
            Translations translatations = new Translations();
            translatations.AddTranslation("Auto", "car", "voiture");
            translatations.AddTranslation("Katze", "cat", "chat");
            translatations.AddTranslation("schwarz", "black", "noir");

            foreach (string s in translatations)
                Console.WriteLine(s); // return all words in all languages

            Console.WriteLine("\nGerman first:");
            foreach (string s in translatations.GermanWords()) {
                Console.WriteLine(s); // return first german words
                break;
            }

            Console.WriteLine("\nGerman all:");
            foreach (string s in translatations.GermanWords())
            {
                Console.WriteLine(s); // return all german words
            }

            Console.ReadKey();
        }
    }
}
