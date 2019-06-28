using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace word_cloud_interface
{
    class FloatingLabel : Label
    {
        public FloatingLabel(string text, int size)
            : base() 
        {
            this.Text = text;
            this.Location.Y = 1;
            this.Location.X = 1;
        }
    }
}
