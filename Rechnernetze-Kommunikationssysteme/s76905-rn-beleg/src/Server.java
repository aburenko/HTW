import java.io.*;
import java.net.*;
import java.util.Arrays;
import java.util.Random;
import java.nio.ByteBuffer;
import java.util.zip.*;

import udp.UDPtransfer;

class Server extends UDPtransfer {
	public Server (String args[]) {
		parseArgs(args);
		init();
		// receive Start packet and send acknowledge
		initStart();
		// begin receiving
		while(!sessionFinished)
		{
			this.receiveExec();

			if (receiveFailedTries == true)
				break;

			calcRTO();
			simulateDelay();

			generateAck();

			send();

			showProgress();
		}
		showResult();
	}

    public static void main(String args[]) {
        new Server(args);
    }

    // initialize variables
    private void init() {
		packetNumber = 0x01;
        // create a socket
		try {
        	thisSocket = new DatagramSocket(port);
		} catch (SocketException e) {
			System.err.println("Can\'t create new DatagramSocket \n");
			e.printStackTrace();
			System.exit(1);
		}
		// arrange receive byte array and send DatagramPacket
        receiveData = new byte[MTU];
        // Create random number generator for use in simulating
        // packet loss and network delay.
        random = new Random();
    }

    // receive new packet and initialize it's values
    private void initStart() {
        System.out.println("waiting for start packet ...");
        // wait to receive a correct Start packet
		boolean startRec = false;
        while(!startRec) {
			try {
				startRec = receive();
			} catch (Exception e) {}
		}
		// get data of sender
        IPAddress = receivePacket.getAddress();
        portClient = receivePacket.getPort();
        // show info about client
        System.out.println("client ip: " + IPAddress.toString() + ":" + String.valueOf(portClient));
        // prepareFile for writing
        prepareFile();
        System.out.println("File: " + fileName);
        // generate Acknowledge of start packet
        generateAck();
        // send acknowledge
        send();
		// set timeout in milliseconds for nexts
		setSocketTimeout(thisSocket, eRTT);
    }

	// decode args
	private void parseArgs(String[] args) {
		// check args
		// 1 - portnumber
		// 2 - packet loss
		// 3 - delay in ms
		// Check how many arguments were passed in
		if(args.length != 3)
		{
			System.out.println("usage: java Client <port> <loss rate> <delay>");
			System.exit(1);
		}
		// get port
		port = Integer.parseInt(args[0]);
		if (port<=0 || port>=65535)
			System.exit(1);
		// get packet loss
		LOSS_RATE = Double.parseDouble(args[1]);
		if (LOSS_RATE<0 || LOSS_RATE>=1)
			System.exit(1);
		// get delay
		AVERAGE_DELAY = Integer.parseInt(args[2]);
	}

    // receive new data packet
	@Override
    public boolean receive() throws SocketTimeoutException {
        receiveData();
        // immulate loss
        if(random.nextDouble() < LOSS_RATE) {
            if(DEBUG) System.out.println("NOT received");
            return false;
        }
		// get Start or Data packet
        if (fileLength != 0) return decodeDataPacket(sequence);
		else return decodeStartPacket(sequence);
    }

	// receive new packet and initialize it's values
    private void receiveData() throws SocketTimeoutException {
        // get time on start
        timeFirst = System.currentTimeMillis();
        // receive a packet
        receivePacket =  new DatagramPacket(receiveData, receiveData.length);
		try {
    		thisSocket.receive(receivePacket);
		} catch (SocketTimeoutException e) {
			throw e;
		} catch (Exception e) {
			e.printStackTrace();
		}
		// get byte[] from Packet
        sequence = Arrays.copyOfRange(receiveData, 0, receivePacket.getLength());
    }

