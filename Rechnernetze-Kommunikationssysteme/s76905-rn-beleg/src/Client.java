import java.io.*;
import java.net.*;
import java.util.Arrays;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Random;
import java.util.zip.*;

import udp.UDPtransfer;

class Client extends UDPtransfer {

	public Client (String[] args) {
		parseArgs(args);
		sendingInit();
		showInit();
		while (true) {
			receiveExec();

			if(sessionFinished || receiveFailedTries)
				break;

			calcRTO();
			updateSend();

			send();

			showProgress();
		}
		showResult();
		// close socket
		thisSocket.close();
	}

    public static void main(String[] args) {
		new Client(args);
    }

	// decode args
	private void parseArgs(String[] args) {
		// check args
		// 1 - hostname
		// 2 - portnumber
		// 3 - file name
		// Check how many arguments were passed in
		if(args.length != 3)
		{
			System.out.println("usage: java Client <hostname> <port> <fileName>");
			System.exit(0);
		}
		// get ip of host by it's name
		try {
			IPAddress = InetAddress.getByName(args[0]);
		} catch (UnknownHostException e) {
			e.printStackTrace();
			System.exit(1);
		}
		// get port
		port = Integer.parseInt(args[1]);
		if (port<=0 || port>=65535)
			System.exit(0);
		// get file Name
		fileName = args[2];
	}

	@Override
	public boolean receive() throws SocketTimeoutException {
        // create a datagram for receiving
        receivePacket = new DatagramPacket(receiveData, receiveData.length);
        // wait to receive a acknowledge packet
		try {
        	thisSocket.receive(receivePacket);
		} catch (SocketTimeoutException e) {
			throw e;
		} catch (Exception e) {
			e.printStackTrace();
		}
	
        if (fileLengthSent == fileLength) {
            sessionFinished = true;
            setSocketTimeout(thisSocket, RTO_MIN*4);
	}
        boolean res = checkAck(receiveData);
        return res;
    }

	@Override
	public void send() {
		try {
        		if(DEBUG) System.out.println("Aufruf...");
			thisSocket.send(sendPacket);
		} catch(IOException e) {
			e.printStackTrace();
		}
	}

    // initialize sending
    private void sendingInit() {
        if(DEBUG) System.out.println("initializing...");
		packetNumber = 0x00;
		// get time on start
        timeFirstFull = System.currentTimeMillis();
        // create client socket
		try {
        	thisSocket = new DatagramSocket();
		} catch(SocketException e) {
			e.printStackTrace();
			System.exit(1);
		}
		// set timeout in milliseconds
		setSocketTimeout(thisSocket, eRTT);
        // arrange receive bytes arrays
        receiveData = new byte[1024];
        // convert start packet sequence
        sendData = genarateStartPacket();
        // create a datagram for sending and receiving
        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
        receivePacket = new DatagramPacket(receiveData, receiveData.length);
        // send the datagram
	/*	try {
        		if(DEBUG) System.out.println("Aufruf.INIT..");
        	thisSocket.send(sendPacket);
		} catch(IOException e) {
			e.printStackTrace();
		}*/
        // logging
        if(DEBUG) System.out.println("Start packet sent");
    }

    private void updateSend() {
		if(DEBUG) System.out.println("update");
        // create a datagram for sending
        sendData = genarateDataPacket();
        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
    }

    // check acknowledge
    private boolean checkAck(byte[] rec) {
        // devide bytes into values
        byte[] sessionNumberRec = Arrays.copyOfRange(rec, 0, 2);
        byte packetNumberRec = rec[2];
        // check consistens
        boolean b_sNrRec = Arrays.equals(sessionNumber, sessionNumberRec);
        boolean b_pNrRec = (packetNumberRec == packetNumber);
        boolean b_res = (b_sNrRec && b_pNrRec);
        // logging
        if (!b_res) {
			if(DEBUG) System.out.println("bad acknowledge, do resend");
			// resend
			send();
		}
        else if(DEBUG) System.out.println("got Acknowledge");

        return b_res;
    }

    // returns bytes for Data Packet
    private byte[] genarateDataPacket() {
		ByteArrayOutputStream sendDataBuffer = new ByteArrayOutputStream();
        // increment packageNumber
        packetNumber = (byte)((packetNumber + 0x01) & 0x01);
	if(DEBUG) System.out.println("GEN " + packetNumber);
        // get data from file
        // calculate size of package
        int packetDataSize = MTU - S_SESSION_NUMBER - S_PACKET_NUMBER;
		try {
	        if((packetDataSize - fileIn.available()) >= S_CRC32) // if have place for CRC
	            packetDataSize -= S_CRC32;
	        // get available BYTES
	        byte[] fileData = new byte[packetDataSize];
	        fileToSend = fileIn.read(fileData);
	        fileLengthSent += fileToSend;
	        // combine data packet
	        sendDataBuffer.write(sessionNumber);
	        sendDataBuffer.write(packetNumber);
		if(DEBUG) System.out.println("file to send: " + fileToSend);
        	sendDataBuffer.write(fileData, 0, fileToSend);
	        // send CRC on last packet
	        if (fileLengthSent == fileLength) {
	            // get checksum of file
	            Checksum checksum = new CRC32();
	            byte[] tempBuf = new byte[128];
	            FileInputStream fis = new FileInputStream(fileName);
	            CheckedInputStream cis = new CheckedInputStream(fis, checksum);
	            while (cis.read(tempBuf) >= 0) {}
	            // write it
	            sendDataBuffer.write(checkSumToByteArray(checksum));
	        }
		} catch (Exception e) {
			e.printStackTrace();
		}
        // return combined data packet
        return sendDataBuffer.toByteArray();
    }

