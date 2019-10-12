package servlets;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import utility.Helper;
import utility.User;

@WebServlet("/UpdateProfile")
public class UpdateProfile extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		int userID = Integer.parseInt(""+request.getSession().getAttribute("userID"));
		String fname = request.getParameter("fname");
		String lname = request.getParameter("lname");
		String email = request.getParameter("email");
		String phone = request.getParameter("phone");
		String major = request.getParameter("major");
		int gradyear = Integer.parseInt(request.getParameter("gradyear"));
		
		User usr = Helper.getUserByID(userID);
		usr.setFname(fname);
		
		usr.setLname(lname);

		usr.setEmail(email);

		usr.setPhone(phone);

		usr.setMajor(major);

		usr.setGradyear(gradyear);

	}

}
