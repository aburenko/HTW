import java.io.*; 
import java.net.*; 
class TCPClientPrakt { 

    public static void main(String argv[]) throws Exception 
    {   
		String sentence; 
        String modifiedSentence; 
	
        BufferedReader inFromUser = 
          new BufferedReader(new InputStreamReader(System.in)); 
	
		String adresse = new String(argv[0]);
		int port = Integer.parseInt(argv[1]);
        	Socket clientSocket = new Socket(adresse, port); 

        DataOutputStream outToServer = 
          new DataOutputStream(clientSocket.getOutputStream()); 
		BufferedReader inFromServer = 
          new BufferedReader(new InputStreamReader(clientSocket.getInputStream())); 
	
		while(true) {
			sentence = inFromUser.readLine(); 
			outToServer.writeBytes(sentence + '\n'); 

			while(inFromServer.ready()) {
				modifiedSentence = inFromServer.readLine(); 
				System.out.println("FROM SERVER: " + modifiedSentence); 
			}
		}         
    } 
} 
