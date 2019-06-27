using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace word_cloud
{
    public class CountedList<T> : List<CountedElement<T>>
    {

        public override string ToString()
        {
            string str = "elementss: \n";
            foreach (CountedElement<T> x in this)
            {
                str += x.ToString();
                str += "\n";
            }
            return str.ToString();
        }

        public void addCounterElement(T elem) 
        {
            CountedElement<T> cursor 
                = this.Find(x => x.Value.Equals(elem));
            if (cursor != null) cursor.increment();
            else {
                this.Add(new CountedElement<T>(elem));
            }
        }
    }
}