    // returns bytes for Start Packet
    private byte[] genarateStartPacket() {
        // arrange a buffer for combining
        ByteArrayOutputStream sendDataBuffer = new ByteArrayOutputStream();

        // get new sessions number
        sessionNumber = generateSessionNumber();

        // get file
        File file = new File(fileName);
		try {
	        fileIn = new FileInputStream(fileName);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	
	String newName = fileName.substring(fileName.lastIndexOf( "/" ) + 1);

        // convert file length into byte array
        fileLength = file.length();
        byte[] fileLengthB = new byte[8];
        ByteBuffer lenBuf = ByteBuffer.allocate(Long.BYTES);
        lenBuf.putLong(fileLength);
        fileLengthB = lenBuf.array();

        // convert name length to byte array
        byte[] fileNameLengthB = new byte[2];
        fileNameLengthB[0] = (byte) ((newName.length() >> 8) & 0xFF);
        fileNameLengthB[1] = (byte) (newName.length() & 0xFF);

        // encode file name into UTF 8 for sending
	byte[] nameUtf = new byte[1];
	try{
        	nameUtf = newName.getBytes("UTF-8");;
	} catch(Exception e) {
		e.printStackTrace();
	}
        // create new CRC32
        CRC32 checkGen = new CRC32();

        // combine Start packet
		try {
	        sendDataBuffer.write(sessionNumber);
	        sendDataBuffer.write(packetNumber);
	        sendDataBuffer.write("Start".getBytes());
	        sendDataBuffer.write(fileLengthB ); // Write file length
	        sendDataBuffer.write(fileNameLengthB); // Write name length
	        sendDataBuffer.write(nameUtf); // Write file name UTF_8

	        // update CRC over combined bytes
	        checkGen.update(sendDataBuffer.toByteArray());
	        byte[] checkSum = checkSumToByteArray(checkGen);
	        sendDataBuffer.write(checkSum); // Write CRC32 checksum over all bytes
		} catch (IOException e) {
			e.printStackTrace();
		}

        // return combined byte array
        return sendDataBuffer.toByteArray();
    }

    // convert to 4 byte array (32 Bit)
    private byte[] checkSumToByteArray(Checksum checkSum) {
        ByteBuffer checkSumBuff = ByteBuffer.allocate(4);
        checkSumBuff.putInt((int)checkSum.getValue());
        // write bytes to array
        byte[] bytes = checkSumBuff.array();
        return bytes;
    }

	private void showInit() {
		// show info about server
		System.out.println("server ip: " + IPAddress.toString() + ":" + String.valueOf(port));
	}

	private void showProgress() {
		// count how much was send pro second
		timeSec += timeDiff;
		fileLenProSec += fileToSend;
		// look if second is gone or last packet sent
		boolean secondGone = false;
		if (timeSec >= 1000 || (fileLengthSent == fileLength)) {
			secondGone = true;
			timeSec %= 1000;
		}
		// not display if failed or second not gone
		if (receiveFailedTries || !secondGone) return;
		// show receive progress
		System.out.print("sent: [");
		int prog = (int)((double)fileLengthSent / (double)fileLength * scaleLength);
		for(int i = 0; i < prog; i++)
			System.out.print("=");
		for(int i = prog; i < (int)scaleLength; i++)
			System.out.print(" ");
		System.out.print("] " + fileLength + " " + fileLenProSec + "B/s");
		if (!DEBUG) System.out.print("       \r");
		else System.out.println();
		// reset counter how much was send pro second
		fileLenProSec = 0;
	}

	private void showResult() {
		System.out.println();


		// get time for full sending time
		timeSecondFull = System.currentTimeMillis();
		timeDiffFull = timeSecondFull - timeFirstFull;
		timeDiffFull /= 1000; //ms to s
		if(timeDiffFull <= 0) timeDiffFull = 1;

		long speed = fileLengthSent/timeDiffFull;
		
		System.out.println(fileLengthSent + "B sent " + speed + "B/s in average");

		// situative logging
		if (receiveFailedTries) {
			System.out.println("max tries riched");
			System.out.println("sent:" + fileLengthSent + "/" + fileLength);
			if (fileLengthSent != fileLength)
				System.out.println("sending failed");
		}
		else {
			System.out.println("sending finished successfully");
		}

	}

}
