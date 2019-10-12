package utility;

public class Activity {
	private int activityID;
	private int userID;
	private String title;
	private String description;
	private float lat;
	private float lon;
	private String startDate;
	private String startTime;
	private String endDate;
	private String endTime;
	private String timeCreated;
	private String picture;
	
	public Activity() {
		
	}
	
	public Activity(int a, int u, String t, String d, float lt, float ln, 
					String sd, String st, String ed, String et, String tc, String p)
	{
		activityID = a;
		userID = u;
		title = t;
		description = d;
		lat = lt;
		lon = ln;
		startDate = sd;
		startTime = st;
		endDate = ed;
		endTime = et;
		timeCreated = tc;
		picture = p;
	}
	
	public int getActivityID()
	{
		return activityID;
	}
	public void setActivityID(int ID) {
		this.activityID = ID;
	}
	
	public int getUserID()
	{
		return userID;
	}
	public void setUserID(int ID) {
		this.userID = ID;
	}
	
	public String getTitle()
	{
		return title;
	}
	public void setTitle(String title)
	{
		this.title = title;
	}
	
	public String getDescription()
	{
		return description;
	}
	public void setDescription(String description)
	{
		this.description = description;
	}
	
	public float getLat()
	{
		return lat;
	}
	public void setLat(float lat)
	{
		this.lat = lat;
	}
	
	public float getLon()
	{
		return lon;
	}
	public void setLon(float lon)
	{
		this.lon = lon;
	}
	
	
	public String getStartDate()
	{
		return startDate;
	}
	public void setStartDate(String startDate)
	{
		this.startDate = startDate;
	}
	
	public String getStartTime()
	{
		return startTime;
	}
	public void setStartTime(String startTime)
	{
		this.startTime = startTime;
	}
	
	public String getEndDate()
	{
		return endDate;
	}
	public void setEndDate(String endDate)
	{
		this.endDate = endDate;
	}
	
	public String getEndTime()
	{
		return endTime;
	}
	public void setEndTime(String endTime)
	{
		this.endTime =  endTime;
	}
	
	public String getTimeCreated()
	{
		return timeCreated;
	}
	public void setTimeCreated(String timeCreated)
	{
		this.timeCreated =  timeCreated;
	}
	
	public String getPicture()
	{
		return picture;
	}
	public void setPicture(String picture)
	{
		this.picture = picture;
	}
	
}
