<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="utility.Activity" %>
    <%@ page import="java.util.ArrayList" %>
    <%@ page import="utility.Helper" %>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="DetailStyle.css"/>
	<%  
	int activityID = Integer.parseInt(request.getParameter("activityID"));
	Activity activity = Helper.getActivityByID(activityID);
	%>
	<script>
			
			function on() {
				  document.getElementById("overlay").style.display = "block";
				}

			function off() {
				  document.getElementById("overlay").style.display = "none";
			}
			var map;
		      function initMap() {
		    	  var latitude = 34.02235998929801; 
		          var longitude = -118.28511714935303; 
		          
		    	var myLatlng = {lat: latitude, lng: longitude};
		        map = new google.maps.Map(document.getElementById('map'), {
		          center: myLatlng,
		          zoom: 16
		        });
		        
		        var marker=new google.maps.Marker({
		    		position: new google.maps.LatLng(<%= activity.getLat() %>, <%= activity.getLon() %>),
    		        map: map
    		      });
		
		        google.maps.event.addListener(map,'click', function(event) {
		            off();
		            });
		      }
		</script>
</head>
<body>

	<%
	int userID = -1;
	if (session.getAttribute("userID") != null) {
		String userIDStr = "" + session.getAttribute("userID");
		if (userIDStr != null && !userIDStr.trim().equals("")) {
			userID = Integer.parseInt(userIDStr.trim());
		}
	}
	%>

<div id="Detail_Page">
	<div id="Group_18"><%=userID%>
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
	
		<% 
			if(userID != -1){
		%>
			<div id="Login">
				<span><a href="profile.jsp" style="color: rgba(248,240,240,1);">Profile</a></span>
			</div> 
			
			<div id="Register">
				<span><a href="index.jsp" id="signout" style="color: rgba(248,240,240,1);">Logout</a></span>
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
		
	<svg class="Rectangle_2">
		
	</svg>
	
	<div id="Group_13">
		<a href="index.jsp"><img id="Backtomap" src="img/BackToMap.png"></a>
	</div>
	<div id="Group_16">
		
		<div id="Group_30">

			<div id="EventIcon">
				<img id="EventPic" src="img/event_icon7.png">
			</div>
			<div id="Event_Name">
				<span style="max-width: 100%; white-space: pre-wrap; word-wrap: break-word;"><%= activity.getTitle() %></span>
			</div>
			<div id="DATE__TIME__Location_">
				<div id="startInfo">Start: <%= activity.getStartDate() %> <%= activity.getStartTime() %></div>
				<div id="endInfo">End: <%= activity.getEndDate() %> <%= activity.getEndTime() %></div>
				<div id="locationInfo">Location:</div>
				<div id="descriptionTitle">Description:</div>
				<div id="descriptionInfo" style="max-width: 100%; white-space: pre-wrap; word-wrap: break-word;"><%=activity.getDescription()%></div>
			</div>
			<div id="Initiator_">
				<span style="">Initiator</span>
			</div>
			<div id="Interested">
				<span>Interested</span>
			</div>
			<div id="initiatorPic">
				<a href="profile.jsp?otherID=<%= activity.getUserID() %>"><img id="initiatorProfile" src="<%= Helper.getUserByID(activity.getUserID()).getProfilepic() %>" width="100%" height="100%"></a>
			</div>
			<div id="User1Pic">
				<a href="profile.jsp?otherID=2"><img id="User1Profile" src="img/interested1.png" width="100%" height="100%"></a>
			</div>
			<div id="User2Pic">
				<a href="profile.jsp?otherID=3"><img id="User2Profile" src="img/interested2.png" width="100%" height="100%"></a>
			</div>
			<div id="User3Pic">
				<a href="profile.jsp?otherID=4"><img id="User3profile" src="img/interested3.png" width="100%" height="100%"></a>
			</div>
			
		</div>
	</div>
	<div id="map_button"><img src='img/map_icon.png' alt='GoogleIcon.png' id='google' onclick='on()'></div>
</div>
<div id="overlay" onclick="off()">
	<div id="map"></div>
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

<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCB_WPm3Y2eL3aSvs64KYGkDoQ_F4RYatE&language=en&callback=initMap"
    async defer></script>
</body>
</html>