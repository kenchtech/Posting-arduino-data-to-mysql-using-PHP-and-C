<?php
//connection to database
$conn= mysqli_connect('localhost','root','','arduinosensor') or die('cannot connect to the DB');

if(!$conn){
    die("Database connection failed: ". mysqli_connect_error());
}
else{
  echo "DB connection successfull<br/>";
}

//$temperature=$_GET['temperature']

$time = time(); //adds time stamp
$tempF = $_POST["temp"];
$humid = $_POST["tempc"];
$file = 'temp.html';  //Html file to display POST values
$data = $time."  -Temperature:  ".$tempF."  -Humidity  ".$humid;
file_put_contents($file, $data);
$sql = "INSERT INTO tempsen (temperature, Humidity) VALUES ('$tempF','$humid')"; //Query to input POST data into tempsen database
//Ensure query is true
if ($conn->query($sql) == TRUE){
echo "worked<br/>";
}
else{
    die('Failed query:' .$sql); //Kills the connection to the database if the query fails
    }
?>