
# Work Report
# Database

## Name: <ins> Yi Zhuang </ins>

## Features:
<pre>
- Implemented:
  - SQL class that reads and runs commands to write or retrieve information from binary files
  - Commands that the database can take:
    - Create/Make table
    - Insert into
    - Write
    - Print
    - Select 

<br>
- Partly implemented:
  - Run function for user interface
  - Drop table
</pre>

# **Brief Overview**
https://user-images.githubusercontent.com/93494138/206886725-cc2edd1b-9ee6-4a1d-8d47-24087bb42ca6.mp4


<br/><br/>

# test.cpp output:
<pre>
<br/><br/>

//****************************************************************************
//              CREATE AND INSERT
//****************************************************************************

//---- employee table ----------
[0] make table employee fields  last,           first,                  dep
sql::run_command: make



SQL: DONE. 

[1] insert into employee values Blow,           Joe,                    CS
sql::run: inserted.



SQL: DONE. 

[2] insert into employee values Johnson,        "Jimmy",                Chemistry
sql::run: inserted.



SQL: DONE. 

[3] insert into employee values Yang,           Bo,                     CS
sql::run: inserted.



SQL: DONE. 

[4] insert into employee values "Jackson",      Billy,                  Math
sql::run: inserted.



SQL: DONE. 

[5] insert into employee values Johnson,        Billy,                  "Phys Ed"
sql::run: inserted.



SQL: DONE. 

[6] insert into employee values "Van Gogh",     "Jim Bob",              "Phys Ed"
sql::run: inserted.



SQL: DONE. 


[7] select * from employee 
There is no condition 
                  records                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS
                        3                  Jackson                    Billy                     Math
                        4                  Johnson                    Billy                  Phys Ed
                        5                 Van Gogh                  Jim Bob                  Phys Ed


SQL: DONE. 


//----- student table ----------
[8] make table student fields   fname,                  lname,          major,                          age
sql::run_command: make



SQL: DONE. 

[9] insert into student values  Flo,                    Yao,            CS,                             20
sql::run: inserted.



SQL: DONE. 

[10] insert into student values         "Flo",                  "Jackson",      Math,                           21
sql::run: inserted.



SQL: DONE. 

[11] insert into student values         Calvin,                 Woo,            Physics,                        22
sql::run: inserted.



SQL: DONE. 

[12] insert into student values         "Anna Grace",   "Del Rio",      CS,                                     22
sql::run: inserted.



SQL: DONE. 

[13] select * from student
There is no condition 
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22
                        3               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 




//****************************************************************************
//              SIMPLE SELECT 
//****************************************************************************

[14] select * from student
There is no condition 
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22
                        3               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 


//------- simple strings -------------------
[15] select * from student where lname = Jackson

Table name: student2, records: 0
                  records                    fname                    lname                    major                      age

                        0                      Flo                  Jackson                     Math                       21


SQL: DONE. 


//----- quoted strings ---------------------
[16] select * from student where lname = "Del Rio"

Table name: student3, records: 0
                  records                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 


//-------- non-existing string ------------------
[17] select * from student where lname = "Does Not Exist"

Table name: student4, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 


//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[18] select * from student where lname > Yang

Table name: student5, records: 0
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20


SQL: DONE. 



//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . . 
[19] select * from student where age > 50

Table name: student6, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 


//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . . . .  
[20] select * from student where age  > 53

Table name: student7, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 


//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . . 
[21] select * from student where age > 54

Table name: student8, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 


//.................
//:Greater Equal  :
//.................
[22] select * from student where lname >= Yang

Table name: student9, records: 0
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20


SQL: DONE. 


//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . . 
[23] select * from employee where last >= Jack

Table name: employee10, records: 5
                  records                     last                    first                      dep

                        0                  Jackson                    Billy                     Math                       20
                        1                  Johnson                    Jimmy                Chemistry                       20
                        2                  Johnson                    Billy                  Phys Ed                       20
                        3                 Van Gogh                  Jim Bob                  Phys Ed                       20
                        4                     Yang                       Bo                       CS                       20


SQL: DONE. 



//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . . 
[24] select * from student where lname < Jackson

Table name: student11, records: 0
                  records                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 


//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[25] select * from student where age  < 20

Table name: student12, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 



//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . . 

[26] select * from student where age  < 19

Table name: student13, records: 0
                  records                    fname                    lname                    major                      age



SQL: DONE. 



//.................
//:Less Equal     :
//.................

[27] select * from student where lname <= Smith

Table name: student14, records: 2
                  records                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22
                        1                      Flo                  Jackson                     Math                       21


SQL: DONE. 


//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . . 
[28] select * from employee where last <= Peach

Table name: employee15, records: 4
                  records                     last                    first                      dep

                        0                     Blow                      Joe                       CS                       21
                        1                  Jackson                    Billy                     Math                       21
                        2                  Johnson                    Jimmy                Chemistry                       21
                        3                  Johnson                    Billy                  Phys Ed                       21


SQL: DONE. 


//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[29] select * from student where fname = "Flo" and lname = "Yao"

Table name: student16, records: 0
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20


SQL: DONE. 



//.................
//:OR            :
//.................
[30] select * from student where fname = Flo or lname = Jackson

Table name: student17, records: 2
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21


SQL: DONE. 



//.................
//:OR AND         :
//.................
[31] select * from student where fname = Flo or major = CS and age <= 23

Table name: student18, records: 3
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 



//.................
//:AND OR AND     :
//.................

[32] select * from student where age <30 and major=CS or major = Physics and lname = Jackson

Table name: student19, records: 2
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 



//.................
//:OR AND OR      :
//.................

[33] select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson 

Table name: student20, records: 3
                  records                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2               Anna Grace                  Del Rio                       CS                       22


SQL: DONE. 


<br/><br/>
</pre>


