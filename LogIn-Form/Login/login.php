<?php
$badInput=FALSE;
session_start();
if(isset($_SESSION['id'])){
    header('Location: ../Logged-In/welcome.php');
}
if(isset($_POST['login'])){
if(isset($_POST['email'])&&isset($_POST['password'])){
    $email = $_POST['email'];
$pass = md5($_POST['password']);
include('../Config/DBConnection.php');

$result = $conn->query("SELECT * FROM user WHERE email='$email' AND password='$pass' ");

    if ($result->num_rows > 0) {
 
        $row=$result->fetch_assoc();
        $_SESSION['email']=$row['email'];
        $_SESSION['id']=$row['user_id'];
        $_SESSION['regDate']=$row['registration_date'];
        $_SESSION['username']=$row['username'];
        header("Location: ../Logged-In/welcome.php");

    } else {
        $badInput=TRUE;
    }
}else{
    $badInput=TRUE;
}
    

$conn->close();
}

?>

<!DOCTYPE html>
<html lang="en">

<?php include('../header.html') ?>

<body>
    <?php include('login.html') ?>
    <?php include('../footer.html') ?>
</body>
<script>
function validateEmail(email) {
    var regex =
        /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return regex.test(email);
}

function notEmptyFields() {

    return $("#email").val() && $("#password").val();
}

$("#logBtn").click(function(e) {
    e.preventDefault();
    if (notEmptyFields()) {
        if (validateEmail($("#email").val())) {
            var method = "POST";
            var url = "<?php echo $_SERVER['PHP_SELF']; ?>";
            var email = $("#email").val();
            var password = $("#password").val();
            $.ajax({
                type: method,
                url: url,
                data: {
                    login: 1,
                    email: email,
                    password: password
                },
                success: function(data) {
                    //alert("Sent From AJAX");
                    var newDoc = document.open("text/html", "replace");
                    newDoc.write(data);
                    newDoc.close();
                }
            });
        } else {
            $("#errors").text("Email format is invalid !");
        }
    } else {
        $("#errors").text("Some Required Fields are empty !");
    }
});
$("#regBtn").click(function(e) {
    e.preventDefault();
    var method = "GET";
    var url = "../Register/register.php";
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