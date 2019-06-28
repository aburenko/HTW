using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForms
{
    
    public partial class Form1 : Form
    {
        private void refreshMatch()
        {
            ComboBox cb1 = this.comboBox1;
            ComboBox cb2 = this.comboBox2;

            int indx1 = cb1.SelectedIndex;
            int indx2 = cb2.SelectedIndex;


            if (indx1 > -1 && indx2 > -1)
            {
                this.label4.Text = Program.matchMatrix[indx1, indx2];
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            refreshMatch();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            refreshMatch();
        }
    }
}
