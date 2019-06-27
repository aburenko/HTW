using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bruch
{
    public class Bruch : IComparable
    {
        public int top { get; set; }
        public int bot { get; set; }
        public bool minus { get; set; }
        public Bruch(int ntop, int nbot) {
            minus = false;
            if (ntop < 0)
            {
                minus = !minus;
                ntop *= -1;
            }
            if (nbot < 0)
            {
                minus = !minus;
                nbot *= -1;
            }

            top = ntop;
            bot = nbot;
        }

        public override string ToString()
        {
            string answer = "";
            if (minus) answer += "-";
            answer += top + "/" + bot;
            return answer;
        }
        
        public static bool operator < (Bruch thisB, Bruch thatB)
        {
            double thisValue = (double)thisB.top / (double)thisB.bot;
            if (thisB.minus) thisValue *= -1;
            double thatValue = (double)thatB.top / (double)thatB.bot;
            if (thatB.minus) thatValue *= -1;
            return thisValue < thatValue;
        }

        public static bool operator > (Bruch thisB, Bruch thatB)
        {
            double thisValue = (double)thisB.top / (double)thisB.bot;
            if (thisB.minus) thisValue *= -1;
            double thatValue = (double)thatB.top / (double)thatB.bot;
            if (thatB.minus) thatValue *= -1;
            return thisValue > thatValue;
        }

        public int CompareTo(object other)
        {
            if (other == null) return 1;

            Bruch that = other as Bruch;

            if (this < that) 
            {
                return -1;
            }
            else if (this > that)
            {
                return 1;
            }
            return 0;
        }
    }
}
