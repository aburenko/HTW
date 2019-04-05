import java.io.*;

class Stream1 {
    public static void main (String [] args) {
    FileInputStream myStream;
        try { 
        
            myStream = new FileInputStream("Taxigeschichten.txt");
        
            int byteAvailable = myStream.available();
            byte [] buff = new byte[byteAvailable];
            myStream.read(buff, 0, byteAvailable);
            System.out.println(new String(buff) + " -___- " + byteAvailable);
            
        } catch (Exception e) {
            System.out.println(e);
            return;
        }
    }
}
