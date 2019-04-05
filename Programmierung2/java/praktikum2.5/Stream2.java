import java.io.*;

class Stream2 {
    public static void main (String [] args) {
    FileInputStream myStream;
        try { 
            File myFile = new File("Taxigeschichten.txt");
            int size = (int)myFile.length(); // get available bit count
            
            FileInputStream in = new FileInputStream(myFile);
            
            byte [] buff = new byte[size];
            int bytesRead = 0;
            while (bytesRead < size)
                bytesRead+=in.read(buff, bytesRead, size-bytesRead);
            
            System.out.println(new String(buff));
        } 
        catch (Exception e) {
            System.out.println(e);
            return;
        }
    }
}
