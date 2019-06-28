using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using word_cloud;

namespace word_cloud_interface
{
    static class Program
    {
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            CountedList<string> newList = word_cloud.Program.getStringCountedList();
            foreach (var i in newList) {
                new FloatingLabel(i.Value, i.Counter);
            }
        }
    }
}
