<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>EduComTU</title>
  <link rel="stylesheet" href="styleP.css">

</head>

<body>
  <section class="header">

  
  <a href="index.html"><img src="logo_se.jpeg" border="5" align="right" height="100px" width="200px"></a>

  </section>
  <div class="wrapper">
        <div class="sidebar">
        <h2>EduCom TU</h2>
            <ul>
                <li><a href="index.html">HOMEPAGE</a></li>
                <li><a href="personal_info.php">PERSONAL DETAILS</a></li>
                <li><a href="attendance.php">ATTENDANCE</a></li>
                <li><a href="feeDetails.html">FEE DETAILS</a></li>
                <li><a href="course.html">COURSE DETAILS</a></li>
                <li><a href="marks.php">MARKS</a></li>
            </ul>
        </div>
    </div>
  <center><h1>Exam Details</h1></center>

<?php
$conn = mysqli_connect("localhost", "root","", "educomtu");
// Check connection
if ($conn-> connect_error) {
      die("Connection failed: " .$conn-> connect_error );
}


$sql="SELECT * FROM exam_details";
$result = $conn-> query($sql);

//find the number of records returned
if($result->num_rows > 0){
  while ($row1 = mysqli_fetch_array($result)) {
    ?>
    <div class="center">
    <div class="form">
    <h2>DATESHEET</h2>
    <span>UCS503 : </span> <?php echo $row1['UCS503']; ?>
    <span><br>UCS411 : </span> <?php echo $row1['UCS411']; ?>
    <span><br>UCS310 : </span> <?php echo $row1['UCS310']; ?>
    <span><br>UMA035 : </span> <?php echo $row1['UMA035']; ?>
    <br></div>
</div>
    <?php
    }
}
else {
      echo "0 result";
}

$conn->close();

?>

</body>

</html>