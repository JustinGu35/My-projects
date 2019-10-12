<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8"/>
<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
<title>EventSC</title>
<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="RegisterStyle.css"/>
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
				<img src="img/register_button.png" id="registerButton" style="position: absolute; z-index: 1; bottom: 10%; left: 38%; cursor: pointer;" />
				<div id="Confirm_Password">
					<span>Confirm Password</span>
					<br/>
					<input type="password" class="registerInput" name="passwordConf" />
				</div>
			</form>
		</div>
	</div>
</div>

<script>
document.getElementById("registerButton").onclick = function(event) {
	document.getElementById("loginForm").submit();
};
</script>
</body>
</html>