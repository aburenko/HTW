import java.io.*; 
import java.net.*; 
class TCPClientAlice { 

    public static void main(String argv[]) throws Exception 
    { 

        BufferedReader inFromUser = 
          new BufferedReader(new InputStreamReader(System.in)); 

        Socket clientSocket = new Socket("localhost", 6789); 

        DataOutputStream outToServer = 
          new DataOutputStream(clientSocket.getOutputStream());

		FileInputStream fileIn = new FileInputStream("alice.txt");
	
		byte[] buffer = new byte[1024];
	
		while(fileIn.available() > 0) {
	    	outToServer.write(buffer, 0, fileIn.read(buffer)); 
		}

		clientSocket.close(); 
                   
    } 
} 
