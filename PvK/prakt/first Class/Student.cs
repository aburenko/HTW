using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_Class
{
    class Student : HSMitglied
    {
        public Student(string name, string surname, DateTime birthday) 
            : base(name, surname, birthday)
        {
        }
        public override void print()
        {
            Console.WriteLine("name: {0} {1} born at: {2} id: {3}",
                name, surname, getAge(), ID);
        }
    }
}
