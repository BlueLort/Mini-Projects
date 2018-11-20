package sample;
//MVC DP
public class Controller {
    private CalculatorSystem  CaclulatorSystem_Instance;
    public void setfxController(FXMLController c){
        CaclulatorSystem_Instance.setFXMLController(c);
    }
    public Controller(){
        CaclulatorSystem_Instance  =  CalculatorSystem.getCalculatorSystem();
    }
    public void input(String s){
        CaclulatorSystem_Instance.input(s);
    }
    public String getResult(){
        return CaclulatorSystem_Instance .getResult();
    }
    public String current(){
        return CaclulatorSystem_Instance .current();
    }
    public void prev(){
         CaclulatorSystem_Instance.prev();
    }
    public void next(){
          CaclulatorSystem_Instance.next();
    }
    public void reset(){
        CaclulatorSystem_Instance.reset();
    }
}
