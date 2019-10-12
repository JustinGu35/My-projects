package utility;

import java.sql.*;

public class DBConnection {
	private Connection con = null;
	private Statement st = null;
	private ResultSet rs =null;
	
	private String url = "jdbc:mysql://localhost:3306/CSCI201L_FinalProject";	
	private String user = "root";//username
	private String password = "root";//password
	
	public DBConnection() {
		
	}
	
	//Open Connection
	public void getConnection(){
		try {
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection(url, user, password);   
			System.out.println(con);
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	//Query Data
	public ResultSet executeQuery(String sql) {
		if (con == null) {
			getConnection();
		}
		try {
			st = con.createStatement();
			rs = st.executeQuery(sql);
		}catch (Exception e) {
			e.printStackTrace();
		}
		return rs;
	}
	
	//Update data
	
	public boolean executeUpdate(String sql) {
		if (con == null) {
			getConnection();
		}
		try {
			Statement upst = con.createStatement();
			upst.execute(sql);
			return true;
		}catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}	
	
	//Close Connection
	
	public void closeConnection() {
		try {
			if (rs != null) {
				rs.close();
				rs =null;
			}
			if (st != null) {
				st.close();
				st =null;
			}
			if (con != null) {
				con.close();
				con =null;
			}
		}catch (Exception e) {
			e.printStackTrace();
		}finally {
			con =null;
		}
	}
}
