using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForms
{
    class BlinkLabel : Label
    {
        public BlinkLabel() : base() 
        {
            Timer t = new Timer();
            // Hook up the Elapsed event for the timer. 
            t.Interval = 1000; // specify interval time as you want
            t.Tick += new EventHandler(timerTick);
            t.Start();
        }
        private void timerTick(object sender, EventArgs e)
        {
            this.Visible = !this.Visible;
        }
    }
}
