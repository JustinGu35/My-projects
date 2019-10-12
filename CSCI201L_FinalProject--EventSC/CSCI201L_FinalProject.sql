DROP DATABASE IF EXISTS CSCI201L_FinalProject;

CREATE DATABASE CSCI201L_FinalProject;
USE CSCI201L_FinalProject;

CREATE TABLE Users (
	userID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,
    email VARCHAR(45) NOT NULL,
    passHash VARCHAR(45) NOT NULL,
    fname VARCHAR(45),
    lname VARCHAR(45),
    phone VARCHAR(45),
    profilepic VARCHAR(45),
    gradyear int(4),
    major VARCHAR(45)
);

CREATE TABLE Activities (
	activityID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,
    userID INT(11) NOT NULL,
    title VARCHAR(45),
    description VARCHAR(300),
    lat FLOAT(10,6), -- xxxx.xxxxxx
    lon FLOAT(10,6), -- xxxx.xxxxxx
    startDate VARCHAR(10), -- YYYY-MM-DD
    startTime VARCHAR(5), -- HH:MM
    endDate VARCHAR(10), -- YYYY-MM-DD
    endTime VARCHAR(6), -- HH:MM
    timeCreated TIMESTAMP,
    picture VARCHAR(45), -- image path
    FOREIGN KEY(userID) REFERENCES Users(userID)
);

CREATE TABLE Comments (
	commentID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,
    userID INT(11) NOT NULL,
    activityID INT(11) NOT NULL,
    content VARCHAR(200),
    timeCreated TIMESTAMP,
    FOREIGN KEY(userID) REFERENCES Users(userID),
    FOREIGN KEY(activityID) REFERENCES Activities(activityID)
);

INSERT INTO Users (email,passHash,fname,lname,phone,profilepic,gradyear,major)
 VALUES	("runshi@usc.edu", "257227","Justin","Gu",2138087452,"img/initiator.png",2021,"CSGM"),
		("aadani@usc.edu", "257227","Arav","Adani",2138087452,"img/interested1.png",2022,"CSCI"),
		("yunbao@usc.edu", "257227","Yun","Bao",2138087452,"img/interested2.png",2021,"PSYC"),
		("tianhual@usc.edu", "257227","Tianhua","Lyu",2138087452,"img/interested3.png",2021,"CECS"),
        ("kevinyya@usc.edu", "257227","Kevin","Yan",2138087452,"img/interested3.png",2022,"CSCI");
                    

INSERT INTO Activities ( userID,title,description,lat,lon,startDate,startTime,endDate,endTime,picture)
 VALUES	(1,"Team Meeting", "Coding the final PROJECT", 34.018798,-118.281716,"2019-06-08","15:34","2019-06-10","02:00","img/event_icon1.png"),
		(2,"CSCI201 graduation party", "Please have fun with Prof. Miller at the end of class", 34.021221,-118.284189,"2019-06-11","10:00","2019-06-11","13:50","img/event_icon3.png"),
		(3,"Octopus Party", "Please have fun with Arav and our friends from the Ocean", 34.020946,-118.283154,"2019-06-01","00:00","2019-06-13","23:00","img/event_icon7.png"),
		(4,"Hotpot dinner At Leavey", "Enjoy free hotpot brought by Uniboil!", 34.021693,-118.282792,"2019-07-08","17:00","2019-07-08","20:00","img/event_icon4.png"),
		(5,"Multi-Threading competition in YOUR HEART", "Compete with students from UCLA in SAL, take your chance to show our power", 34.01953,-118.289527,"2019-09-01","15:00","2019-09-03","15:00","img/event_icon5.png");