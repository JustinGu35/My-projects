package utility;

public class User {
	private int userID;
	private String email;
	private String fname;
	private String lname;
	private String phone;
	private String profilepic;
	private int gradyear;
	private String major;
	
	private DBConnection db;
	
	public User(int userId, String email, String fname, String lname, String phone, String profilepic, int gradyear, String major){
		this.userID = userId;
		this.email = email;
		this.fname = fname;
		this.lname = lname;
		this.phone = phone;
		this.profilepic = profilepic;
		this.gradyear = gradyear;
		this.major = major;
		
		this.db = new DBConnection();
		db.getConnection();
	}
	
	public int getUserID() {
		return userID;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
		db.executeUpdate("UPDATE User SET email = \"" + email + "\" WHERE userID = " + this.userID + ";");
	}
	public String getFname() {
		return fname;
	}
	public void setFname(String fname) {
		this.fname = fname;
		db.executeUpdate("UPDATE User SET fname = \"" + fname + "\" WHERE userID = " + this.userID + ";");
	}
	public String getLname() {
		return lname;
	}
	public void setLname(String lname) {
		this.lname = lname;
		db.executeUpdate("UPDATE User SET lname = \"" + lname + "\" WHERE userID = " + this.userID + ";");
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
		db.executeUpdate("UPDATE User SET phone = \"" + phone + "\" WHERE userID = " + this.userID + ";");
	}
	public String getProfilepic() {
		return profilepic;
	}
	public void setProfilepic(String profilepic) {
		this.profilepic = profilepic;
		db.executeUpdate("UPDATE User SET profilepic = \"" + profilepic + "\" WHERE userID = " + this.userID + ";");
	}
	public int getGradyear() {
		return gradyear;
	}
	public void setGradyear(int gradyear) {
		this.gradyear = gradyear;
		db.executeUpdate("UPDATE User SET gradyear = \"" + gradyear + "\" WHERE userID = " + this.userID + ";");
	}
	public String getMajor() {
		return major;
	}
	public void setMajor(String major) {
		this.major = major;
		db.executeUpdate("UPDATE User SET major = \"" + major + "\" WHERE userID = " + this.userID + ";");
	}

	
	
}