    private void prepareFile() {
        File f = new File(fileName);
        while(f.exists()) {
            int lastDot = fileName.lastIndexOf('.');
            fileName = fileName.substring(0,lastDot) + "1" + fileName.substring(lastDot);
            f = new File(fileName);
        }
		try {
        	fileOut = new FileOutputStream(f);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

    private void generateAck() {
        // combine Acknowledge packet
        ByteArrayOutputStream sendDataBuffer = new ByteArrayOutputStream();
		try {
	            // sessionNumber
	        sendDataBuffer.write(sessionNumber);
	            // packetNumber
	        sendDataBuffer.write((byte)packetNumber);
		if(DEBUG) System.out.println("ACK NEW " + packetNumber);
		} catch (IOException e) {
			e.printStackTrace();
		}
        // convert to byte array
        byte[] sendData = sendDataBuffer.toByteArray();
        // send answer to sender
        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, portClient);
    }

    // decodes a Start Packet and returns status
    private boolean decodeDataPacket(byte[] sequence) {
        // get sessionNumber
        byte[] sessionNumberRec = Arrays.copyOfRange(sequence, 0, S_SESSION_NUMBER);
        // get packet Number
        byte packetNumberRec = sequence[2];
	if(DEBUG) System.out.println("GET " + packetNumberRec);
        boolean b_pnRepeat = (packetNumberRec == packetNumber);
        if (b_pnRepeat) {
            if(DEBUG) System.err.println("Reapeat");
            send();
            return false;
        }
        // check received session and packet Number
        boolean b_snc = Arrays.equals(sessionNumber, sessionNumberRec);
        boolean b_pnc = (packetNumberRec == 0x00 || packetNumberRec == 0x01);
        if (!(b_snc && b_pnc)) {
            if(DEBUG) System.err.println("Data Packet DECODING ERROR");
            return false;
        }
        // check if last packet
        int offset = S_SESSION_NUMBER + S_PACKET_NUMBER;
        // check for CRC in packet
        // sequence.l - "session- and packetNumber and CRC" compared with "need to receive"
        if( (sequence.length - S_SESSION_NUMBER - S_PACKET_NUMBER - S_CRC32)
            >= (fileLength - fileLengthReceived) )
            offset += S_CRC32;
        // write gotten data into file
		try {
			fileOut.write(sequence, 3, sequence.length - offset);
		} catch (IOException e) {
			e.printStackTrace();
		}
		fileLengthReceived += sequence.length - offset;
        // check CRC correctness
        if(offset == (S_SESSION_NUMBER + S_PACKET_NUMBER + S_CRC32)) {
            byte[] fileCRC =
                Arrays.copyOfRange(sequence, sequence.length - S_CRC32, sequence.length);
            if(!compareFileCRCwith(fileCRC)) {
                if(DEBUG) System.err.println("Data Packet DECODING ERROR");
                return false;
            } else {
                sessionFinished = true;
            }
        }
        packetNumber = packetNumberRec;
        return true;
    }

	@Override
	public void send() {
		if(random.nextDouble() < LOSS_RATE) {
			if(DEBUG) System.out.println("NOT SENT");
				return;
		}
		try {
			thisSocket.send(sendPacket);
		} catch(IOException e) {
			e.printStackTrace();
		}
	}

    // decodes a Start Packet and returns status
    private boolean decodeStartPacket(byte[] sequence) {
        // check CRC32
        if (!checkCRC(sequence)) {
            if(DEBUG) System.err.println("bad CRC32 of start packet");
            return false;
        }
        // get sessionNumber
        sessionNumber = Arrays.copyOfRange(sequence, 0, S_SESSION_NUMBER);
        long sessionNumberLong = byteToLong(sessionNumber, 0, S_SESSION_NUMBER);
        // get packet Number
        packetNumber = sequence[2];
        boolean b_packetNumber = (packetNumber == 0x00 || packetNumber == 0x01);
        // get "Start"
        String startString = new String(sequence, 3, 5);
        boolean b_start = (startString.equals("Start"));
        // get file length
        fileLength = byteToLong(sequence, 8, 8);
        boolean b_fLen = (fileLength > 1);
        // get name length of file
        int fileNameLength = (int)byteToLong(sequence, 16, 2);
        boolean b_fNLen = (fileNameLength > 1);
        // get file name itself
		try {
        	fileName = new String(sequence, 18, fileNameLength, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		boolean b_fName = (fileName.length() > 1);
        // get compare result
        boolean b_res = (b_packetNumber && b_start && b_start && b_fLen && b_fNLen && b_fName);
        if(DEBUG) {
            if(!b_res) {
                System.err.println("Start Packet DECODING ERROR");
				fileLength = 0;
            } else { // do loging
                System.out.println("sNr: " + sessionNumberLong
                    + "  pNr: " + packetNumber
                    + "  str: " + startString
                    + "\nfileLength: " + fileLength
                    + "  fileNameLength: " + fileNameLength
                    + "\nfileName: " + fileName
                );
            }
        }

        return b_res;
    }

    // checks if CRC32 correct
    private boolean compareFileCRCwith(byte[] receiveCRC) {
        // get checksum of file
        Checksum checksum = new CRC32();
        byte[] tempBuf = new byte[128];
		try {
        	FileInputStream fis = new FileInputStream(fileName);
        	CheckedInputStream cis = new CheckedInputStream(fis, checksum);
        	while (cis.read(tempBuf) >= 0) {}
		} catch (Exception e) {
			e.printStackTrace();
		}
		// convert file CRC to long
        long fileChecksumLong = checksum.getValue();
        // convert received CRC to long
        long receiveCRCLong = byteToLong(receiveCRC, 0, receiveCRC.length);
        return (fileChecksumLong == receiveCRCLong);
    }

	// checks if CRC32 correct
    private boolean checkCRC (byte[] subject) {
        // take out the CRC that was received and convert it to long
        long receiveCRCLong =
            byteToLong(subject, (subject.length - S_CRC32), S_CRC32);
        // calculate new CRC over the package for compare
        CRC32 newCheck = new CRC32();
        newCheck.update(subject, 0, subject.length - S_CRC32);
        long newCRCLong = newCheck.getValue();
        boolean res = (receiveCRCLong == newCRCLong);
        // loging
        if (!res && DEBUG)
            System.err.println("CRC32 is NOT correct");
        // return compare value
        return res;
    }

    // returns long from byte array
    private long byteToLong(byte[] b, int offset, int size) {
        long res = 0;
        for (int i = 0; i < size; i++)
           res = (res << 8) + (b[offset + i] & 0xff);
        return res;
    }

    private void showProgress() {
        if (receiveFailedTries) return;
        // show receive progress
        System.out.print("received: [");
        int prog = (int)((double)fileLengthReceived / (double)fileLength * scaleLength);
        for(int i = 0; i < prog; i++)
            System.out.print("=");
        for(int i = prog; i < (int)scaleLength; i++)
            System.out.print(" ");
        System.out.print("]");
        // show time for Round Trip Time
		System.out.print(" RTT: " + timeDiff + "ms");
		if (!DEBUG) System.out.print("        \r");
    	else System.out.println();
    }

    private void showResult() {
        System.out.println();
        if (receiveFailedTries) System.out.println("failed, max tries riched");
        else System.out.println("success");
    }
}
