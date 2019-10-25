<?php // Create connection
$conn = new mysqli("localhost", "lort", "1234", "registration");
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 ?>
