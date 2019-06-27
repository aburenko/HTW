using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_Class
{
     class Person
    {
        public string name { get; private set; }
        public string surname { get; private set; }
        public DateTime dt;
        public DateTime Dt
        {
            get { return dt; }
            private set {
                DateTime ndt = value;
                if (ndt.Year < 1900)
                {
                    Console.Write("Born date of {0} < 1900, write it one more time:", name);
                    int yearInput = int.Parse(Console.ReadLine());
                    Dt = new DateTime(yearInput, ndt.Month, ndt.Day);
                }
            }
        }

        public Person(string nname, string nsurname, DateTime ndt)
        {
            name = nname;
            surname = nsurname;
            dt = ndt;
        }

        public int getAge()
        {
            DateTime now = DateTime.Now;
            int nowY = now.Year;
            int dob = dt.Year;
            int age = nowY - dob;
            if (now.Month < dt.Month || (now.Month == dt.Month && now.Day < dt.Day))
                age--;
            return age;
        }

        public virtual void print()
        {
            Console.WriteLine("name: {0} {1} born at: {2}",
                name, surname, getAge());
        }
    }
}
