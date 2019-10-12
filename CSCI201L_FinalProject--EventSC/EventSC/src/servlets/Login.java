package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import utility.DBConnection;

@WebServlet("/Login")
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
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
	
	private static boolean checkPassword(int userID, String password) {
		boolean ans = false;
		
		try {
			DBConnection db = new DBConnection();
			db.getConnection();
			ResultSet rs = db.executeQuery("SELECT passHash FROM Users WHERE userID = " + userID + ";");

			if (rs.next()) {
				String passHash = rs.getString("passHash");
				if (hashFunction(password).equals(passHash)) { // password matches
					ans = true;
				}
			}
			
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		}
		
		return ans;
	}
	
	public static int loginUserPass(String username, String password) {
		// returns:
		//		0 - successful login
		//		1 - valid username, bad password
		//		2 - unrecognized username
		
		int userID = getUserIDByUsername(username);
		
		if (userID == -1) return 2;
		if (!checkPassword(userID, password)) return 1;
		return 0;
	}
	
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		
		int status = loginUserPass(username, password);
		
		PrintWriter pw = response.getWriter();
		pw.println(status);
		pw.close();
		
		int userID = getUserIDByUsername(username);
		HttpSession session = request.getSession();
		session.setAttribute("userID", null);
		session.setAttribute("userID", userID);
	}

}
