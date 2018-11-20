package controller;

import Utility.OsCheck;
import com.fazecast.jSerialComm.SerialPort;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import model.JSerialComm.JSerial_Communicator;
import model.SerialRXTX.Serial_CommunicatorRXTX;

import java.net.URL;
import java.util.ResourceBundle;

public class Controller  implements Initializable {
    //Singleton
    private static Controller controllerInstance=null;

    public static void setControllerInstance(Controller controllerInstance) {
        Controller.controllerInstance = controllerInstance;
    }

    public synchronized static Controller getInstance() {
        if(controllerInstance==null){
            controllerInstance=new Controller();
        }
        return controllerInstance;
    }


    //MAIN LAYOUT NEEDED FOR LISTENERS
    @FXML
    private AnchorPane _main_layout;
    @FXML
    private ComboBox<String> _ports;
    @FXML
    private ComboBox<Integer> _baud_rate;
    //BUTTONS
    @FXML
    private ToggleButton _connect;
    //LABELS
    @FXML
    private Label _connectivity;
    @FXML
    private Label _debug;
    /*  ROBOT INFO */
    @FXML
    private Label _longitude;
    @FXML
    private Label _latitude;
    @FXML
    private Label _current_angle;
    @FXML
    private Label _distance;
    @FXML
    private Label _target_counter;
    @FXML
    private Label _target_longitude;
    @FXML
    private Label _target_latitude;


    //ESP COMM
  //  private ESP_communicator e=ESP_communicator.getESP_communicator();
    //SERIAL COMM
    private Serial_CommunicatorRXTX serialListener= Serial_CommunicatorRXTX.getSerialInstance();
    private JSerial_Communicator JSerialCom= JSerial_Communicator.getSerialInstance();
    private boolean CONNECTED=false;
    //ACTION FUNCTIONS
    @FXML
    public void portOnAction(){
        serialListener.setSelectedPort(_ports.getSelectionModel().getSelectedItem());
    }
  @FXML
  public void baudRateOnAction(){
        serialListener.setBaudRate(_baud_rate.getSelectionModel().getSelectedItem());
    }
   @FXML
   public void refreshAction(){

        try {
            String[] info = serialListener.getInfo().split(",");
            _connectivity.setText("");
            _debug.setText("Debug Info: ");
            int length=info.length;
            if(length<7)return;
            _longitude.setText("Longitude: " + info[0]);
            _latitude.setText("Latitude: " + info[1]);
            _current_angle.setText("Current Angle: " + info[2]);
            _distance.setText("Distance: " + info[3]);
            _target_longitude.setText("Target Longitude: " + info[4]);
            _target_latitude.setText("Target Latitude: " +info[5]);
            _target_counter.setText("Target Counter: " +info[6]);


            for(int i=7;i<length;i++){
                _debug.setText(_debug.getText()+info[i]);
            }
        }catch (Exception e){


            connectAction();
            _connectivity.setText("ERROR OCCURRED DISCONNECTED ...");
        }
    }
    @FXML
    private void connectAction() {
        _connectivity.setText("");
        if(_ports.getValue()==null){
            _connectivity.setText("SELECT A PORT...");
            return;
        }
        if (!CONNECTED) {
            _connect.setSelected(false);
            if (serialListener.initialize()) {
                CONNECTED = true;
                enableButtons();
                _connect.setText("Disconnect");
                _connect.setSelected(true);
            }

        } else {
            serialListener.close();
            _connect.setSelected(false);
            CONNECTED=false;
            disableButtons();
            _connectivity.setText("DISCONNECTED");
            _connect.setText("Connect");
        }
    }
    //DISABLE AND ENABLE BUTTONS
    private void disableButtons(){

        _ports.setDisable(false);
        _baud_rate.setDisable(false);

    }
    private void enableButtons(){


        _ports.setDisable(true);
        _baud_rate.setDisable(true);

    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        disableButtons();
        SerialPort comPort[] = SerialPort.getCommPorts();
        int len=comPort.length;
        for(int i=0;i<len;i++){
            _ports.getItems().add(comPort[i].getSystemPortName());
        }
        for (int i = 0; i <= 7; i++) {
            _baud_rate.getItems().add(300 * (int) Math.pow(2, i));
        }
        _baud_rate.getItems().addAll(57600, 74880, 115200, 230400, 250000, 500000, 1000000, 2000000);
        _baud_rate.getSelectionModel().select(10);
        _ports.addEventHandler(ComboBox.ON_SHOWING, event -> {
            JSerialCom.refreshPorts();
        });
        Timeline fiveSecondsWonder = new Timeline(new KeyFrame(javafx.util.Duration.seconds(2), new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {
                if(!CONNECTED)return;
                SerialPort comPorts[] = SerialPort.getCommPorts();
                int length=comPorts.length;
                boolean found=false;
                for(int i=0;i<length;i++){
                    if(comPorts[i].getSystemPortName().equals(_ports.getValue())){
                        found=true;
                        break;
                    }
                }
                if(!found) {
                    controller.Controller.getInstance().get_connect().fire();
                }
            }
        }));
        fiveSecondsWonder.setCycleCount(Timeline.INDEFINITE);
        fiveSecondsWonder.play();

    }

    public static Controller getControllerInstance() {
        return controllerInstance;
    }

    public AnchorPane get_main_layout() {
        return _main_layout;
    }

    public ToggleButton get_connect() {
        return _connect;
    }

    public Label get_connectivity() {
        return _connectivity;
    }

    public Label get_debug() {
        return _debug;
    }

    public Label get_longitude() {
        return _longitude;
    }

    public Label get_latitude() {
        return _latitude;
    }

    public Label get_current_angle() {
        return _current_angle;
    }

    public Label get_distance() {
        return _distance;
    }

    public Label get_target_counter() {
        return _target_counter;
    }

    public Label get_target_longitude() {
        return _target_longitude;
    }

    public Label get_target_latitude() {
        return _target_latitude;
    }

    public Serial_CommunicatorRXTX getSerialListener() {
        return serialListener;
    }

    public ComboBox<String> get_ports() {
        return _ports;
    }

    public boolean isCONNECTED() {
        return CONNECTED;
    }
};
