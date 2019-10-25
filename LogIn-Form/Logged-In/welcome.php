<?php
session_start();
if(!isset($_SESSION['id'])){
    header('Location: ../Login/login.php');
}
if(isset($_GET['logout'])){
unset($_SESSION['email']);
unset($_SESSION['id']);
unset($_SESSION['regDate']);
unset($_SESSION['registered']);

header("Location: ../Login/login.php");
}
?>

<!DOCTYPE html>
<html lang="en">

<?php include('../header.html') ?>

<body>
    <?php include('welcome.html') ?>
    <?php include('../footer.html') ?>
</body>
<script>
$("#logOut").click(function(e) {
    e.preventDefault();
    var method = "GET";
    var url = "<?php echo $_SERVER['PHP_SELF']; ?>";
    $.ajax({
        type: method,
        url: url,
        data: {
            logout: 1
        },
        success: function(data) {
            //alert("Sent From AJAX");
            var newDoc = document.open("text/html", "replace");
            newDoc.write(data);
            newDoc.close();
        }
    });
});
</script>

</html>