-- KINDLY WAIT FOR  1 MINUTE DURING EXECUTION TO PRINT ALL THE POSSIBILITIES

delimiter // -- changed the delimiter to //

drop procedure if exists tt_violation//
create procedure tt_violation()
begin 

-- I declared all the local variables required which I will be using during fetching of variables
declare student_rollnumber varchar(20);
declare c_id_1 varchar(20); -- course id 1 for clashing
declare c_id_2 varchar(20); -- course id 2 for clashing
declare student_name varchar(100);

declare done_1 int default 0; -- done_1 for handling of 1st cursor


-- Firstly I will find all the clashing courses i.e. same exam_date and start_time
declare cursor_1 cursor for select distinct e1.course_id as cid1,e2.course_id as cid2 from ett as e1,ett as e2 where e1.course_id < e2.course_id 
and e1.exam_date = e2.exam_date and e1.start_time=e2.start_time;

declare continue handler for not found set done_1 = 1; -- Handler for 1st cursor

open cursor_1; -- First cursor opened

Loop_1: loop -- Loop_1 starts here

	fetch cursor_1 into c_id_1,c_id_2;
	if done_1 then 
		leave Loop_1; -- Loop_1 leave statement 
	end if; 
	BLOCK1 : begin -- ....................................BLOCK1 begins here
		declare done_2 int default 0; -- done_2 is for handling of 2nd cursor

-- Now, I will find all the students with exam time table clashes i.e. if any student is having time table clash in 2 distinct courses
		declare cursor_2 cursor for select  distinct cwsl1.roll_number,cwsl1.name from cwsl as cwsl1,cwsl as cwsl2 where cwsl1.roll_number=cwsl2.roll_number and 
		cwsl1.course_id=c_id_1 and cwsl2.course_id=c_id_2;

		declare continue handler for not found set done_2 = 1;-- Handler for 2nd cursor
		open cursor_2; -- Second cursor
			-- Loop_2 will 
			Loop_2: loop -- ....................Loop_2 starts here

				fetch cursor_2 into student_rollnumber,student_name;
				if done_2 then
					leave Loop_2;-- Loop_2 leave statement
				end if;
				-- SET @roll_number=student_rollnumber,@name=student_name,@clashing_course_id1=c_id_1,@clashing_course_id2=c_id_2;
				-- select @roll_number,@name,@clashing_course_id1,@clashing_course_id2;
				select student_rollnumber as Rollnumber,student_name as Name,c_id_1 as Clashing_Course_id1,c_id_2 as Clashing_Course_id2;
			end loop Loop_2; -- Loop_2 ends here
		close cursor_2;
	end BLOCK1; -- BLOCK1 ends here
end loop Loop_1; -- Loop_1 ends here
close cursor_1;
end//

delimiter ; -- now delimiter is changed back to ;
call tt_violation; -- call the stored procedure tt_violation
-- I got 17 total distinct clashes of course_credits for the given data  