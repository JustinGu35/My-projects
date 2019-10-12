<%@ page import="utility.Helper" %>
<%@ page import="utility.User" %>

<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="ProfileStyle.css"/>
	<script>
		
	<%
	int userID = -1;
	if (session.getAttribute("userID") != null) {
		String userIDStr = "" + session.getAttribute("userID");
		if (userIDStr != null && !userIDStr.trim().equals("")) {
			userID = Integer.parseInt(userIDStr.trim());
		}
	}
	
	int otherID = -1;
	if (request.getParameter("otherID") != null) {
		String otherIDStr = "" + request.getParameter("otherID");
		if (otherIDStr != null && !otherIDStr.trim().equals("")) {
			otherID = Integer.parseInt(otherIDStr.trim());
		}
	}
	
	User usr = null;
	if(otherID == -1)
	{
		usr = Helper.getUserByID(userID);
	}
	else if(otherID == userID)
	{
		usr = Helper.getUserByID(userID);
		otherID = -1;
	}
	else
	{
		usr = Helper.getUserByID(otherID);
	}
	
	// unchecked if userID == -1 but they should only be here if logged in anyways
	
	%>	
	
		function updateProfile() {
			var fname = document.getElementById("formFirstName").value;
			var lname = document.getElementById("formLastName").value;
			var email = document.getElementById("formEmail").value;
			var phone = document.getElementById("formPhone").value;
			var major = document.getElementById("formMajor").value;
			var gradyear = document.getElementById("formGradYear").value;
			var id = <%=userID%>;
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "UpdateProfile?userID=" + id +
						"&fname=" + fname +
						"&lname=" + lname +
						"&email=" + email +
						"&phone=" + phone +
						"&major=" + major +
						"&gradyear=" + gradyear
						, false);
			xhttp.send();
		}
	</script>
</head>
<body>

	<%	
	
	
	
	%>

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
		<% 
			if(userID != -1){
		%>
			<div id="Login">
				<span><a href="profile.jsp" style="color: rgba(248,240,240,1);">Profile</a></span>
			</div> 
			
			<div id="Register">
				<span><a href=" " id="signout" style="color: rgba(248,240,240,1);">Logout</a ></span>
			</div>
		<%		
			}
			else if(userID == -1){
		%>
			<div id="Login">
				<span><a href="login.jsp" style="color: rgba(248,240,240,1);">Login</a></span>
			</div>
			<div id="Register">
				<span><a href="register.jsp" style="color: rgba(248,240,240,1);">Register</a></span>
			</div>
		<% 
			}
		%>
		
	
	
		<div id="Group_13">
			<a href="index.jsp"><img id="Backtomap" src="img/BackToMap.png"></a>
		</div>
		<div id="Group_16">
			<div id="user">
				<!-- <img id="userpic" src="<%= usr.getProfilepic().substring(0,usr.getProfilepic().length()-4) %>_redcircle.png"> -->
				<img id="userpic" src="<%= usr.getProfilepic() %>">
			</div>
			<% if (otherID == -1) { %><form id="profileForm" name="profileForm" method="post" action="index.jsp" onsubmit="updateProfile()"><% } %>
				<div id="profileInfo">
					
					<%
					if (otherID == -1) { // viewing him/herself
					%>
					<!-- MAKE SURE THERE IS AN EXTRA SPACE IN FRONT OF VALUE -->
					<div id="firstInfo">First: <input name="fname" id="formFirstName" class="formInput" value="<%= (usr.getFname() == null || usr.getFname().equals("")) ? "" : usr.getFname() %>" placeholder=" First Name..." /></div>
					<div id="lastInfo">Last: <input name="lname" id="formLastName" class="formInput" value="<%= (usr.getLname() == null || usr.getLname().equals("")) ? "" : usr.getLname() %>" placeholder=" Last Name..." /></div>
					<div id="emailInfo">Email: <input name="email" id="formEmail" class="formInput" value="<%= (usr.getEmail() == null || usr.getEmail().equals("")) ? "" : usr.getEmail() %>" placeholder=" Email..." /></div>
					<div id="phoneInfo">Phone: <input name="phone" id="formPhone" class="formInput" value="<%= (usr.getPhone() == null || usr.getPhone().equals("")) ? "" : usr.getPhone() %>" placeholder=" Phone Number..." /></div>
					<div id="majorInfo">Major: <input name="major" id="formMajor" class="formInput" value="<%= (usr.getMajor() == null || usr.getMajor().equals("")) ? "" : usr.getMajor() %>" placeholder=" Major..." /></div>
					<div id="gradyearInfo">Grad Year: <input name="gradyear" id="formGradYear" class="formInput" value="<%= usr.getGradyear() %>" placeholder=" Graduation Year..." /></div>
					<div id="ImageUpload">
					
					</div>
					<% } else { // viewing other user %>
					<div id="firstInfo">First: <%= usr.getFname() %></div>
					<div id="lastInfo">Last: <%= usr.getLname() %></div>
					<div id="emailInfo">Email: <%= usr.getEmail() %></div>
					<div id="phoneInfo">Phone: <%= usr.getPhone() %></div>
					<div id="majorInfo">Major: <%= usr.getMajor() %></div>
					<div id="gradyearInfo">Grad Year: <%= usr.getGradyear() %></div>
					<% } %>
					
				</div>
				<% if (otherID == -1) { %><input type="image" id="profileSaveChanges" src="img/save_changes_button.png" />
			</form>
			<form action = "ImageUpload" id="ImageUpload" method = "post" enctype = "multipart/form-data">
       				<input type = "file" name = "file" size = "50" />
				    <br />
				    <input type = "submit" value = "Upload File" />
			</form><% } %>
		</div>
	</div>
<script>
  document.getElementById("signout").onclick = function(event) {
      event.preventDefault();
      
      var xhttp = new XMLHttpRequest();
   xhttp.open("GET", "Logout", false);
   xhttp.send();
      
      window.location = "index.jsp";
  };
 </script>
</body>
</html>
