using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace first_Class
{
    abstract class HSMitglied : Person
    {
        static public int IDCounter = 0;
        protected int ID { get; private set; }

        public HSMitglied (string name, string surname, DateTime birthday) 
            : base(name, surname, birthday)
        {
            ID = IDCounter++;
        }
    }
}
