package udp;

import java.io.*;
import java.net.*;
import java.lang.Runtime;
import java.util.Random;

public abstract class UDPtransfer {
	public static final boolean DEBUG = false;
    // constants
    public static final int MTU = 1500;
    public static final int MAX_TRIES = 10;
		// simulating
	public static int AVERAGE_DELAY = 20;  // milliseconds
	public static double LOSS_RATE = 0.2;
		// referred to protokol
	public static final int S_SESSION_NUMBER = 2;
	public static final int S_PACKET_NUMBER = 1;
	public static final int S_CRC32 = 4;
    // socket variables
    public static InetAddress IPAddress;
    public static int port;
    // current sessionData
    public static boolean receiveFailedTries = false;
    public static boolean sessionFinished = false;
    public static byte[] sendData, receiveData, sequence;
    public static int portClient;
    public static DatagramSocket thisSocket;
	// packet variables
    public static DatagramPacket sendPacket, receivePacket;
	public static byte packetNumber;
    public static byte[] sessionNumber;
	// file variables
    public static String fileName;
    public static FileOutputStream fileOut;
    public static FileInputStream fileIn;
    public static long fileLength = 0;
    public static int fileLengthSent = 0;
    public static long fileLengthReceived = 0;
    public static int fileToSend = 0;
	// time variables
	public static long timeFirst, timeSecond, timeDiff;
	public static Random random = new Random();
	// for time of full runtime
    public static long timeFirstFull, timeSecondFull, timeDiffFull;
    public static long timeSec = 0;
    public static int fileLenProSec = 0;
	// ranging variables for WAIT STOP protokol
	public static int eRTT = 1000; // [ms] estimated Round Trip Time
	public static final double ALPHA = 0.125;
	public static final int RTO_MIN = 30; // minimal Roundtrip time
	public static int DevRTT = 1500;
	// user interface vars
	public static double scaleLength = 10.0; // scale displayed on screen

	public void receiveExec() {
	    // get time on start of RTT
	    timeFirst = System.currentTimeMillis();

		boolean ack = false;
	    int numTries = 0;
		while(!ack && numTries < MAX_TRIES) {
			try {
				// try to receive
				ack = receive();
			} catch (SocketTimeoutException ste) {
				// resend
				send();
			}
	        numTries++;
		}
	    if (numTries == MAX_TRIES) receiveFailedTries = true;
	}

	public boolean receive() throws SocketTimeoutException {
		return true;
	}

	public void send() {
		return;
	}

	public static void setSocketTimeout(DatagramSocket ds, int time) {
		try {
			ds.setSoTimeout(time);
		} catch (SocketException e) {
			e.printStackTrace();
		}
	}

	public static void simulateDelay() {
		// Simulate network delay.
		try {
			Thread.sleep((int) (new Random().nextDouble() * 2 * AVERAGE_DELAY));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void calcRTO() {
		// show time for Round Trip Time
		timeSecond = System.currentTimeMillis();
		timeDiff = timeSecond - timeFirst; // timeDiff = sRTT
		// estimate RTT
		eRTT = (int)((1-ALPHA)*eRTT + ALPHA*timeDiff);
		// get how sRTT and eRTT differences
		DevRTT = (int)((1-ALPHA)*DevRTT + ALPHA*(timeDiff-eRTT));
		// get RTO (Retransmission Timeout)
		int RTO = (int)(eRTT + 4*DevRTT);

		if(RTO < RTO_MIN) RTO = RTO_MIN;
		if (DEBUG) System.out.println(RTO);
		// set new Timeout
		setSocketTimeout(thisSocket, RTO);
	}
	// creates random Session Number (2Byte) and returns it
	public static byte[] generateSessionNumber() {
		byte[] res = new byte[S_SESSION_NUMBER];
		random.nextBytes(res);
		return res;
	}
}
