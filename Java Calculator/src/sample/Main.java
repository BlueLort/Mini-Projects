/*
                Developed By : Omar Nasr (lort)
                email:emaranasr@gmail.coms

 */
package sample;

import com.sun.source.doctree.AttributeTree;
import javafx.application.Application;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.StringProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.VPos;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.input.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.awt.*;
import java.net.URL;
import java.util.ResourceBundle;


public class Main extends Application  {
    private BooleanProperty ControlDOWN = new SimpleBooleanProperty();
    public final int HEIGHT=500;
    public final int WIDTH=385;
    private static Scene scene;
    private Controller controller;
    private FXMLLoader loader;
    private Parent root;

    @Override
    public void start(Stage primaryStage) throws Exception{


        // intialization
        controller = new Controller();
        loader = new FXMLLoader(getClass().getResource("FXML/design.fxml"));
       root =loader.load();
        FXMLController FXMLcontroller = (FXMLController)loader.getController();

        controller.setfxController(FXMLcontroller);
       scene =new Scene(root,WIDTH,HEIGHT);
        primaryStage.setScene(scene);
        scene.setFill(Color.WHITE);//FRAME
        primaryStage.initStyle(StageStyle.DECORATED);//MINIMIZE AND ALL
        primaryStage.setOpacity(0.925);
        /* SETTING BOTTOM LABEL LAYOUT */
        primaryStage.setTitle("Calculator");


        primaryStage.setResizable(false);
        primaryStage.show();
        //////////////////////////KEYBOARD INPUT
        scene.addEventHandler(KeyEvent.ANY,e->{
            if (e.getCode() == KeyCode.ENTER||e.getCode() == KeyCode.SPACE) {
                FXMLcontroller._equal.fire();
                e.consume(); // TO DEACTIVATE CLICKING BUTTONS USING SPACE OR ENTER but it doesnt work xD
            }
        });
        scene.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.CONTROL) {
                ControlDOWN.set(true);
            }

        });
        scene.setOnKeyTyped(e-> {
            if(e.getCharacter().equals("%")){
                FXMLcontroller._mod.fire();
            }
            if(e.getCharacter().equals("0")){
                FXMLcontroller.zero.fire();
            }
            if(e.getCharacter().equals("1")){
                FXMLcontroller.one.fire();
            }
            if(e.getCharacter().equals("2")){
                FXMLcontroller.two.fire();
            }
            if(e.getCharacter().equals("3")){
                FXMLcontroller.three.fire();
            }
            if(e.getCharacter().equals("4")){
                FXMLcontroller.four.fire();
            }
            if(e.getCharacter().equals("5")){
                FXMLcontroller.five.fire();
            }
            if(e.getCharacter().equals("6")){
                FXMLcontroller.six.fire();
            }
            if(e.getCharacter().equals("7")){
                FXMLcontroller.seven.fire();
            }
            if(e.getCharacter().equals("8")){
                FXMLcontroller.eight.fire();
            }
            if(e.getCharacter().equals("9")){
                FXMLcontroller.nine.fire();
            }
            if(e.getCharacter().equals(".")){
                FXMLcontroller._dot.fire();
            }
            if(e.getCharacter().equals("(")){
                FXMLcontroller._open_brackets.fire();
            }
            if(e.getCharacter().equals(")")) {
                FXMLcontroller._closing_brackets.fire();
            }
            if(e.getCharacter().equals("*")) {
                FXMLcontroller._multiply.fire();
            }
            if(e.getCharacter().equals("/")) {
                FXMLcontroller._divide.fire();
            }
            if(e.getCharacter().equals("+")) {
                FXMLcontroller._sum.fire();
            }
            if(e.getCharacter().equals("-")) {
                FXMLcontroller._substract.fire();
            }
            if(e.getCharacter().equals("^")) {
                FXMLcontroller._power.fire();
            }
            if(e.getCharacter().equals("!")) {
                FXMLcontroller._fact.fire();
            }
            if(e.getCharacter().equals("s")) {
                FXMLcontroller._sin.fire();
            }
            if(e.getCharacter().equals("c")&&e.getCode()!=KeyCode.CONTROL) {
                FXMLcontroller._cos.fire();
            }
            if(e.getCharacter().equals("t")) {
                FXMLcontroller._tan.fire();
            }
            if(e.getCharacter().equals("P")) {
                FXMLcontroller._permutation.fire();
            }
            if(e.getCharacter().equals("C")&&e.getCode()!=KeyCode.CONTROL) {
                FXMLcontroller._combination.fire();
            }
            if(e.getCharacter().equals("=")) {
                FXMLcontroller._equal.fire();
            }







        });

        scene.addEventHandler(KeyEvent.KEY_PRESSED, e -> {

                if (e.getCode() == KeyCode.BACK_SPACE) {
                    FXMLcontroller._backspace.fire();
                }

                if (e.getCode() == KeyCode.ESCAPE) {
                    FXMLcontroller._ce.fire();
                }

            if ((e.getCode()==KeyCode.C)){

                if(ControlDOWN.get()) {
                    final Clipboard clipboard = Clipboard.getSystemClipboard();
                    final ClipboardContent content = new ClipboardContent();
                    content.putString(FXMLcontroller._result.getText());
                    clipboard.setContent(content);
                    FXMLcontroller._Console.setTextFill(Color.GREEN);
                    FXMLcontroller._Console.setText("  > Copied to Clipboard");
                    FXMLcontroller._Console.setTextFill(Color.RED);
                    ControlDOWN.set(false);
                }



            }


        });
        scene.addEventHandler(KeyEvent.KEY_RELEASED, e -> {

            if (e.getCode() == KeyCode.BACK_SPACE) {
                FXMLcontroller._backspace.fire();
            }

            if (e.getCode() == KeyCode.ESCAPE) {
                FXMLcontroller._ce.fire();

            }
            if (e.getCode() == KeyCode.UP) {
                FXMLcontroller._prev.fire();
            }
            if (e.getCode() == KeyCode.DOWN) {
                FXMLcontroller._next.fire();
            }



        });


    }





    public static void main(String[] args) {

        launch(args);
    }
}
