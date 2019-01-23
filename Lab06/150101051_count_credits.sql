
delimiter //
drop procedure if exists count_credits; -- if the procedure already exists

create procedure count_credits()
BLOCK1:begin
	declare counter int ; -- counter denotes total credits registred
	declare temporary_rollnumber varchar(20);
	declare student_rollnumber varchar(20); -- local variable
	declare student_name varchar(100); -- local variable
	declare counter2 int default 0; -- is helpful to count no.of students having registred credits more than 40

	declare done int default 0;
	-- Firstly I declared a cursor for selecting all the distinct roll numbers along with their names from cwsl table
	declare cursor_1 cursor for select distinct roll_number,name from cwsl;
	declare continue handler for not found set done = 1; -- Declared handler for 1st cursor

	open cursor_1;
	Loop_1 : loop -- Loop_1 starts here
		fetch cursor_1 into student_rollnumber,student_name; -- fetch each rollnumber and name one by one

		if done then 
			leave Loop_1; -- Loop_1 leave statement
			end if;

		select X.roll_number,sum(Y.number_of_credits) into temporary_rollnumber, counter from cwsl X, cc Y where 
		X.course_id = Y.course_id AND X.roll_number = student_rollnumber;   

		if(counter > 40) then -- This prints if the student has total credits registred are more than 40
			set counter2 = counter2 + 1;
			select temporary_rollnumber as Rollnumber, student_name as Name, counter as Total_Credits_Registred;
		end if;
	end loop Loop_1; -- Loop_1 ends here
	-- select counter2; -- uncomment to print total count of students who registred for more than 40 credits,here I got 1082 entries
	close cursor_1; -- closing the cursor_1
end BLOCK1;//

delimiter ; -- now delimiter is changed back to ;
call count_credits; -- call the stored procedure count_credits 