

<!DOCTYPE html>
<html lang="en" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>EduCom TU</title>
        <link rel="stylesheet" href="se.css">
    </head>
    <body>
        <?php
        $connect=mysqli_connect("localhost","root","","login") or die("Connection Failed!");
        if(!empty($_GET['submit'])){
            $username=$_POST['user'];
            $password=$_POST['pass'];
            $query="select * from login where username='$username' and password='$password'";
            $result=mysqli_query($connect, $query); 
            $count=mysqli_num_rows($result);
            if($count>0){
                 echo "Login Susccesfull!";
            }
            else{
                echo "Wrong Username or Password!";
            }
                    
        }
        ?>
        <header>
            <nav class="navbar">
                <ul>
                    <li class="image"> 
                       <img src="logo_se.jpeg"style="width :700px; height: 600px;" >
                    </li>
                </ul>
            </nav>
        </header>
        <div class="center">
            
            <h1>Login</h1>
            
            <form method="post">
                <div class="txt_field">
                    <input type="text" name="user" required>
                    <span></span>
                    <label>Username</label>
                </div>
                <div class="txt_field">
                    <input type="password" name="pass" required>
                    <span></span>
                    <label>Password</label>
                </div>
                <div class="pass">Forgot Password?</div>
                <input type="submit" value="Login" name="submit">
            </form>
        </div>
        
        
    </body>
    </html>