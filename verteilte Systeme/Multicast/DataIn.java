import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Arrays;


public class DataIn {
	int kanal;
	NetInOut   myNetIn;
	FileInOut  myFileIn;
	
	public DataIn(int kanal)  {
		this.kanal = kanal;
		switch (kanal) {
		case 4:  // Net in
			myNetIn   = new NetInOut();
			break;			
		case 5:  // File in
			myFileIn  = new FileInOut(1);								
			break;			
		default:
			break;
		}								
	}
	
	public float getValue() throws IOException  {
		float value = 0;
		switch (kanal) {
		case 4:  // Net in
			value = myNetIn.getValue();
			break;			
		case 5:  // File in
			value = myFileIn.getValue();								
			break;			
		default:
			break;
		}
		return value;
	}
	
	public static void main(String[] args) {
            System.out.println("start");
            NetInOut nio = new NetInOut();
            for(int i=0; i<10; i++)
                try {
                    System.out.println(nio.getValue());
                } catch(Exception e) {
                    e.printStackTrace();
                }
	}
}

/* ***************************************************    */
class FileInOut {
	// Floting values, separated by space or newline e.g. 1.23e+001 -2.3e-002 ...
	String dateiIn 		 = "dcf77-44100-1tg.dat";
	StreamTokenizer st;	
	OutputStreamWriter outs;
	
	FileInOut( int  io)  {		
		FileInputStream   fin = null;
		try {
			fin = new FileInputStream( dateiIn );
		} catch (FileNotFoundException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
		InputStreamReader ins = new InputStreamReader(fin);		
		BufferedReader 	  br  = new BufferedReader(ins);				
		st  = new StreamTokenizer(br);
		st.resetSyntax();		
		st.wordChars('0', '9');
		st.wordChars('e', 'e');
		st.wordChars('E', 'E');
		st.wordChars('+', '.');
		st.whitespaceChars(0, 32);
	}
	
	float getValue() {		
		try {
			if ( st.nextToken() == StreamTokenizer.TT_EOF)  throw new IOException("End of File reached...");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
		return Float.parseFloat( st.sval);		
	}		
}

/* ***************************************************    */
class NetInOut {
	String group_ip       = "225.0.0.1";
	InetAddress mcAddress = null;
	MulticastSocket socket;
        int port 	      = 3333; 
	int samples           = 441;   // 882 Bytes pro Paket
	int recCounter        = 0;    // sampleCounter
	int recPaketCounter   = 0;
	byte[] buffer;

	int packetLength    = 886;
	byte[] receiveData  = new byte[packetLength];   
	
	NetInOut() {
		try {
			mcAddress = InetAddress.getByName(group_ip);
			socket    = new MulticastSocket(port);
			socket.setTimeToLive(1);
			socket.joinGroup(mcAddress);
		} catch (Exception e) {
			e.printStackTrace();
		}
		buffer = new byte[2];
	}
	
	float getValue() throws IOException {
            //  Daten von UDP-Paketen 
            if ( recCounter == samples || recPaketCounter == 0){
                // Datagramm empfangen
                DatagramPacket dp = new DatagramPacket(receiveData, receiveData.length);
                recCounter = 0;
                socket.receive(dp);
                // Paketnummer aus Paket extrahieren
                byte[] aktPaketBytes = Arrays.copyOfRange(receiveData, receiveData.length-4, receiveData.length);
                int aktPaket = ByteBuffer.wrap(aktPaketBytes).getInt();
                if (recPaketCounter != aktPaket )  {
                    System.out.println("Paket(e) verloren erwartet Nr.:" + recPaketCounter + " erhalten Nr.: " + aktPaket);
                }   
                recPaketCounter = aktPaket + 1;
            }
            buffer[0] = receiveData[2*recCounter];
            buffer[1] = receiveData[2*recCounter+1];
            recCounter++;
            // Umwandlung in float
            return ((float) ( (buffer[0]<<8) | (buffer[1] & 0xFF) ) / 32768.0f);
	}
}
