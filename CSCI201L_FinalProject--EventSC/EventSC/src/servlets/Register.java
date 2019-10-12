package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.concurrent.ThreadLocalRandom;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.DBConnection;

@WebServlet("/Register")
public class Register extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
	private static ArrayList<String> profileImagePaths = new ArrayList<String>() {
		{
			add("img/initiator.png");
			add("img/interested1.png");
			add("img/interested2.png");
			add("img/interested3.png");
		}
	};
	
	public static int randomInt(int min, int max) {
		// min and max are inclusive
		return ThreadLocalRandom.current().nextInt(min, max + 1);
	}
	
	public static int getUserIDByUsername(String username) {
		int ans = -1;
		
		try {
			DBConnection db = new DBConnection();
			db.getConnection();
			ResultSet rs = db.executeQuery("SELECT userID FROM Users WHERE email = \"" + username + "\";");
			
			if (rs.next()) { // username exists
				ans = rs.getInt("userID");
			}
			
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}
		
		return ans;
	}
	
	private static String hashFunction(String str) {
		int hash = 7;
		for (int i = 0; i < str.length(); i++) {
		    hash = hash*31 + str.charAt(i);
		}
		return ""+hash;
	}
	
	private static void addUserDB(String username, String password) {
		DBConnection db = new DBConnection();
		db.getConnection();
		String randomImage = profileImagePaths.get(randomInt(0, profileImagePaths.size()-1));
		db.executeUpdate("INSERT INTO Users (email, passHash, profilepic, gradyear) VALUES (\"" + username + "\", \"" + hashFunction(password) + "\", \"" + randomImage + "\", " + Calendar.getInstance().get(Calendar.YEAR) + ");");
	}
	
	public static int registerUser(String username, String password, String passwordConf) {
		// returns:
		//		0 - successful registration
		//		1 - passwords don't match
		//		2 - username taken
		//		3 - empty fields
		//		4 - not a USC registered email
		
		if(username.length() == 0 
			|| password.length() == 0 
			|| passwordConf.length() == 0) return 3;
		
		if (!password.equals(passwordConf)) return 1;
		
		if(!username.endsWith("@usc.edu")) return 4;
		
		int userID = getUserIDByUsername(username);
		if (userID != -1) return 2;
		
		addUserDB(username, password);
		
		return 0;
	}
	
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String passwordConf = request.getParameter("passwordConf");
		
		int status = registerUser(username, password, passwordConf);
		
		PrintWriter pw = response.getWriter();
		pw.println(status);
		pw.close();
		
		int userID = getUserIDByUsername(username);
		HttpSession session = request.getSession();
		session.setAttribute("userID", null);
		session.setAttribute("userID", userID);
	}

}
