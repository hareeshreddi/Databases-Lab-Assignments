drop database if exists 25jan2018;
create database 25jan2018;
use 25jan2018
-- not null
-- primary key has automtically unique constraint 
CREATE TABLE ett
(
	course_id varchar(20) not null, 
	exam_date DATE not null,-- of form 2018-02-26
	start_time TIME not null,-- of form 14:00
	end_time TIME not null,-- of form 14:00
	primary key(course_id,exam_date,start_time)
);
CREATE TABLE cc
(
	course_id varchar(20) not null,-- assuming it has string of maximum length 20
	number_of_credits int unsigned default 0, -- cannot be negative
	primary key(course_id)
);
CREATE TABLE cswl
(
	serial_number int unsigned not null,-- cannot be negative
	roll_number int unsigned not null,-- cannot be negative
	name varchar(100) ,-- maximum length 100 and assuming can be null
	email varchar(100),-- maximum length 100 and assuming can be null
	course_id varchar(20) not null,-- maximum length 20
	primary key(roll_number,course_id)
);
-- droping temporary tables if they already exists 
drop table if exists ett_temp;
drop table if exists cc_temp;
drop table if exists cswl_temp;
CREATE TEMPORARY TABLE ett_temp
(
	course_id varchar(20) not null, 
	exam_date DATE not null,-- of form 2018-02-26
	start_time TIME not null,-- of form 14:00
	end_time TIME not null,-- of form 14:00
	primary key(course_id,exam_date,start_time)
);
CREATE TEMPORARY TABLE cc_temp
(
	course_id varchar(20) not null,-- assuming it has string of maximum length 20
	number_of_credits int unsigned default 0, -- cannot be negative
	primary key(course_id)
);
CREATE TEMPORARY TABLE cswl_temp
(
	serial_number int unsigned not null,-- cannot be negative
	roll_number int unsigned not null,-- cannot be negative
	name varchar(100) ,-- maximum length 100 and assuming can be null
	email varchar(100),-- maximum length 100 and assuming can be null
	course_id varchar(20) not null,-- maximum length 20
	primary key(roll_number,course_id)
);
-- cloning the 3 tables 
CREATE TABLE ett_clone like ett;
CREATE TABLE cc_clone like cc;
CREATE TABLE cswl_clone like cswl;

