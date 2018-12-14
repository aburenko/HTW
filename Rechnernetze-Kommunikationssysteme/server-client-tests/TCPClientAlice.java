import java.io.*; 
import java.net.*;
class TCPClientAlice {

    public static void main(String argv[]) throws Exception
    {
        // create new client socket
        Socket clientSocket = new Socket("localhost", 6789);
        // set a output stream for client
        DataOutputStream outToServer =
          new DataOutputStream(clientSocket.getOutputStream());
        // get file to read from it
		FileInputStream fileIn = new FileInputStream("alice.txt");
	    // arrange new buffer for sending a data from file
		byte[] buffer = new byte[1024];
	    // check if there are available bytes to send
		while(fileIn.available() > 0) {
		    // send bytes from buffer from 0...number of bytes read
	    	outToServer.write(buffer, 0, fileIn.read(buffer));
		}
		// close socket when all bytes are sent
		clientSocket.close();
    }
}
