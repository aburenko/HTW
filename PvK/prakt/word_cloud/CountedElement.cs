using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace word_cloud
{
    public class CountedElement<T> : IComparable
    {
        private int counter;
        private T element ;

        public T Value {
            get {
                return element;
            }
        }
        public int Counter
        {
            get
            {
                return counter;
            }
        }

        public CountedElement (T e) {
            counter = 1;
            element = e;
        }

        public void increment() {
            counter++;
        }

        public override string ToString()
        {
            return (string)(counter + "/" + element);
        }

        public int CompareTo(object other) {
            if (other == null) return 1;

            CountedElement<T> that = other as CountedElement<T>;
            int thisCounter = this.counter;
            int thatCounter = that.counter;

            if (thisCounter < thatCounter)
                return -1;
            else if (thisCounter > thatCounter)
                return 1;
            return 0;
        }
    }
}
