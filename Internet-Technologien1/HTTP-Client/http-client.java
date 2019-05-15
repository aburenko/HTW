import java.io.*; 
import java.net.*; 
class TCPClientPrakt { 
    public static void main(String argv[]) throws Exception 
    {   
        // for www.heise.de port 80
        String sentence = "GET / HTTP/1.1\r\nHost: www.heise.de\r\n\r\n"; 
        String answer; 
	
        BufferedReader inFromUser = 
          new BufferedReader(new InputStreamReader(System.in)); 
	
        String adresse = new String(argv[0]);
        int port = Integer.parseInt(argv[1]);
        Socket clientSocket = new Socket(adresse, port); 

        DataOutputStream outToServer = 
          new DataOutputStream(clientSocket.getOutputStream()); 
          
        BufferedReader inFromServer = 
          new BufferedReader(new InputStreamReader(clientSocket.getInputStream())); 
	
        outToServer.writeBytes(sentence); 
        
        System.out.println("FROM SERVER:\n"); 
        
        while(true) {
            answer = inFromServer.readLine(); 
            System.out.println(answer); 
        }
    } 
} 
