package sample;
public interface Calculator {
    /**
     * takes input from the user tokenize it and then do the wanted maths functions
     * save the edits for goodString global char array
     * @param s input String from the editable label
     */
    public void input(String s);
    /**
     *
     * @return result String for the operations specified in editable label
     */
    public String getResult();
    /**
     *
     * @return current String Answer if its null return 0
     */
    public String current();
    /**
     *
     * change calculator editable and result labels for previous operations
     */
    public void prev();
    /**
     *
     * change calculator editable and result labels for next operations
     */
    public void next();

    /**
     * NO PARAMS
     * return postfix string result of public char array u will find in "CalculatorSystem Class"
     *
     * @return      POSTFIX STRING RESULT OF PUBLIC CHAR ARRA char array
     */
    public String INFIX_TO_POSTFIX();

    /**
     *@param arr postfix array we want to evaluate
     * @return     value of the postfix string in String format
     */
    public String POSTFIX_TO_VALUE(String arr);

}