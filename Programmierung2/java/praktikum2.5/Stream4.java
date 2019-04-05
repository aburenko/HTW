import java.io.*;

class Stream4 {
    public static void main (String [] args) {
    FileInputStream myStream;
        try { 
            File myFile = new File("Taxigeschichten.txt");
            FileReader in = new FileReader(myFile);
            CharArrayWriter bytesOS = new CharArrayWriter();
            
            char [] buff = new char[1024];
            int bytesRead = 0;
            
            
            while ((bytesRead=in.read(buff, 0, 1024)) > -1) { // schreiben in Zwischenspeicher buff
                bytesOS.write(buff, 0, bytesRead); // schreiben von buf in bytesOS
            }
                
            System.out.println(bytesOS.toString());
    
        } 
        catch (Exception e) {
            System.out.println(e);
            return;
        }
    }
}
