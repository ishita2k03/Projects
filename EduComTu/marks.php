<!DOCTYPE html>
<html>
<head>
<title>EduComTu</title>
<link rel="stylesheet" href="styleP.css">
<style>
.center{
    position: absolute;
    top: 40%;
    left: 60%;
    margin: 5px 5px;
    transform: translate(-50%,-50%);
    width: 700px;
    height: 300px;
    border-radius: 10px;
}
table {
border-collapse: collapse;
width: 100%;
color: black;
font-family: monospace;
font-size: 25px;
text-align: left;
border: 2px solid black;
padding-right: 60px;
}
th {
    
    border: 2px solid black;
color: purple;
}
tr{
    border: 2px solid black;
}
tr:nth-child(even) {background-color: #f2f2f2}

</style>
</head>
<body>
<div class="wrapper">
        <div class="sidebar">
        <h2>EduCom TU</h2>
            <ul>
                <li><a href="index.html">HOMEPAGE</a></li>
                <li><a href="attendance.php">ATTENDANCE</a></li>
                <li><a href="feeDetails.html">FEE DETAILS</a></li>
                <li><a href="course.html">COURSE DETAILS</a></li>
                <li><a href="exam_details.php">EXAM DETAILS</a></li>
                
            </ul>
        </div>
    </div>
    <a href="index.html"><img src="logo_se.jpeg" border="5" align="right" height="100px" width="200px"></a>

<div class="center"> 
 <center> <h1> MARKS</h1> </center>  
<table>
<tr>
<th>Course</th>
<th>Total Marks</th>
<th>Marks Scored</th>
<th>Grade</th>

</tr>
<?php
$conn = mysqli_connect("localhost", "root", "", "educomtu");
// Check connection
if ($conn->connect_error) {
die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT * FROM marks";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
// output data of each row
while($row = $result->fetch_assoc()) {
echo "<tr><td>" . $row["course"]. "</td><td>" . $row["total_marks"] . "</td><td>"
. $row["marks_obtained"]. "</td><td>". $row["grade"]. "</td></tr>";
}
echo "</table>";
} else { echo "0 results"; }
$conn->close();
?>
</table>
</div>
</body>
</html>