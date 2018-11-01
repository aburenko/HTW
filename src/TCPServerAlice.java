import java.io.*; 
import java.net.*; 

class TCPServerAlice { 
	public static void main(String argv[]) throws Exception 
	{ 
		String clientSentence; 
		String capitalizedSentence; 

		ServerSocket welcomeSocket = new ServerSocket(6789); 

		while(true) {   
		   	Socket connectionSocket = welcomeSocket.accept(); 

        		InputStream inFromClient = 
             			connectionSocket.getInputStream(); 	
			FileOutputStream fileOut = new FileOutputStream("aliceServer.txt");

			byte[] buffer = new byte[1024];

			while(connectionSocket.isConnected()) {
				int bytesRead = inFromClient.read(buffer);
				
				if (bytesRead == -1) break;

				fileOut.write(buffer, 0, bytesRead); 
			}

			fileOut.close();
			connectionSocket.close();
		} 
	} 
} 
           
