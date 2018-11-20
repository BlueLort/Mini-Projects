package sample;


import javax.swing.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.function.DoubleToIntFunction;

public class CalculatorSystem implements  Calculator {
    FXMLController _fxController;
    char goodString[] = new char[100];
    int k = 0;
  //  final double EPSILON = 1.0E-16;// for Accuracy not used (used math round instead)//NO NEED MATH ROUND WILL DO THE JOB
    final double inf = 1.2;//AS TRIG FUNCTIONS MUST RETURN value between -1 , 1
    boolean infi = false;
    boolean syntaxError = false;
    boolean noExpression=false;
    boolean mathError=false;
    boolean overFlow=false;

////////////////////////
    int historySize=0;
    private String lastExp=null;
    private String lastAns=null;

    private String currentEXP=null;
   // boolean floatingPoint=false;//NO NEED ANY ERROR WILL BE CAUGHT USING TRY CATCH BLOCKs
    private Stack<String> _prev_answers=new Stack();
    private Stack<String> _next_answers=new Stack();
    private Stack<String> _prev_exp=new Stack();
    private Stack<String> _next_exp=new Stack();
    protected void reset(){
      _prev_answers=new Stack();
            _prev_exp=new Stack();
       _next_answers=new Stack();
            _next_exp=new Stack();
        historySize=0;
        lastExp=null;
        lastAns=null;
        currentEXP=null;
        _fxController._editable.setText("");
        _fxController._result.setText("");
        _fxController._Console.setText("");
    }
    protected void setFXMLController(FXMLController c) {
        this._fxController = c;
    }

    //MATHs FUNCTIONS
    private static long factorial(long x) {
        if (x < 0) return 0;
        long n = 1;
        for (long i = 1; i <= x; i++) {
            n *= i;
        }
        return n;
    }

    private static long nPr(long n, long r) {
        if (r > n) return 0;
        if (r == n) return 1;
        return factorial(n) / factorial(n - r);
    }

    private static long nCr(long n, long r) {
        if (r > n) return 0;
        if (r == n) return 1;
        return factorial(n) / (factorial(n - r) * factorial(r));
    }
    private static long power(long n,long ex){
        if(ex==0)return 1;
     return n*power(n,ex-1);
    }


    private static CalculatorSystem CalculatorSystem = null;


    public static CalculatorSystem getCalculatorSystem() {
        if (CalculatorSystem == null) {
            CalculatorSystem = new CalculatorSystem();
            return CalculatorSystem;
        } else {
            return CalculatorSystem;
        }
    }

