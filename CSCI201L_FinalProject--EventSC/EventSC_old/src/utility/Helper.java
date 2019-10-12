package utility;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

public class Helper {
	
	public static Activity getActivityById(int activityID) {
		try {
			DBConnection db = new DBConnection();
			db.getConnection();
			ResultSet rs = db.executeQuery("SELECT * FROM Activities WHERE activityID=" + activityID + ";");
			if (rs.next()) {
				int userID = rs.getInt("userID");
				String title = rs.getString("title");
				String description = rs.getString("description");
				float lat = rs.getFloat("lat");
				float lon = rs.getFloat("lon");
				String startDate = rs.getString("startDate");
				String startTime = rs.getString("startTime");
				String endDate = rs.getString("endDate");
				String endTime = rs.getString("endTime");
				
				return new Activity(activityID, userID, title, description, lat, lon,
									startDate, startTime, endDate, endTime, "", "");
			}
			
		} catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}
		
		return new Activity(0,0,"","",0,0,"","","","","","");
	}
	
	public static User getUserById(int userID) {
		try {
			DBConnection db = new DBConnection();
			db.getConnection();
			ResultSet rs = db.executeQuery("SELECT * FROM Users WHERE userID=" + userID + ";");
			if (rs.next()) {
				String email = rs.getString("email");
				String fname = rs.getString("fname");
				String lname = rs.getString("lname");
				String phone = rs.getString("phone");
				int gradyear = rs.getInt("gradyear");
				String major = rs.getString("major");
				
				return new User(userID, email, fname, lname,
								phone, "", gradyear, major);
			}
			
		} catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}
		
		return new User(0,"","","","","",0,"");
	}
	
	public static HashMap<Integer, Coordinate> getLocations() {
		HashMap<Integer, Coordinate> coords = new HashMap<Integer, Coordinate>();
		try {
			DBConnection db = new DBConnection();
			db.getConnection();
			ResultSet rs = db.executeQuery("SELECT activityID, lat, lon FROM Activities;");
			while (rs.next()) {
				int activityID = rs.getInt("activityID");
				float lat = rs.getFloat("lat");
				float lon = rs.getFloat("lon");
				
				Coordinate coord = new Coordinate(lat, lon);
				coords.put(activityID, coord);
			}
			
		} catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}
		
		return coords;
	}
	
}
