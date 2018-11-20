

import controller.Controller;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{

        FXMLLoader f=new FXMLLoader(getClass().getResource("view/RobotGUI.fxml"));
        Parent root = f.load();
        Controller.setControllerInstance(f.getController());
        primaryStage.setTitle("MindCloud Robot Communicator");
        primaryStage.setScene(new Scene(root, 1024, 768));
        primaryStage.setOpacity(1);
        primaryStage.getIcons().add(new Image("file:res/logo.png"));
        primaryStage.show();
        primaryStage.setOnCloseRequest(e->{
            Controller.getInstance().getSerialListener().close();
        });
    }


    public static void main(String[] args) {
        launch(args);
    }
}