    /**
     *@inheritDoc
     * @see CalculatorSystem
     */
    @Override
    public void input(String s) {
        _next_exp=new Stack();//if user modified in the previous answers next answer must be destroyed
        _next_answers=new Stack();
        mathError=false;
        overFlow=false;
        infi = false;
        syntaxError = false;
        noExpression=false;

        _fxController._Console.setText("");
        char in[] = s.toCharArray();
        long x = s.length();
        if(x==0){
            noExpression=true;
            return;
        }
        //MAX CAPICITY 100
        k = 0;
        for (int i = 0; i < x; i++) {

            if ((in[i] - '0' < 10 && in[i] - '0' >= 0) || in[i] == '(' || in[i] == ')' || in[i] == '.' || in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/') {
                goodString[k++] = in[i];

            } else {
                long tmp1;
                long tmp2;
                long tmp3;
                double tmp4;

                String s1;
                String s2;
                String s3;
                //CHECK FOR infinity used by Ans button
                if(in[i]=='I'){
                    infi=true;
                    if(i!=0)k--;
                    return;
                }
                switch (in[i]) {
                    case 's':
                        try {

                            i += 4;
                            tmp2 = i;

                            while ((in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) || in[(int) tmp2 + 1] == '.' || in[(int) tmp2 + 1] == ')') {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                                if (in[(int) tmp2] == ')') break;
                            }
                            if (in[(int) tmp2] != ')') ++tmp2;
                            tmp4 = Math.sin(Double.parseDouble(s.substring(i, (int) tmp2)) * (Math.PI / 180.0));
                            tmp4 = Math.round(tmp4 * Math.pow(10, 3)) / Math.pow(10, 3);
                            s1 = Double.toString(tmp4);
                            i += tmp2 - i;
                            tmp2 = s1.length();

                            for (tmp3 = 0; tmp3 < tmp2; tmp3++) {

                                goodString[k++] = s1.charAt((int) tmp3);

                            }


                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case 'c':
                        try {

                            i += 4;
                            tmp2 = i;

                            while ((in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) || in[(int) tmp2 + 1] == '.' || in[(int) tmp2 + 1] == ')') {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                                if (in[(int) tmp2] == ')') break;
                            }
                            if (in[(int) tmp2] != ')') ++tmp2;
                            tmp4 = Math.cos(Double.parseDouble(s.substring(i, (int) tmp2)) * (Math.PI / 180.0));
                            tmp4 = Math.round(tmp4 * Math.pow(10, 3)) / Math.pow(10, 3);
                            s1 = Double.toString(tmp4);
                            i += tmp2 - i;
                            tmp2 = s1.length();

                            for (tmp3 = 0; tmp3 < tmp2; tmp3++) {
                                goodString[k++] = s1.charAt((int) tmp3);
                            }

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case 't':
                        try {

                            i += 4;
                            tmp2 = i;

                            while ((in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) || in[(int) tmp2 + 1] == '.' || in[(int) tmp2 + 1] == ')') {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                                if (in[(int) tmp2] == ')') break;
                            }
                            if (in[(int) tmp2] != ')') ++tmp2;
                            tmp4 = Math.tan(Double.parseDouble(s.substring(i, (int) tmp2)) * (Math.PI / 180.0));
                            tmp4 = Math.round(tmp4 * Math.pow(10, 3)) / Math.pow(10, 3);
                            s1 = Double.toString(tmp4);
                            if (tmp4 > inf) {
                                goodString=s1.toCharArray();
                                infi = true;
                                return;
                            }


                            i += tmp2 - i;
                            tmp2 = s1.length();

                            for (tmp3 = 0; tmp3 < tmp2; tmp3++) {
                                goodString[k++] = s1.charAt((int) tmp3);
                            }


                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case 'P':
                        try {

                            tmp1 = i;
                            tmp2 = i;
                            while (in[(int) tmp1 - 1] - '0' < 10 && in[(int) tmp1 - 1] - '0' >= 0) {
                                tmp1--;
                                if (tmp1 == 0) break;
                            }


                            while (in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                            }


                            k -= i - tmp1;
                            s1 = s.substring((int) tmp1, i);
                            s2 = s.substring(i + 1, (int) tmp2 + 1);

                            tmp3 = nPr(Long.parseLong(s1), Long.parseLong(s2));
                            if (tmp3 == 0) {
                                mathError=true;
                                //_fxController._Console.setText("  > Math Error");
                                return;
                            } else if (tmp3 < 0) {
                                overFlow=true;
                              //  _fxController._Console.setText("  > Overflow");
                                return;
                            } else {
                                s3 = Long.toString((int) tmp3);
                                tmp3 = s3.length();
                                for (tmp1 = 0; tmp1 < tmp3; tmp1++) {
                                    goodString[k++] = s3.charAt((int) tmp1);
                                }

                            }
                            i += tmp2 - i;

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case 'C':
                        try {

                            tmp1 = i;
                            tmp2 = i;
                            while (in[(int) tmp1 - 1] - '0' < 10 && in[(int) tmp1 - 1] - '0' >= 0) {
                                tmp1--;
                                if (tmp1 == 0) break;
                            }
                            while (in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                            }

                            k -= i - tmp1;
                            s1 = s.substring((int) tmp1, i);
                            s2 = s.substring(i + 1, (int) tmp2 + 1);
                            tmp3 = nCr(Long.parseLong(s1), Long.parseLong(s2));

                            if (tmp3 == 0) {
                                //_fxController._Console.setText("  > Math Error");
                                mathError=true;
                                return;
                            } else if (tmp3 < 0) {
                                overFlow=true;
                                //_fxController._Console.setText("  > Overflow");
                                return;
                            } else {
                                s3 = Long.toString((int) tmp3);
                                tmp3 = s3.length();
                                for (tmp1 = 0; tmp1 < tmp3; tmp1++) {
                                    goodString[k++] = s3.charAt((int) tmp1);
                                }

                            }
                            i += tmp2 - i;

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case '!':
                        try {

                            tmp1 = i;
                            while (in[(int) tmp1 - 1] - '0' < 10 && in[(int) tmp1 - 1] - '0' >= 0) {
                                tmp1--;
                                if (tmp1 == 0) break;
                            }
                            k -= i - tmp1;//TO OVERWRITE EXISTING DATA
                            s1 = s.substring((int) tmp1, i);
                            tmp3 = factorial(Long.parseLong(s1));

                            if (tmp3 == 0) {
                                mathError=true;
                               // _fxController._Console.setText("  > Math Error");
                                return;
                            } else if (tmp3 < 0) {
                                overFlow=true;
                               // _fxController._Console.setText("  > Overflow");
                                return;
                            } else {
                                s3 = Long.toString((int) tmp3);
                                tmp3 = s3.length();
                                for (tmp1 = 0; tmp1 < tmp3; tmp1++) {
                                    goodString[k++] = s3.charAt((int) tmp1);
                                }

                            }

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case '%':
                        try {

                            tmp1 = i;
                            tmp2 = i;
                            while (in[(int) tmp1 - 1] - '0' < 10 && in[(int) tmp1 - 1] - '0' >= 0) {
                                tmp1--;
                                if (tmp1 == 0) break;
                            }

                            while (in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                            }

                            k -= i - tmp1;
                            s1 = s.substring((int) tmp1, i);
                            s2 = s.substring(i + 1, (int) tmp2 + 1);
                            tmp3 = Long.parseLong(s1) % Long.parseLong(s2);


                            s3 = Long.toString((int) tmp3);
                            tmp3 = s3.length();
                            for (tmp1 = 0; tmp1 < tmp3; tmp1++) {
                                goodString[k++] = s3.charAt((int) tmp1);
                            }
                            i += i - tmp2 + 2;

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                    case '^':
                        try {

                            tmp1 = i;
                            tmp2 = i;
                            while (in[(int) tmp1 - 1] - '0' < 10 && in[(int) tmp1 - 1] - '0' >= 0) {
                                tmp1--;
                                if (tmp1 == 0) break;
                            }

                            while (in[(int) tmp2 + 1] - '0' < 10 && in[(int) tmp2 + 1] - '0' >= 0) {
                                tmp2++;
                                if (tmp2 == x - 1) break;
                            }

                            k -= i - tmp1;
                            s1 = s.substring((int) tmp1, i);
                            s2 = s.substring(i + 1, (int) tmp2 + 1);
                            tmp3 = power(Long.parseLong(s1)  ,Long.parseLong(s2));


                            s3 = Long.toString( tmp3);
                            tmp3 = s3.length();
                            for (tmp1 = 0; tmp1 < tmp3; tmp1++) {
                                goodString[k++] = s3.charAt((int) tmp1);
                            }
                            i += i - tmp2 + 2;

                        } catch (Exception e) {
                            _fxController._Console.setText("  > Syntax Error");
                            syntaxError=true;
                        }
                        break;
                }
            }

        }
    }

    /**
     *
     @inheritDoc
     */
    @Override
    public String getResult() {
        String tmp=INFIX_TO_POSTFIX();
        if(!noExpression&&!syntaxError&&!mathError&&lastAns!=null){
            if(!lastExp.equals(_fxController._editable.getText())) {
                _prev_answers.push(lastAns);
                _prev_exp.push(lastExp);
                historySize++;
            }
        }

        lastAns=tmp;
        lastExp=_fxController._editable.getText();
        currentEXP=lastExp;
        return current();
    }

    /**
     *
     @inheritDoc
     */
    @Override
    public String current() {
        if (lastAns==null) return "0";
        return lastAns;
    }

    /**
     *
     *@inheritDoc
     */
    @Override
    public void prev() {
        String s1,s2;

            if(!_prev_answers.empty()){
               // _fxController.DisableButtons();


                do {
                    s1 = _prev_answers.pop();
                    s2 = _prev_exp.pop();
                    _next_answers.push(s1);
                    _next_exp.push(s2);

                } while(!_prev_answers.empty()&&s1.equals(_fxController._result.getText())&&s2.equals(_fxController._editable.getText()));
            _fxController._editable.setText(s2);
            _fxController._result.setText(s1);
        }

    }

    /**
     *
     *@inheritDoc
     */
    @Override
    public void next() {
        String s1="",s2="";
        if(_next_answers.empty()){
            _fxController._editable.setText(currentEXP);
            _fxController._result.setText("");
           // _fxController.EnableButtons();
            return;
        }
        //_fxController.DisableButtons();
        do {
            s1 = _next_answers.pop();
            s2 = _next_exp.pop();
            _prev_answers.push(s1);
            _prev_exp.push(s2);

        } while(!_next_answers.empty()&&s1.equals(_fxController._result.getText())&&s2.equals(_fxController._editable.getText()));

        if(_next_answers.empty()&&s1.equals(_fxController._result.getText())&&s2.equals(_fxController._editable.getText())){
            _fxController._editable.setText(currentEXP);
            _fxController._result.setText("");
            //_fxController.EnableButtons();
            return;
        }
            _fxController._editable.setText(s2);
            _fxController._result.setText(s1);


    }

    //////////////////////////////////
    private int priority(char c) {
        if ((c - '0' < 10 && c - '0' >= 0) || c == '.'||c=='~') return 0;
        switch (c) {// LEVEL OF + - higher and it works no worries xD
            case '+':
            case '-':
                return 2;
            case '*':
            case '/':
                return 1;
            case '(':
                return 3;
            default:
                return -1;//ERROR
        }
    }
    /**
    * @inheritDoc
     */
    @Override
    public String INFIX_TO_POSTFIX() {
        Stack<Character> POSTFIX_operators = new Stack();
        char postFix[] = new char[100];
        int l = 0;
        if (!noExpression && goodString[0] == '-') goodString[0] = '~';//SOME SIGN TO KNOW NEGATIVE NUMBERS
        try {
            for (int i = 0; i < k; i++) {
                if (priority(goodString[i]) == 0) postFix[l++] = goodString[i];
                else if (goodString[i] == '(') {
                    postFix[l++] = ' ';
                    POSTFIX_operators.push('(');
                    if (goodString[i + 1] == '-') goodString[i + 1] = '~';
                } else if (goodString[i] == ')') {

                    while (!POSTFIX_operators.empty() && POSTFIX_operators.peek() != '(') {
                        postFix[l++] = ' ';
                        postFix[l++] = POSTFIX_operators.pop();
                    }

                    if (!POSTFIX_operators.empty() && POSTFIX_operators.peek() != '(') {
                        syntaxError = true;
                    } else {
                        POSTFIX_operators.pop();
                    }
                } else {
                    postFix[l++] = ' ';
                    {
                        while (!POSTFIX_operators.empty() && priority(goodString[i]) >= priority(POSTFIX_operators.peek())) {
                            postFix[l++] = POSTFIX_operators.pop();
                            postFix[l++] = ' ';
                        }
                        POSTFIX_operators.push(goodString[i]);
                    }
                }
            }

            while (!POSTFIX_operators.empty()) {
                postFix[l++] = ' ';
                postFix[l++] = POSTFIX_operators.pop();// remaining
            }
        } catch (Exception e) {
            _fxController._Console.setText("  > Syntax Error");
            syntaxError = true;
        }
        postFix[l] = '#'; //INDICATE END OF ARR
        return POSTFIX_TO_VALUE(new String(postFix));
    }
    /**
     * @inheritDoc
     *
     */
    @Override
   public String POSTFIX_TO_VALUE(String arr) {
        Stack<String> numbers = new Stack();
        int zz=0;
        for(int i=0;arr.charAt(i)!='#';i++){
            zz++;
        }
        int start , end ;
        try {
            for (int i = 0; i < zz; i++) {
                if (arr.charAt(i) == ' ') continue;
               // floatingPoint=false;
                if ((arr.charAt(i) - '0' < 10 && arr.charAt(i) - '0' >= 0) || arr.charAt(i) == '.'||arr.charAt(i)=='~') {
                    start = i;
                    end=i;
                    i++;
                    while ((arr.charAt(i) - '0' < 10 && arr.charAt(i) - '0' >= 0) ||arr.charAt(i) == '.') {
                        end = i;
                        i++;
                    }
                    numbers.push(arr.substring(start, end + 1));

                } else {
                    double v1,v2;
                    //CHECK IF ITS NEGATIVE NUMBER
                    if(numbers.peek().charAt(0)=='~'){
                        v2 = -Double.parseDouble(numbers.peek().substring(1,numbers.pop().length()));
                    }else{
                        v2 = Double.parseDouble(numbers.peek().substring(0,numbers.pop().length()));
                    }
                    if(numbers.peek().charAt(0)=='~'){
                        v1 = -Double.parseDouble(numbers.peek().substring(1,numbers.pop().length()));
                    }else{
                        v1 =  Double.parseDouble(numbers.peek().substring(0,numbers.pop().length()));
                    }
                    switch (arr.charAt(i)) {
                        case '+':
                            numbers.push(Double.toString(v1+v2));
                            break;
                        case '-':
                            numbers.push(Double.toString(v1-v2));
                            break;
                        case '*':
                            numbers.push(Double.toString(v1*v2));
                            break;
                        case '/':
                            numbers.push(Double.toString(Math.round(v1/v2 * Math.pow(10, 4)) / Math.pow(10, 4)));//4 decimal point
                            break;
                    }
                }

            }
            if (infi) return "Infinity";
            if (syntaxError) {
                _fxController._Console.setText("  > Syntax Error");
                return "";
            }
            if(mathError){
                _fxController._Console.setText("  > Math Error");
                return "";
            }
            if(overFlow){
                _fxController._Console.setText("  > Over Flow");
                return "";
            }
            if(noExpression){
                return "0";
            }

            //if user sent -ve number without operation this will handle it
            String s;
            s=numbers.pop();
            char[] ss=s.toCharArray();
            if(ss[0]=='~')ss[0]='-';

            return Double.toString(Double.parseDouble(new String(ss)));//if input is 01 this will convert it to 1(better view)


        } catch (Exception e) {

            _fxController._Console.setText("  > Syntax Error");
            syntaxError=true;
            return "";
        }

    }
}
