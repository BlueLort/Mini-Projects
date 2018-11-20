package model.JSerialComm;
import com.fazecast.jSerialComm.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import javafx.application.Platform;

import java.io.PrintStream;
import java.util.Enumeration;
import controller.Controller;
import java.io.InputStream;

public class JSerial_Communicator  /*implements SerialPortPacketListener*/ {
    //    @Override
//    public int getListeningEvents() { return SerialPort.LISTENING_EVENT_DATA_AVAILABLE; }
//
//    @Override
//    public int getPacketSize() { return 100; }
//
//    @Override
//    public void serialEvent(SerialPortEvent event)
//    {
//        Platform.runLater(//Because of FX THREAD
//                        () -> {
//
//                            InputStream in = selectedPort.getInputStream();
//                            try {
//
//                                byte[] newData = event.getReceivedData();
//                                int k = newData.length;
//                                char infoChars[] = new char[k];
//                                for (int i = 0; i < k; i++) {
//                                    infoChars[i] = (char) newData[i];
//                                }
//
//                                infoString = new String(infoChars);
//
//
//                                Controller.getInstance().refreshAction();
//                                in.close();
//                            } catch (Exception e) {
//                                System.err.println(e.toString());
//                                Controller.getInstance().get_connect().fire();
//                            }
//
//                        });
//
//    }
    //Singleton
    private JSerial_Communicator(){

    }
    private static JSerial_Communicator serialInstance=null;

    public synchronized static JSerial_Communicator getSerialInstance() {
        if(serialInstance==null){
            serialInstance=new JSerial_Communicator();
        }
        return serialInstance;
    }

    /** Milliseconds to block while waiting for port open */
    private static final int TIME_OUT = 5000;
    /** Default bits per second for COM port. */
    private int BAUD_RATE = 115200;
    private SerialPort selectedPort;
    private String portSysName;
    public synchronized boolean initialize() {
        SerialPort comPort[] = SerialPort.getCommPorts();
        int len=comPort.length;
        for(int i=0;i<len;i++){
            if(portSysName==null){
                Controller.getInstance().get_connectivity().setText("SELECT A PORT FIRST");
                return false;

            }
            if(portSysName.equals(comPort[i].getSystemPortName())){
                selectedPort=comPort[i];
                break;
            }

        }

        selectedPort.setBaudRate(BAUD_RATE);

        selectedPort.openPort();
        selectedPort.setComPortTimeouts(SerialPort.TIMEOUT_NONBLOCKING, 500, 0);

        selectedPort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() { return SerialPort.LISTENING_EVENT_DATA_AVAILABLE; }

            @Override
            public void serialEvent(SerialPortEvent event) {
                Platform.runLater(//Because of FX THREAD
                        () -> {

                            if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE)
                                return;
                            InputStream in = selectedPort.getInputStream();
                            try {
                                byte infoChars[]=new byte[2048];
                                selectedPort.readBytes(infoChars, infoChars.length);
                                infoString = new String(infoChars);


                                Controller.getInstance().refreshAction();
                                in.close();
                            } catch (Exception e) {
                                System.err.println(e.toString());
                                Controller.getInstance().get_connect().fire();
                            }

                        });

            }
        });

        Controller.getInstance().get_connectivity().setText("CONNECTED!");
        return true;
    }

    /**
     * This should be called when you stop using the port.
     * This will prevent port locking on platforms like Linux.
     */
    public  void close() {
        if (selectedPort != null) {
            selectedPort.removeDataListener();
            selectedPort.closePort();

        }
    }

    /**
     * Handle an event on the serial port. Read the data and print it.
     */
    private String infoString;


    public  String getInfo(){

        return infoString;
    }
    public void setSelectedPort(SerialPort selectedPort) {
        this.selectedPort = selectedPort;
    }

    public void setBaudRate(int BAUD_RATE) {
        this.BAUD_RATE = BAUD_RATE;
    }

    public  void refreshPorts(){
        SerialPort comPorts[] = SerialPort.getCommPorts();
        Controller.getInstance().get_ports().getItems().clear();
        int len=comPorts.length;
        for(int i=0;i<len;i++){

            Controller.getInstance().get_ports().getItems().add(comPorts[i].getSystemPortName());
        }
    }

    public void setPortSysName(String portSysName) {
        this.portSysName = portSysName;
    }

    public SerialPort getSelectedPort() {
        return selectedPort;
    }
}
