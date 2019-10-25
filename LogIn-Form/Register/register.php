<?php
$badEmail=FALSE;
$badUserName=FALSE;
$badInput=FALSE;
session_start();
if(isset($_SESSION['id'])){
    header('Location: ../Logged-In/welcome.php');
}
if(isset($_POST['register'])){
$email = $_POST['email'];
$username=$_POST['username'];
$pass = $_POST['password'];
include('../Config/DBConnection.php');
$encrypted_password=md5($pass);
$result = $conn->query("SELECT * FROM user WHERE email='$email'");
if ($result->num_rows > 0) {
    $badEmail=TRUE;
} else {
    $result = $conn->query("SELECT * FROM user WHERE username='$username'");
    if ($result->num_rows > 0) {
        $badUserName=TRUE;
        } else {
        $result = $conn->query("INSERT INTO `user` (`email`, `username`, `password`) VALUES ( '$email','$username', '$encrypted_password')");
        if($result===TRUE){
            $result = $conn->query("SELECT * FROM user WHERE email='$email'");
            $row=$result->fetch_assoc();
            $_SESSION['email']=$row['email'];
            $_SESSION['id']=$row['user_id'];
            $_SESSION['regDate']=$row['registration_date'];
            $_SESSION['username']=$row['username'];
            header('Location: ../Logged-In/welcome.php');
        }else{
            $badInput = TRUE;
        }
    }
}
    

$conn->close();

}

?>

<!DOCTYPE html>
<html lang="en">

<?php include('../header.html') ?>

<body>
    <?php include('register.html') ?>
    <?php include('../footer.html') ?>
</body>
<script>
function validateEmail(email) {
    var regex =
        /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return regex.test(email);
}

function notEmptyFields() {

    return $("#email").val() && $("#password").val() && $("#username");
}
$("#regBtn").click(function(e) {
    e.preventDefault();
    if (notEmptyFields()) {
        if (validateEmail($("#email").val())) {
            if ($("#password").val() === $("#re_password").val()) {
                var method = "POST";
                var url = "<?php echo $_SERVER['PHP_SELF']; ?>";
                var email = $("#email").val();
                var password = $("#password").val();
                var username = $("#username").val();
                $.ajax({
                    type: method,
                    url: url,
                    data: {
                        register: 1,
                        email: email,
                        password: password,
                        username: username
                    },
                    success: function(data) {
                        //alert("Sent From AJAX");
                        var newDoc = document.open("text/html", "replace");
                        newDoc.write(data);
                        newDoc.close();
                    }
                });
            } else {
                $("#errors").text("Passwords do NOT match !");
            }
        } else {
            $("#errors").text("Email format is invalid !");
        }
    } else {
        $("#errors").text("Some Required Fields are empty !");
    }
});
$("#logBtn").click(function(e) {
    e.preventDefault();
    var method = "GET";
    var url = "../Login/login.php";
    $.ajax({
        type: method,
        url: url,
        success: function(data) {
            //alert("Sent From AJAX");
            window.location = url;
        }
    });
});
</script>

</html>