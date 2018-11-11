import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileReader;
import java.net.Socket;

class TCPClientAliceAlternative {

    public static void main(String argv[]) throws Exception 
    {
        // create new client socket
        Socket clientSocket = new Socket("localhost", 6789); 
        // set a output stream for client
        DataOutputStream outToServer = 
          new DataOutputStream(clientSocket.getOutputStream());
        // set buffer to read from it
		BufferedReader bufferIn
			= new BufferedReader(new FileReader("alice.txt"));
	    // arrange new buffer for sending a data from file
		char[] buffer = new char[1024];
	    // check if there are available bytes to send
		while(bufferIn.ready()) {
		    int numBytesRead = bufferIn.read(buffer, 0, buffer.length-1);
		    buffer[numBytesRead] = '\n';
            if(numBytesRead == -1) break;
            // send bytes from buffer from 0...number of bytes read
            outToServer.writeChars(String.valueOf(buffer));
		}
		// close socket when all bytes are sent
		clientSocket.close();
    } 
} 
