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
	<%  //String parameter=request.getParameter("activityID");
		//int activityID=Integer.parseInt(parameter);
		ArrayList<Activity> temp = Helper.getAllActivities(); // CHANGE TO getActivityById();
		String tempName="";
		String tempDescription="";
		float templat=0;
		float templon=0;
		String tempStart="";
		String tempEnd="";
		for(int i=0;i<temp.size();i++){
			if(true)//ajust it after setup all links which should be (temp.get(i).getActivityID()==activityID)
			{
				tempName=temp.get(i).getTitle();
				tempDescription =temp.get(i).getDescription();
				templat=temp.get(i).getLat();
				templon=temp.get(i).getLon();
				tempStart=temp.get(i).getStartDate()+" "+temp.get(i).getStartTime();
				tempEnd=temp.get(i).getEndDate()+" "+temp.get(i).getEndTime();
				
				break;
			}
		}
	
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
		    	var marker=new google.maps.Marker({
    		        position: new google.maps.LatLng('<%=templat%>', '<%=templon%>'),
    		        map: map
    		      });
		    	
		        map = new google.maps.Map(document.getElementById('map'), {
		          center: myLatlng,
		          zoom: 16
		        });
		
		        google.maps.event.addListener(map,'click', function(event) {
		            off();
		            });
		      }
		</script>
</head>
<body>

<div id="Detail_Page">
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
		
		<div id="Group_30">

			<div id="EventIcon">
				<img id="EventPic" src="img/event_icon7.png">
			</div>
			<div id="Event_Name">
				<span><%=tempName %>Name</span>
			</div>
			<div id="DATE__TIME__Location_">
				<div id="startInfo">Start: <%=tempStart %></div>
				<div id="endInfo">End: <%=tempEnd %></div>
				<div id="locationInfo">Location:</div>
				<div id="descriptionTitle">Description:</div>
				<div id="descriptionInfo">test description<%=tempDescription %></div>
			</div>
			<div id="Initiator_">
				<span style="">Initiator</span>
			</div>
			<div id="Interested">
				<span>Interested</span>
			</div>
			<div id="initiatorPic">
				<a href="profile.jsp"><img id="initiatorProfile" src="img/initiator.png" width="100%" height="100%"></a>
			</div>
			<div id="User1Pic">
				<a href="profile.jsp"><img id="User1Profile" src="img/interested1.png" width="100%" height="100%"></a>
			</div>
			<div id="User2Pic">
				<a href="profile.jsp"><img id="User2Profile" src="img/interested2.png" width="100%" height="100%"></a>
			</div>
			<div id="User3Pic">
				<a href="profile.jsp"><img id="User3profile" src="img/interested3.png" width="100%" height="100%"></a>
			</div>
			
		</div>
	</div>
	<div id="map_button"><img src='img/map_icon.png' alt='GoogleIcon.png' id='google' onclick='on()'></div>
</div>
<div id="overlay" onclick="off()">
			<div id="map"></div>
		</div>
<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCB_WPm3Y2eL3aSvs64KYGkDoQ_F4RYatE&language=en&callback=initMap"
    async defer></script>
</body>
</html>