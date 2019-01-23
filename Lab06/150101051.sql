drop database if exists 150101051_23feb2018;
create database 150101051_23feb2018;
use 150101051_23feb2018
-- not null
-- primary key has automtically unique constraint 
CREATE TABLE ett
(
	line_number int unsigned not null,
	course_id varchar(20) not null, 
	exam_date DATE not null,-- of form 2018-02-26
	start_time TIME not null,-- of form 14:00
	end_time TIME not null,-- of form 14:00
	primary key(course_id,exam_date,start_time)
);
CREATE TABLE cc
(
	course_id varchar(20) not null,-- assuming it has string of maximum length 20
	number_of_credits int unsigned not null default 0, -- cannot be negative
	primary key(course_id)
);
CREATE TABLE cwsl
(
	serial_number int unsigned not null,-- cannot be negative
	roll_number varchar(20) not null,-- some are having roll numbers of form X170104081 which is not an integer
	name varchar(100) ,-- maximum length 100 and assuming can be null
	email varchar(100),-- maximum length 100 and assuming can be null
	course_id varchar(20) not null,-- maximum length 20
	primary key(roll_number,course_id)
);
