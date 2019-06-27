using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_Class
{
    class Program
    {

        static void Main(string[] args)
        {

            Person[] personen = new Person[4];
            personen[0] = new Student("Max", "Mustermann", new DateTime(1981, 8, 13));
            personen[1] = new Student("Mia", "Musterfrau", new DateTime(1993, 3, 22));
            personen[2] = new Mitarbeiter("Jane", "Doe", new DateTime(1995, 1, 15));
            personen[3] = new Mitarbeiter("Jack", "Doe", new DateTime(1995, 12, 15));


            foreach (Person p in personen) p.print();
              
            Console.ReadKey();
        }
    }
}
