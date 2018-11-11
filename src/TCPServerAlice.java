import java.io.*; 
import java.net.*; 

class TCPServerAlice { 
	public static void main(String argv[]) throws Exception 
	{
		// create a welcome socket
		ServerSocket welcomeSocket = new ServerSocket(6789); 
        // start a loop to work with clients
		while(true) {
		    // accept a client
		   	Socket connectionSocket = welcomeSocket.accept(); 
            // set a input stream
			InputStream inFromClient = connectionSocket.getInputStream();
			// set output file
			FileOutputStream fileOut = new FileOutputStream("aliceServer.txt");
            // arrange a buffer to write accepted bytes
			byte[] buffer = new byte[1024];
            // read until client has sent all bytes from file
			while(connectionSocket.isConnected()) {
			    // read client package
				int bytesRead = inFromClient.read(buffer);
				// if non was read
				if (bytesRead == -1) break;
				// write gotten bytes into the file
				fileOut.write(buffer, 0, bytesRead); 
			}
            // closes of file and socket
			fileOut.close();
			connectionSocket.close();
		} 
	} 
} 
           
