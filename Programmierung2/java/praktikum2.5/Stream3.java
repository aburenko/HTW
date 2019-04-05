import java.io.*;

class Stream3 {
    public static void main (String [] args) {
    FileInputStream myStream;
        try { 
            File myFile = new File("Taxigeschichten.txt");
            FileInputStream in = new FileInputStream(myFile);
            ByteArrayOutputStream bytesOS = new ByteArrayOutputStream();
            
            byte [] buff = new byte[1024];
            int bytesRead = 0;
            
            
            while ((bytesRead=in.read(buff)) > -1) { // schreiben in Zwischenspeicher buff
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
