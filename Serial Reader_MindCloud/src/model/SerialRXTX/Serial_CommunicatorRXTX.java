package model.SerialRXTX;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;

import controller.Controller;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import javafx.application.Platform;

import java.io.PrintStream;
import java.util.Enumeration;

public class Serial_CommunicatorRXTX implements SerialPortEventListener {
    //Singleton
    private Serial_CommunicatorRXTX(){

    }
    private static Serial_CommunicatorRXTX serialInstance=null;

    public synchronized static Serial_CommunicatorRXTX getSerialInstance() {
        if(serialInstance==null){
            serialInstance=new Serial_CommunicatorRXTX();
        }
        return serialInstance;
    }

    SerialPort serialPort;
    /** The port we're normally going to use. */
    /**
     * A BufferedReader which will be fed by a InputStreamReader
     * converting the bytes into characters
     * making the displayed results codepage independent
     */
    private static BufferedReader input;
    /** The output stream to the port */
    private static  OutputStream output;
    private static PrintStream printStream;
    /** Milliseconds to block while waiting for port open */
    private static final int TIME_OUT = 5000;
    /** Default bits per second for COM port. */
    private int BAUD_RATE = 115200;
    private String SelectedPort="COM3";
    public synchronized boolean initialize() {
        // the next line is for Raspberry Pi and
        // gets us into the while loop and was suggested here was suggested http://www.raspberrypi.org/phpBB3/viewtopic.php?f=81&t=32186
        //  System.setProperty("gnu.io.rxtx.SerialPorts", "/dev/ttyACM0");

        CommPortIdentifier portId = null;

        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

        //First, Find an instance of serial port as set in PORT_NAMES.
        while (portEnum.hasMoreElements()) {
            CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();

            if (currPortId.getName().equals(SelectedPort)) {
                portId = currPortId;
                Controller.getInstance().get_connectivity().setText("FOUND DEVICE ON" + SelectedPort);
                break;
            }
        }
        if (portId == null) {
            //
            Controller.getInstance().get_connectivity().setText("COULDN'T CONNECT WITH THE DEVICE");

            return false;
        }

        try {
            // open serial port, and use class name for the appName.
            serialPort = (SerialPort) portId.open(this.getClass().getName(),
                    TIME_OUT);
            Thread.sleep(500);
            // set port parameters
            serialPort.setSerialPortParams(BAUD_RATE,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);

            // open the streams
            input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
            output = serialPort.getOutputStream();
            printStream = new PrintStream(output);
            // add event listeners
            serialPort.addEventListener(this);
           // serialPort.notifyOnDataAvailable(true);
            // listen to all the events
            serialPort.notifyOnBreakInterrupt(true);
            serialPort.notifyOnCarrierDetect(true);
            serialPort.notifyOnCTS(true);
            serialPort.notifyOnDataAvailable(true);
            serialPort.notifyOnDSR(true);
            serialPort.notifyOnFramingError(true);
            serialPort.notifyOnOutputEmpty(true);
            serialPort.notifyOnOverrunError(true);
            serialPort.notifyOnParityError(true);
            serialPort.notifyOnRingIndicator(true);

        } catch (Exception e) {
            Controller.getInstance().get_connectivity().setText("ERROR OCCURRED DURING SETTING PROPERTIES");
            return false;
        }
        Controller.getInstance().get_connectivity().setText("CONNECTED!");
        return true;

    }

    /**
     * This should be called when you stop using the port.
     * This will prevent port locking on platforms like Linux.
     */
    public  void close() {
        if (serialPort != null) {
            serialPort.removeEventListener();
            serialPort.close();

        }
    }

    /**
     * Handle an event on the serial port. Read the data and print it.
     */
    private String infoString;
    public  void serialEvent(SerialPortEvent oEvent) {
        Platform.runLater(//Because of FX THREAD
                () -> {
                    if (oEvent.getEventType() != SerialPortEvent.DATA_AVAILABLE)
                        return;
                        try {
                            if(input.ready()) {
                                String inputLine = input.readLine();
                                //SAFETY IF INPUT LINE CRASHED WE DONT COPY IT ON THE INFO STRING
                                infoString = inputLine;
                                Controller.getInstance().refreshAction();
                            }
                        } catch (Exception e) {
                            System.err.println(e.toString());
                            Controller.getInstance().get_connect().fire();
                        }

                } );
        // Ignore all the other eventTypes, but you should consider the other ones.
        }


    public  String getInfo(){

        return infoString;
    }
    public  void sendData(String str) {
       printStream.println(str);
    }

    public void setSelectedPort(String selectedPort) {
        SelectedPort = selectedPort;
    }

    public void setBaudRate(int BAUD_RATE) {
        this.BAUD_RATE = BAUD_RATE;
    }
}
