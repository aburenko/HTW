using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForms
{
        
    static class Program
    {
        static public string[,] matchMatrix = new string[3,3] 
        {
            {"ungeeignet","Traumfrau/-mann","Affäre"},
            {"ungeeignet","Ehe","Winterfreund(in)"},
            {"Traumfrau/-mann","Affäre","ungeeignet"}
        };
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());


        }
    }
}
