package model.ESP;
import  java.io.*;
import  java.net.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;

public class ESP_communicator {
    private String IP = null;
    private static ESP_communicator ESP_communicator_instance = null;

    private ESP_communicator() {
        IP = new String();
        IP = "http://192.168.1.72";//Static ip (same on esp8266)

    }

    public static ESP_communicator getESP_communicator() {
        if (ESP_communicator_instance == null) {
            ESP_communicator_instance = new ESP_communicator();
            return ESP_communicator_instance;
        } else {
            return ESP_communicator_instance;
        }
    }

    public boolean forward() {

        try {


            URL url = new URL(IP + "/forward");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);
            int responseCode = con.getResponseCode();

            if(responseCode==200)return true;
            else return  false;
        } catch (Exception e) {
            return false;
        }
    }

    public boolean backward() {


        try {

            URL url = new URL(IP + "/backward");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);

            int responseCode = con.getResponseCode();
            if(responseCode==200)return true;
            else return  false;
        } catch (Exception e) {
            return false;
        }
    }

    public boolean right() {


        try {
            URL url = new URL(IP+"/right");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);

            int responseCode = con.getResponseCode();
            if(responseCode==200)return true;
            else return  false;

        } catch (Exception e) {
            return false;
        }
    }
    public boolean stop() {


        try {
            URL url = new URL(IP+"/stop");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);
            int responseCode = con.getResponseCode();

            if(responseCode==200)return true;
            else return  false;

        } catch (Exception e) {
            return false;
        }
    }


    public boolean left() {

        try {
            URL url = new URL(IP + "/left");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);
            int responseCode = con.getResponseCode();
            if(responseCode==200)return true;
            else return  false;
        } catch (Exception e) {
            return false;
        }
    }
    public boolean setLatitude(String rawData) {

        try {
            URL url = new URL(IP + "/newLatitude");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);

            con.setDoOutput(true);
            OutputStream os = con.getOutputStream();
            os.write(rawData.getBytes());

            if(con.getResponseCode()==200)return true;
            return false;
        } catch (Exception e) {
            return false;
        }
    }
    public boolean setLongitude(String rawData) {


        try {
            URL url = new URL(IP + "/newLongitude");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);

           // con.setDoOutput(true);
            OutputStream os = con.getOutputStream();
            os.write(rawData.getBytes());

            if(con.getResponseCode()==200)return true;
            return false;
        } catch (Exception e) {
            return false;
        }
    }
    public boolean setAngle(String rawData) {



        try {


            URL url = new URL(IP + "/newAngle");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(500);//500ms max latency
            con.setReadTimeout(500);
            if(con.getResponseCode()==200)return true;
            return false;
        } catch (Exception e) {
            return false;
        }
    }

    public String getInfo() {

        try {
            URL url = new URL(IP + "/info");
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(2000);//500ms max latency
            con.setReadTimeout(2000);
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(con.getInputStream()));
            String respond=in.readLine();
            in.close();
           return respond;
        } catch (Exception e) {
            return null;
        }
    }


    public boolean checkConnection() {


        try {
            URL url = new URL(IP );
            HttpURLConnection con = (HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            con.setConnectTimeout(4000);//4s max latency
            con.setReadTimeout(4000);

            int responseCode = con.getResponseCode();
            if(responseCode==200)return true;
            else return  false;
        } catch (Exception e) {
            return false;
        }

    }


}
