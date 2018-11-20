package sample;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;

import java.net.URL;
import java.util.ResourceBundle;

public class FXMLController
        implements Initializable {
    private Controller controller;

    /* 0 to 9 buttons */
    @FXML
    protected Button zero;
    @FXML
    protected Button one;
    @FXML
    protected Button two;
    @FXML
    protected Button three;
    @FXML
    protected Button four;
    @FXML
    protected Button five;
    @FXML
    protected Button six;
    @FXML
    protected Button seven;
    @FXML
    protected Button eight;
    @FXML
    protected Button nine;
 ////////////////////////////////
 /* MATH OPERATIONS buttons*/
    @FXML
    protected Button _multiply;
    @FXML
    protected Button _substract;
    @FXML
    protected Button _divide;
    @FXML
    protected Button _sum;
    @FXML
    protected Button _power;
    @FXML
    protected Button _mod;
    @FXML
    protected Button _equal;
    @FXML
    protected Button _fact;
        /////
    /* Utility Buttons */
    @FXML
    protected Button _ans;
    @FXML
    protected Button _prev;
    @FXML
    protected Button _next;
    @FXML
    protected Button _ce;
    @FXML
    protected Button _del;
    @FXML
    protected Button _backspace;
    //////////////////////
    /* Functionality Buttons */
    @FXML
    protected Button _open_brackets;
    @FXML
    protected Button _dot;
    @FXML
   protected Button _permutation;
    @FXML
    protected Button _combination;
    @FXML
    protected Button _sin;
    @FXML
    protected Button _cos;
    @FXML
    protected Button _tan;
    @FXML
    protected Button  _closing_brackets;
    /////////////////
    @FXML
    protected Label _editable;
    @FXML
    protected Label _result;
    @FXML
    protected Label _Console;
    public  void EnableButtons(){
        one.setDisable(false);
        two.setDisable(false);
        three.setDisable(false);
        four.setDisable(false);
        five.setDisable(false);
        six.setDisable(false);
        seven.setDisable(false);
        eight.setDisable(false);
        nine.setDisable(false);
        _equal.setDisable(false);
        _ans.setDisable(false);
        _mod.setDisable(false);
        _multiply.setDisable(false);
        _dot.setDisable(false);
        zero.setDisable(false);
        _open_brackets.setDisable(false);
        _closing_brackets.setDisable(false);
        _sin.setDisable(false);
        _cos.setDisable(false);
        _tan.setDisable(false);
        _power.setDisable(false);
        _fact.setDisable(false);
        _sum.setDisable(false);
        _substract.setDisable(false);
        _permutation.setDisable(false);
        _combination.setDisable(false);
        _ce.setDisable(false);
        _del.setDisable(false);
        _divide.setDisable(false);
        _backspace.setDisable(false);
        _Console.setTextFill(Color.RED);
        _Console.setText("");
    }
    public  void DisableButtons(){
        one.setDisable(true);
       two.setDisable(true);
        three.setDisable(true);
        four.setDisable(true);
        five.setDisable(true);
        six.setDisable(true);
        seven.setDisable(true);
        eight.setDisable(true);
        nine.setDisable(true);
        _equal.setDisable(true);
        _ans.setDisable(true);
        _mod.setDisable(true);
        _multiply.setDisable(true);
        _dot.setDisable(true);
        zero.setDisable(true);
        _open_brackets.setDisable(true);
        _closing_brackets.setDisable(true);
        _sin.setDisable(true);
        _cos.setDisable(true);
       _tan.setDisable(true);
        _power.setDisable(true);
        _fact.setDisable(true);
        _sum.setDisable(true);
        _divide.setDisable(true);
        _substract.setDisable(true);
        _permutation.setDisable(true);
        _combination.setDisable(true);
        _ce.setDisable(true);
        _del.setDisable(true);
        _backspace.setDisable(true);
        _Console.setTextFill(Color.GREEN);
        _Console.setText("  > Click CTRL+C to Copy Ans");

    }
    @Override
   public void initialize(URL url, ResourceBundle rb) {
        controller=new Controller();
        _Console.setTextFill(Color.RED);
        /*NUMBER BUTTONS*/


        zero.setOnAction(e -> {
            _editable.setText(_editable.getText() + "0");
        });

        one.setOnAction(e -> {
            _editable.setText(_editable.getText() + "1");
        });

        two.setOnAction(e -> {
            _editable.setText(_editable.getText() + "2");
        });

        three.setOnAction(e -> {
            _editable.setText(_editable.getText() + "3");
        });

        four.setOnAction(e -> {
            _editable.setText(_editable.getText() + "4");
        });

        five.setOnAction(e -> {
            _editable.setText(_editable.getText() + "5");
        });

        six.setOnAction(e -> {
            _editable.setText(_editable.getText() + "6");
        });

        seven.setOnAction(e -> {
            _editable.setText(_editable.getText() + "7");
        });

        eight.setOnAction(e -> {
            _editable.setText(_editable.getText() + "8");
        });

        nine.setOnAction(e -> {
            _editable.setText(_editable.getText() + "9");
        });


        /*Math Operations */


        _sum.setOnAction(e -> {
            _editable.setText(_editable.getText() + "+");
        });
        _substract.setOnAction(e -> {
            _editable.setText(_editable.getText() + "-");
        });
        _divide.setOnAction(e -> {
            _editable.setText(_editable.getText() + "/");
        });
        _multiply.setOnAction(e -> {
            _editable.setText(_editable.getText() + "*");
        });
        _power.setOnAction(e -> {
            _editable.setText(_editable.getText() + "^");
        });
        _mod.setOnAction(e -> {
            _editable.setText(_editable.getText() + "%");
        });
        _fact.setOnAction(e -> {
            _editable.setText(_editable.getText() + "!");
        });
        _equal.setOnAction(e -> {
           controller.input(_editable.getText());
            _result.setText(controller.getResult());
        });
        //////////////////////////
        /*Utility Buttons */
        _backspace.setOnAction(e -> {
            String x;
            String y;
            y=_editable.getText();
            int z=y.length();
            if(z==0)return;
            if(z>3){
                if(y.charAt(z-2)=='n'||y.charAt(z-2)=='s') {
                    x = y.substring(0, y.length() - 4);
                    _editable.setText(x);
                    return;
                }
            }

            x=y.substring(0,y.length()-1);
            _editable.setText(x);

        });
        _ce.setOnAction(e -> {
            _editable.setText("");
        });
        _del.setOnAction(e -> {
            controller.reset();
        });
        _prev.setOnAction(e -> {
            controller.prev();
        });
        _next.setOnAction(e -> {
            controller.next();
        });

        _ans.setOnAction(e -> {
            _editable.setText(_editable.getText()+controller.current());
        });
        ////////////////////////////////
        /* FUNCTIONALITY */
        _dot.setOnAction(e -> {
            _editable.setText(_editable.getText() + ".");
        });
        _open_brackets.setOnAction(e -> {
            _editable.setText(_editable.getText() + "(");
        });
        /* TODO implement all utility buttons */
        _sin.setOnAction(e -> {
            _editable.setText(_editable.getText() + "sin(");
        });
        _cos.setOnAction(e -> {
            _editable.setText(_editable.getText() + "cos(");
        });
        _tan.setOnAction(e -> {
            _editable.setText(_editable.getText() + "tan(");
        });

        _closing_brackets.setOnAction(e -> {
            _editable.setText(_editable.getText() + ")");
        });
        _permutation.setOnAction(e -> {
            _editable.setText(_editable.getText() + "P");
        });

        _combination.setOnAction(e -> {
            _editable.setText(_editable.getText() + "C");
        });



        _equal.setDefaultButton(true);


    };

}