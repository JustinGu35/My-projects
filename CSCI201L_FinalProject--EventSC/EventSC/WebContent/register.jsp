<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="RegisterStyle.css"/>
	<script>
		function validateForm() {
			// set error message div to empty here
			
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "Register?" +
						"username=" + document.getElementsByName("email")[0].value +
						"&password=" + document.getElementsByName("password")[0].value +
						"&passwordConf=" + document.getElementsByName("passwordConf")[0].value
						, false);
			xhttp.send();
			if (xhttp.responseText.trim() == "1") {
				// set error message div to "The passwords do not match." here
				document.getElementById("ErrorMessage").innerHTML = "The passwords do not match.";
				return false;
			}
			else if (xhttp.responseText.trim() == "2") {
				// set error message div to "The username is already taken." here
				document.getElementById("ErrorMessage").innerHTML = "The username is already taken.";
				return false;
			}
			else if (xhttp.responseText.trim() == "3") {
				// set error message div to "Fields cannot be empty." here
				document.getElementById("ErrorMessage").innerHTML = "Fields cannot be empty.";
				return false;
			}
			else if (xhttp.responseText.trim() == "4") {
				// set error message div to "Not a USC registered email." here
				document.getElementById("ErrorMessage").innerHTML = "Not a USC registered email.";
				return false;
			}
			return true;
		}
	</script>
	<style>
	#ErrorMessage {
	opacity: 1;
	position: absolute;
	left: 0%;
	top: 205%;
	box-sizing: border-box;
	margin: 0;
	padding: 0;
	overflow: visible;
	width: 204px;
	white-space: nowrap;
	text-align: left;
	font-family: Sukhumvit Set;
	font-style: normal;
	font-weight: bold;
	font-size: 26px;
	color: rgba(193, 31, 31, 1);
	letter-spacing: 0.1px;
}
	</style>
</head>
<body>
<div id="Register">
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
	
	
	<div id="RegisterLink">
		<span><a href="register.jsp" style="color: rgba(248,240,240,1);">Register</a></span>
	</div>
	
	<div id="Group_27">
		
		<div id="Group_33">
			<form id="loginForm" action="index.jsp"  method="post" onsubmit="return validateForm();">
				
				<div id="Email">
					<span>Email</span>
					<br/>
					<input type="text" class="registerInput" name="email" />
				</div>
				<div id="Password">
					<span>Password</span>
					<br/>
					<input type="password" class="registerInput" name="password" />
				</div>
				<input type="image" src="img/register_button.png" id="registerButton" style="position: absolute; z-index: 1; bottom: 10%; left: 38%; cursor: pointer;" />
				<div id="Confirm_Password">
					<span>Confirm Password</span>
					<br/>
					<input type="password" class="registerInput" name="passwordConf" />
					<span id="ErrorMessage"></span>
				</div>
			</form>
		</div>
	</div>
</div>


</body>
</html>