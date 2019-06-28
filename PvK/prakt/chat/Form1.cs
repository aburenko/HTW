using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace chat
{
    public partial class Form1 : Form
    {
        private Client c;

        public void writeStatus(String m) 
        {
            try
            {
                this.status.Text = m;
            }
            catch (Exception ex) { writeStatus("..."); } 
        }
        public string getText()
        {
            return this.textBox.Text;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                c.send();
            }
            catch (Exception ex) { writeStatus("cant send!"); } 
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void connectionToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void serverToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void connectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            c = new Client();
        }

        private void disconnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            c = null;
        }
    }
}
