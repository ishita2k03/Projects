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
                <li><a href="attendance.php">ATTENDANCE</a></li>
                <li><a href="feeDetails.html">FEE DETAILS</a></li>
                <li><a href="course.html">COURSE DETAILS</a></li>
                <li><a href="exam_details.php">EXAM DETAILS</a></li>
                <li><a href="marks.php">MARKS</a></li>
                
            </ul>
        </div>
    </div>
  <center><h1>Personal Information</h1></center>

<?php
$conn = mysqli_connect("localhost", "root","", "educomtu");
// Check connection
if ($conn-> connect_error) {
      die("Connection failed: " .$conn-> connect_error );
}


$sql="SELECT * FROM personal_info";
$result = $conn-> query($sql);

//find the number of records returned
if($result->num_rows > 0){
  while ($row1 = mysqli_fetch_array($result)) {
    ?>
    <div class="center">
    <div class="form">
    <h2>---Details---</h2>
    <span>Name:</span> <?php echo $row1['name']; ?>
    <span><br>Roll Number:</span> <?php echo $row1['roll_number']; ?>
    <span><br>Branch</span> <?php echo $row1['branch']; ?>
    <span><br>Date of Birth</span> <?php echo $row1['dob']; ?>
    <span><br>Father Name</span> <?php echo $row1['father_name']; ?>
    <span><br>Mother Name:</span> <?php echo $row1['mother_name']; ?>
    <span><br>Student E-mail:</span> <?php echo $row1['student_email']; ?>
    <span><br>Student Contact No:</span> <?php echo $row1['student_mobile_number']; ?>
    <span><br>Parent E-mail</span> <?php echo $row1['parent_email']; ?>
    <span><br>Parent Contact No.</span> <?php echo $row1['parent_mobile_number']; ?>
    <span><br>Address:</span> <?php echo $row1['Address']; ?>   
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