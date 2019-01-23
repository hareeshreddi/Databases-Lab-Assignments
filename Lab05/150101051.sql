-- Submitted by Hareesh Reddi Roll Number:: 150101051
/*
	Assumptions::
		Tables and Entities-- Names followed/same as previous(4th) assignment conventions::
		1)Course
			a)course_id
			b)division
		2)Department
			a)department_id
			b)name
		3)Slot
			a)letter
			b)day
			c)start_time
			d)end_time
		4)Room
			a)room_no
			b)location
		5)ScheduledIn
			a)course_id
			b)division
			c)department_id
			d)letter
			e)day
			f)room
*/

-- First Answer(a)
-- course_ids which are in the room 2001, where clause was used
select DISTINCT course_id from ScheduledIn where room_no = '2001';

-- Second Answer(b)
-- course_ids which are in Slot C, where clause was used
select DISTINCT course_id from ScheduledIn where letter= 'C';

-- Third Answer(c)
-- division which is allotted to room L2 or L3, where clause with OR operator is used
select DISTINCT division from ScheduledIn where room_no = 'L2' OR room_no = 'L3';

-- Fourth Answer(d)
-- course_ids which are allotted to multiple rooms irrespective of division
-- I have used Cross Product operation b/n ScheduledIn tables X and Y and found the answer
select DISTINCT X.course_id from ScheduledIn X, ScheduledIn Y where X.course_id = Y.course_id AND X.room_no != Y.room_no;

-- Fifth Answer(e)
-- department names in which any of the course of the department have been allotted to room L1 or L2 or L3 or L4
-- Here a Nested Query was used and two tables i.e. Department and ScheduledIn were used 
select DISTINCT name from Department where department_id IN 
( select department_id from ScheduledIn where room_no = 'L1' OR room_no = 'L2' OR room_no = 'L3' OR room_no = 'L4' );

-- Sixth Answer(f)
-- department names which do not use L1 or L2 rooms, Nested Query was used along with 2 tables ScheduledIn and Department
select DISTINCT name from Department where department_id NOT IN
( select DISTINCT department_id from ScheduledIn where room_no = 'L1' OR room_no = 'L2' );

-- Seventh Answer(g)
-- department names which have utilized all the slots, 3 tables i.e. ScheduledIn,Department and Slot were used
select DISTINCT DEPT.name from Department as DEPT where NOT EXISTS 
    ( select * from Slot as SLOT where NOT EXISTS
    	  ( select * from ScheduledIn as SCH where DEPT.department_id = SCH.department_id AND SCH.letter = SLOT.letter ));

-- Eighth Answer(h)
-- number of courses the slot was assigned is represented by count
select letter , COUNT(DISTINCT course_id) as count from ScheduledIn group by letter order by count ASC;

-- Ninth Answer(i)
-- number of courses the room was assigned is represented by count
-- The order by keyword sorts the records in ascending order by default hence DESC is mentioned based on value of count
select room_no , COUNT(DISTINCT course_id) as count from ScheduledIn group by room_no order by count DESC;

-- Tenth Answer(j)
-- slot name which was assigned minimum number of courses, ScheduledIn Table was used
-- ScheduledIn Table was used to perform the query 
select QQ.letter , QQ.CA from ( select letter , COUNT(DISTINCT course_id) as CA from ScheduledIn group by letter ) as QQ 
	where QQ.CA = 
		( select MIN(C.CB) as COURSES from ( select letter , COUNT(DISTINCT course_id) as CB from ScheduledIn group by letter ) as C );

-- Eleventh Answer(k)
-- The LIKE operator is used in a WHERE clause to search for a specified pattern in a column 
-- The percent sign(%) represents zero, one, or multiple characters
-- slots which were assigned to minor courses(ends with M)
select DISTINCT letter from ScheduledIn where course_id like '%M' order by letter ASC;

-- Twelth Answer(l)
-- Department name wise list the slots which were not used, 3 tables i.e. ScheduledIn,Department and Slot were used
select DISTINCT DEPT.name, SLOT.letter from Department as DEPT, Slot as SLOT where NOT EXISTS
	( select * from ScheduledIn as SCH where DEPT.department_id = SCH.department_id AND SCH.letter = SLOT.letter ) 
		order by DEPT.name ASC;