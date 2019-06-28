using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Net.Sockets;

namespace chat
{
    class Client
    {
        Socket s { get; set; }
        public Client() { 

            IPAddress ipServer = IPAddress.Parse("141.56.2.105");
            int port = 20000;
            IPEndPoint EPhost = new IPEndPoint(ipServer, port);

            Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream,
                ProtocolType.Tcp);
            s.BeginConnect(EPhost, new AsyncCallback(ConnectCallback), s);
            Program.myApp.writeStatus("connected to " + ipServer);
        }

        private void ConnectCallback(IAsyncResult ar)
        { 
            try { // Complete connecting to the remote device.
                s.EndConnect(ar);
            } catch (Exception e) {
                Program.myApp.writeStatus(e.ToString());
            }
        }

        public void send() 
        {
            string send = Program.myApp.getText();
            // Begin to send data.
            byte[] bytes = Encoding.ASCII.GetBytes(send);
            s.BeginSend(bytes, 0, bytes.Length, 0,
                new AsyncCallback(ConnectCallback), s);
        }
    }
}
