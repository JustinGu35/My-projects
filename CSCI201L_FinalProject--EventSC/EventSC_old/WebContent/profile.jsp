<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="ProfileStyle.css"/>
</head>
<body>
<div id="Profile_Page">

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
	<div id="Login">
		<span><a href="login.jsp" style="color: rgba(248,240,240,1);">Login</a></span>
	</div>
	<svg class="Rectangle_2">

	</svg>


	<div id="Register">
		<span><a href="register.jsp" style="color: rgba(248,240,240,1);">Register</a></span>
	</div>

	<div id="Group_13">
		<a href="index.jsp"><img id="Backtomap" src="img/BackToMap.png"></a>
	</div>
	<div id="Group_16">
		<div id="user">
			<img id="userpic" src="img/initiator_redcircle.png">
		</div>
		<form id="profileForm" name="profileForm" method="post" action="index.jsp" onclick="return validateForm();">
			<div id="profileInfo"> <!-- MAKE SURE THERE IS AN EXTRA SPACE IN FRONT OF VALUE -->
				<div id="firstInfo">First: <input name="fname" id="formFirstName" class="formInput" value=" Jeffrey" placeholder=" First Name..." /></div>
				<div id="lastInfo">Last: <input name="lname" id="formLastName" class="formInput" value=" Miller" placeholder=" Last Name..." /></div>
				<div id="emailInfo">Email: <input name="email" id="formEmail" class="formInput" value=" jeffrey.miller@usc.edu" placeholder=" Email..." /></div>
				<div id="phoneInfo">Phone: <input name="phone" id="formPhone" class="formInput" value=" 2137407129" placeholder=" Phone Number..." /></div>
				<div id="majorInfo">Major: <input name="major" id="formMajor" class="formInput" value=" Computer Science" placeholder=" Major..." /></div>
				<div id="gradyearInfo">Grad Year: <input name="gradyear" id="formGradYear" class="formInput" value=" 2019" placeholder=" Graduation Year..." /></div>
			</div>
			<img id="profileSaveChanges" src="img/save_changes_button.png" />
		</form>
	</div>
</div>

<script>
	document.getElementById("profileSaveChanges").onclick = function() {
		document.getElementById("profileForm").submit();
	};
</script>

</body>
</html>
