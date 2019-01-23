-- Submitted by Hareesh Reddi Roll Number:: 150101051
drop database if exists 09feb2018;
create database 09feb2018;
use 09feb2018
-- primary key constraint automatically enforces not NULL constraint so I did not mention not NULL condition again for primary key entities
-- there is an implicit not null constraint for every field listed in a Primary Key constraint.
-- ENUM does not enforce not null constraint so I added not NULL constraint where ever required i.e. if the attribute is not primary key

CREATE TABLE Course
(
	course_id varchar(10),
	division ENUM('I','II','III','IV','NA') default 'NA',-- takes values only... I, II, III, IV, NA
	primary key(course_id,division)-- enforces not null for course_id and division
);
CREATE TABLE Department
(
	department_id varchar(10),
	name varchar(40) not NULL,-- as name is string
	primary key(department_id)-- enforces not null for department_id
);
CREATE TABLE Slot
(
	letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1') ,
	day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'),
	start_time time not NULL,-- TIME type
	end_time time not NULL,-- TIME type 
	primary key(letter,day)-- enforces not null for letter and day
);
CREATE TABLE Room
(
	room_no varchar(25),
	location ENUM('Core-I', 'Core-II','Core-III', 'Core-IV', 'LH', 'Local') default 'Local',
	primary key(room_no)-- enforces not null for room_no
);
CREATE TABLE ScheduledIn
(
    -- the primary key fields from each of the above 4 tables are enough in ScheduledIn table
	course_id varchar(10),
	division ENUM('I','II','III','IV','NA') default 'NA',-- default value is NA
	department_id varchar(10),
	letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1'),
	day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'),
	room_no varchar(25),
	
-- Explanation of some key concepts:: 
	/* 1)The variables defined whih references to previous ones must have same type which was taken care 
	   2)the cascade keyword says that if any room_no row is deleted/updated from Room table,all ScheduledIn rows that refer to it 
		 are to be deleted/updated respectively as well,similarly I defined cascade option for remaining 3 referenced tables/relations
	   3)ScheduledIn is called Referencing relation and all the 4 other tables are called Referenced relations.
	   4)whenever a ScheduledIn tuple is inserted a check is made to see if the room_no is present in the Room relation,if the letter&day
		are in Slot relation,department_id is in Department relation,course_id&division are in Course relation,this work is done by
		foreign key constraint.*/

	primary key(course_id,division,department_id,letter,day,room_no),-- these 6 fields of Course Table are enough for the primary key field
		-- and it enforces not null for all the 6 attributes

		-- the foreign key constraint states that  every (course_id,division) value in ScheduledIn must also appear in Course
	foreign key(course_id,division) references Course(course_id,division) on delete cascade on update cascade,

		-- the foreign key constraint states that  every (department_id) value in ScheduledIn must also appear in Department
	foreign key(department_id) references Department(department_id) on delete cascade on update cascade,
	
		-- the foreign key constraint states that  every (letter,day) value in ScheduledIn must also appear in Slot
	foreign key(letter,day) references Slot(letter,day) on delete cascade on update cascade,
	
		-- the foreign key constraint states that  every (room_no) value in ScheduledIn must also appear in Room
	foreign key(room_no) references Room(room_no) on delete cascade on update cascade
);
		
	-- Following comments were used for my own reference while performing various operations
/*
insert into Room values('4','Other');
insert into Slot values('ss','ss','ll','jj');
insert into Slot values(NULL,'DD','SS','MM');
insert into Room values('333',' ');
insert into Room values('333','ll');
insert into Room values('33','ss');
insert into Course values('aa','aaa');
insert into Course values('aaa','I');
insert into Course values('aa','I');
insert into Course values('aa','I');
insert into Course values(NULL,'II');
insert into Course values(NULL,NULL);
insert into Course values('ggg',NULL);

LOAD DATA LOCAL INFILE  
 '/home/cse/Downloads/ASS4/Course.csv'
INTO TABLE Course
FIELDS TERMINATED BY ',' 

LINES TERMINATED BY '\n'
(course_id,division);

LOAD DATA LOCAL INFILE  
 '/home/cse/Downloads/ASS4/Department.csv'
INTO TABLE Department
FIELDS TERMINATED BY ',' 

LINES TERMINATED BY '\n'
(department_id,name);

LOAD DATA LOCAL INFILE  
 '/home/cse/Downloads/ASS4/Slot.csv'
INTO TABLE Slot 
FIELDS TERMINATED BY ',' 

LINES TERMINATED BY '\n'
(letter,day,start_time,end_time);

LOAD DATA LOCAL INFILE  
 '/home/cse/Downloads/ASS4/Room.csv'
INTO TABLE Room
FIELDS TERMINATED BY ',' 

LINES TERMINATED BY '\n'
(room_no,location);


LOAD DATA LOCAL INFILE  
 '/home/cse/Downloads/ASS4/ScheduledIn.csv'
INTO TABLE ScheduledIn
FIELDS TERMINATED BY ',' 

LINES TERMINATED BY '\n'
(course_id,division,department_id,letter,day,room_no);
*/
