using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace word_cloud
{
    public class Program
    {

        static public CountedList<string> getStringCountedList() {  
            CountedList<string> maLest = new CountedList<string>();
            string maTekst = "I am armadelo I jem yara bruda armadelo krakadila I buma krakadila buma yara yara";
            string[] words = maTekst.Split();
            foreach (string item in words)
            {
                if(item.Length > 3)
                    maLest.addCounterElement(item);
            }
            maLest.Sort();
            return maLest;
        }

        static void Main(string[] args)
        {
            CountedList<string> maLest = new CountedList<string>();
            string maTekst = "I am armadelo I jem yara bruda armadelo krakadila I buma krakadila buma yara yara";
            string[] words = maTekst.Split();
            foreach (string item in words)
            {
                if(item.Length > 3)
                    maLest.addCounterElement(item);
            }
            maLest.Sort();
            Console.Write(maLest.ToString());
            Console.ReadKey();
        }
    }
}
