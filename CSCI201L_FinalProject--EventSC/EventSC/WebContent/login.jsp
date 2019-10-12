<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="LoginStyle.css"/>
	<script>
		function validateForm() {
			// set error message div to empty here
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "Login?" +
						"username=" + document.getElementsByName("email")[0].value +
						"&password=" + document.getElementsByName("password")[0].value
						, false);
			xhttp.send();
			if (xhttp.responseText.trim() == "1") {
				// set error message div to "Incorrect password." here
				document.getElementById("ErrorMessage").innerHTML = "Incorrect password.";
				return false;
			}
			else if (xhttp.responseText.trim() == "2") {
				// set error message div to "This user does not exist." here
				document.getElementById("ErrorMessage").innerHTML = "This user does not exist.";
				return false;
			}
			return true;
		}
	</script>
</head>
<body>
<div id="Login">
	<div id="Group_18">
		<svg class="Rectangle_4">
			
		</svg>
	</div>
	
	<div id="Group_28">
		<svg class="Rectangle_1">
			
		</svg>
		<div id="USCCardinal">
			<a href="index.jsp"><img id="UscLogo" src="img/USC_logo.png"></a>
		</div>
	</div>
	<div id="EventSc">
		<a href="index.jsp"><span style="color:white;">Event</span><span style="color:rgba(246,190,52,1);">SC</span></a>
	</div>
	<svg class="Rectangle_2">
	</svg>
	<div id="LoginLink">
		<span><a href="login.jsp" style="color: rgba(248,240,240,1);">Login</a></span>
	</div>
	<svg class="Rectangle_2">
		
	</svg>
	
	
	<div id="Register">
		<span><a href="register.jsp" style="color: rgba(248,240,240,1);">Register</a></span>
	</div>
	
	
	<div id="Group_16">
		<div id="Group_32">
			<form id="loginForm" name="loginForm" action="index.jsp" method="post" onsubmit="return validateForm();">
				
				<div id="Email">
					<span>Email</span>
					<br/>
					<input type="text" class="loginInput" name="email" />
				</div>
				
				<div id="Password">
					<span>Password</span>
					<br/>
					<input type="password" class="loginInput" name="password" />
					<span id="ErrorMessage"></span>
				</div>
				<input type="image" src="img/login_button.png" id="loginButton" style="position: absolute; z-index: 1; bottom: 15%; left: 35%; cursor: pointer;" />
			</form>
		</div>
	</div>
</div>


</body>
</html>