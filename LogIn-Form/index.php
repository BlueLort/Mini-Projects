<?php session_start();
if(isset($_SESSION['id'])){
    header('Location: ../Logged-In/welcome.php');
}
 ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
    <title>Log-In Form</title>
    <link href="./font.css" rel="stylesheet" />
    <link href="./styles.css" rel="stylesheet" />
    <script src="./jquery.min.js"></script>
</head>

<body>
    <?php include('index.html') ?>
    <?php include('footer.html') ?>
</body>
<script>
$("#logBtn").click(function(e) {
    e.preventDefault();
    var method = "GET";
    var url = "./Login/login.php";
    $.ajax({
        type: method,
        url: url,
        success: function(data) {
            //alert("Sent From AJAX");
            window.location = url;
        }
    });
});
$("#regBtn").click(function(e) {
    e.preventDefault();
    var method = "GET";
    var url = "./Register/register.php";
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