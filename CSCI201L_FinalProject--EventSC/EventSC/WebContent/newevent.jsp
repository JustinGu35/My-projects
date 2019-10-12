<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
	<title>EventSC</title>
	<link rel="stylesheet" type="text/css" id="applicationStylesheet" href="NewEventStyle.css"/>
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
	
	        google.maps.event.addListener(map,'click', function(event) {
	        	var latitude = Math.round(event.latLng.lat() * 1000000) / 1000000;
	             var longitude = Math.round(event.latLng.lng() * 1000000) / 1000000;
	        	document.getElementById('lat').value = latitude;
	            document.getElementById('lon').value = longitude;
	            off();
	            });
	      }
	      
	      function validateEvent()
	      {
	    	  if(document.getElementById("Name").value.trim().length == 0)
	    	  {
	    		  alert("Event Name is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("date_start").value.trim().length == 0)
	    	  {
	    		  alert("Start Date is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("time_start").value.trim().length == 0)
	    	  {
	    		  alert("Start Time is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("date_end").value.trim().length == 0)
	    	  {
	    		  alert("End Start is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("time_end").value.trim().length == 0)
	    	  {
	    		  alert("End Time is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("lat").value.trim().length == 0)
	    	  {
	    		  alert("Location is required.");
	    		  return false;
	    	  }
	    	  if(document.getElementById("lon").value.trim().length == 0)
	    	  {
	    		  alert("Location is required.");
	    		  return false;
	    	  }
	    	  return true;
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
		
		if (userID == -1) {
			RequestDispatcher dispatch = getServletContext().getRequestDispatcher("/login.jsp");
			dispatch.forward(request,response);
		}
%>

	<div id="New_Event_Page">
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
		<svg class="Rectangle_7">
		</svg>
		<div id="Group_13">
			<a href="index.jsp"><img id="Backtomap" src="img/BackToMap.png" style="cursor: pointer;"></a>
		</div>
		<form id="NewEvent" name="NewEvent" action="NewActivity" method="GET" onsubmit="return validateEvent();">
			<div id="Group_19">
				<div id="Event_Name_A7_Text_7">
					<span>Event Name</span><span style="color:red;font-size:25px;">*</span><br>
				</div>
				<input id="Name" type="text" name="Name" >
			</div>
			<div id="Group_20">
				<div id="Date">
					<span>Start Date</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="date_start" type="date" name="Date_Start" width="313.5">
			</div>
			<div id="Group_21">
				<div id="Time">
					<span>Start Time</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="time_start" type="time" name="Time_Start" width="313.5">
			</div>
			<div id="Group_20_2">
				<div id="Date_2">
					<span>End Date</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="date_end" type="date" name="Date_End" width="313.5">
			</div>
			<div id="Group_21_2">
				<div id="Time_2">
					<span>End Time</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="time_end" type="time" name="Time_End" width="313.5">
			</div>
			<div id="Group_22">
				<div id="Location">
					<span>Latitude</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="lat" type="text" name="Lat">
				<div id="Location_2">
					<span>Longitude</span><span style="color:red;font-size:25px;">*</span>
				</div>
				<input id="lon" type="text" name="Lon">
			</div>
	
			<div id="mapicon">
				<img id="mapIcon" src="img/map_icon.png" onclick='on()'>
			</div>
			<div id="Group_25">
				<div id="Detailed_Description">
					<span>Description</span>
				</div>
	
				<textarea id ="Description" name="Description" rows="4" cols="100"></textarea>
				<br/><br/><br/>
				<span style="color:red;font-size:25px;">required*</span>
			</div>
	
			<input type="image" id="submitButton" src="img/submit_button.png" width="180" height="42">
		</form>
	</div>

	<div id="overlay">
		<div id="map"></div>
	</div>
	
	
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCB_WPm3Y2eL3aSvs64KYGkDoQ_F4RYatE&language=en&callback=initMap"
	    async defer></script>
</body>
</html>