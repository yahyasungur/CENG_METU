#include "Student.h"
#include <algorithm>
#include<bits/stdc++.h>

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****               *** STUDENT ***              ****/
vector<const CourseInstance*> crses;
/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
*/
Student::Student(int _id, string _fullname, string _department) {
	// TODO
   this->fullname = _fullname;
   this->department = _department;
   this->id = _id;
   this->update = false;
   this->gpa = 100.0;

   this->courses_of_student.clear();
   this->courses_of_student.shrink_to_fit();
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current student.
*/
Student::~Student() {
	// TODO
   for (int i = 0; (unsigned)i < this->courses_of_student.size(); i++){
      this->courses_of_student[i].~CourseInstance();
   }
   this->courses_of_student.clear();

   for (int i = 0; (unsigned)i < crses.size(); i++){
      delete crses[i];
   }
   
}

/* Copy constructor : It totally applies shallow copy.
*/
Student::Student(const Student& student) {
	// TODO
   this->department = student.department;
   this->fullname = student.fullname;
   this->gpa = student.gpa;
   this->update = student.update;
   this->id = student.id;

   for (int i = 0; (unsigned)i < student.courses_of_student.size(); i++){
      this->courses_of_student.push_back(student.courses_of_student[i]);
   }

}

/* This method returns the id of the student.
*/
int Student::getId() const {
	// TODO
   return this->id;
}

/* This method returns the GPA of the student.
*/
float Student::getGPA() const {
	// TODO
   return this->gpa;
}

/* This method returns the courses taken by
   this student. Note that the grade taken in that
   course is not important. You should return
   all the passed and failed courses.
*/

vector<const CourseInstance*> Student::listCourses() const {
	// TODO
   
   for (int i = 0; (unsigned)i < this->courses_of_student.size() ; i++){
      crses.push_back(&(this->courses_of_student[i]));
   }
   
   return crses;
}

/* This method grades the given course for this student.
   In order to grade the course, learnGrade() method is 
   called. learnGrade() method is already implemented by 
   the HW admin, yet it is invisible to you. You call it
   by giving the course name as the first argument and
   student id as the second argument. For instance;
   learnGrade("Programming Languages", 1234567);
   Then, you should save the grade returned by learnGrade().
   
   Also, after learning the grade, you should recalculate
   the GPA of the student in this method.
   GPA is a float value calculated by simply taking the 
   average of all the graded courses (The courses for which
   gradeCourse() method is called before or now).
*/

void Student::gradeCourse(const OpenCourse& openCourse) {
	// TODO
   
   Grade grade = learnGrade(openCourse.getName(), this->id);
   this->gpa = ((this->gpa)*(float)(this->graded_course_num) + grade) / (float)(this->graded_course_num + 1);

   this->graded_course_num++;
}

/* This method sets the upgrade information for the current
   student to true. You may not need this method, yet still
   it is defined in case that it may be beneficial later.
*/
void Student::setUpgradeStatus() {
	// TODO
   this->update = true;
}


/****************************************************/
/****              *** FRESHMAN ***              ****/
vector<const Course*> press;
/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to 
   carry the upgrade information and initalize it to 
   false. This may be needed in the other methods 
   later on.
*/
Freshman::Freshman(int id, string fullname, string department):Student(id, fullname, department) {
	// TODO
   this->id = id;
   this->fullname = fullname;
   this->department = department;
   this->gpa = 100.0;
   this->update = false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current freshman.
*/
Freshman::~Freshman() {
	// TODO
   for (int i = 0; (unsigned)i < this->courses_of_student.size(); i++){
      this->courses_of_student[i].~CourseInstance();
   }
   this->courses_of_student.clear();

   for (int i = 0; (unsigned)i < press.size(); i++){
      delete press[i];
   }
   
}

/* Copy constructor : It totally applies shallow copy.
*/
Freshman::Freshman(const Freshman& freshman):Student(freshman.id, freshman.fullname, freshman.department) {
	// TODO
   this->department = freshman.department;
   this->fullname = freshman.fullname;
   this->gpa = freshman.gpa;
   this->update = freshman.update;
   this->id = freshman.id;

   for (int i = 0; (unsigned)i < freshman.courses_of_student.size(); i++){
      this->courses_of_student.push_back(freshman.courses_of_student[i]);
   }
}

/* This method tries to add the given opencourse.
   In order to add, it just checks the prerequisites of the
   course is satisfied ot not. If all the prerequisites are
   satisfied (the prerequisite courses had been taken before),
   then it adds the course by constructiong a new CourseInstance
   object by using given OpenCourse object, then the newly
   created CourseInstance should be stored in an array of taken
   courses.
   If the course could be added successfuly, the method returns
   true. Otherwise (if there is at least one non-satisfied 
   prerequisite), it returns false.
*/

bool Freshman::addCourse(const OpenCourse& opencourse) {
	// TODO
   int elgible = 0; 
   
   press = opencourse.getPrerequisites();
   for (int i = 0; (unsigned)i < press.size(); i++){
      bool is_in = false;
      for (int j = 0; (unsigned)j < this->courses_of_student.size(); j++){
         if (this->courses_of_student[j].getName() == press[i]->getName()){
            is_in = true;
            break;
         }
      }
      
      if (is_in == true){
         elgible++;
      }
   }

   if ((unsigned)elgible == press.size()){
      // add course
      CourseInstance course_ins = CourseInstance(opencourse, *this);
      this->courses_of_student.push_back(course_ins);
      return true;
   }
   
   return false;
}

/****************************************************/
/****              *** SOPHOMORE ***             ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
*/
Sophomore::Sophomore(int id, string fullname, string department):Freshman(id, fullname, department) {
	// TODO
   this->id = id;
   this->fullname = fullname;
   this->department = department;
   this->gpa = 100.0;
   this->internship_1 = false;
   this->internship_2 = false;
}

/* Constructor : initializes the derived members of the
   Freshman class with the one given as first parameter.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
 */
Sophomore::Sophomore(const Freshman& freshman):Freshman(freshman) {
	// TODO
   this->internship_1 = false;
   this->internship_2 = false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current sophomore.
*/
Sophomore::~Sophomore() {
	// TODO
   for (int i = 0; (unsigned)i < this->courses_of_student.size(); i++){
      this->courses_of_student[i].~CourseInstance();
   }
   this->courses_of_student.clear();
}

/* Copy constructor : It totally applies shallow copy.
*/
Sophomore::Sophomore(const Sophomore& sophomore):Freshman(sophomore.id, sophomore.fullname, sophomore.department)  {
	// TODO
   this->department = sophomore.department;
   this->fullname = sophomore.fullname;
   this->gpa = sophomore.gpa;
   this->update = sophomore.update;
   this->id = sophomore.id;
   this->internship_1 = sophomore.internship_1;
   this->internship_2 = sophomore.internship_2;

   for (int i = 0; (unsigned)i < sophomore.courses_of_student.size(); i++){
      this->courses_of_student.push_back(sophomore.courses_of_student[i]);
   }
}

/* This method grades the internship with the given id
   (1 or 2).
   In order to grade the internship, learnGrade() method 
   is called. learnGrade() method is already implemented 
   by the HW admin, yet it is invisible to you. You call 
   it by giving the internship name as the first argument 
   and student id as the second argument. For instance;
   learnGrade("INTERNSHIP-1", 1234567); or
	learnGrade("INTERNSHIP-2", 1234567);
   If the grade returned by learnGrade() method is greater
   than or equal to DD, then restore the value of the 
   corresponding internship variable as true, else leave it
   as false.
*/
void Sophomore::doAnInternship(int intership_no) {
	// TODO
   string int_name;
   if(intership_no == 1){
      int_name = "INTERNSHIP-1";
   }
   else{
      int_name = "INTERNSHIP-2";
   }
   
   if (DD <= learnGrade(int_name, this->id)){
      switch (intership_no){
      case 1:
         this->internship_1 = true;
         break;
      
      case 2:
         this->internship_2 = true;
         break;
      }
   }
   
}

/* This method returns the status of the internship with
   the given id (1 or 2). The status is the fact that 
   it is completed successfully or not (true or false, 
   respectively).
*/
bool Sophomore::getInternshipStatus(int intership_no) {
	// TODO
   switch (intership_no){
      case 1:
         return this->internship_1;
         break;
      
      case 2:
         return this->internship_2;
         break;
   }

   return false;
}

/****************************************************/
/*                                                  */
/*           IT IS ENOUGH TO IMPLEMENT              */
/*    JUST CONSTRUCTORs, DESTRUCTOR & COPY CONS.    */
/*        FOR THE CLASS JUNIOR and SENIOR           */
/*     SIMILAR TO CLASS FRESHMAN and SOPHOMORE.     */
/*                                                  */
/*     JUNIOR and SENIOR OBJECTS MAY BE DEFINED     */
/*     IN TESTS, YET selectElectiveCourse() and     */ 
/*        graduate() METHOD WILL NOT BE USED.       */
/*                                                  */
/****************************************************/


/****************************************************/
/****                *** JUNIOR ***              ****/

Junior::Junior(int id, string fullname, string department):Sophomore(id, fullname, department) {
	// TODO
   this->id = id;
   this->fullname = fullname;
   this->department = department;
   this->gpa = 100.0;
   this->internship_1 = false;
   this->internship_2 = false;
}

Junior::Junior(const Sophomore& sophomore):Sophomore(sophomore) {
	// TODO
   this->internship_1 = false;
   this->internship_2 = false;
}

Junior::~Junior() {
	// TODO
   for (int i = 0; (unsigned)i < this->courses_of_student.size(); i++){
      this->courses_of_student[i].~CourseInstance();
   }
   this->courses_of_student.clear();
}

Junior::Junior(const Junior& junior):Sophomore(junior.id, junior.fullname, junior.department) {
	// TODO
   this->department = junior.department;
   this->fullname = junior.fullname;
   this->gpa = junior.gpa;
   this->update = junior.update;
   this->id = junior.id;
   this->internship_1 = junior.internship_1;
   this->internship_2 = junior.internship_2;

   for (int i = 0; (unsigned)i < junior.courses_of_student.size(); i++){
      this->courses_of_student.push_back(junior.courses_of_student[i]);
   }
}

void Junior::selectElectiveCourse() {
	// LEAVE EMPTY
}

/****************************************************/
/****                *** SENIOR ***              ****/

Senior::Senior(int id, string fullname, string department):Junior(id, fullname, department) {
	// TODO
   this->id = id;
   this->fullname = fullname;
   this->department = department;
   this->gpa = 100.0;
   this->internship_1 = false;
   this->internship_2 = false;
}

Senior::Senior(const Junior& junior):Junior(junior) {
	// TODO
   this->internship_1 = false;
   this->internship_2 = false;
}

Senior::~Senior() {
	// TODO
   for (int i = 0; (unsigned)i < this->courses_of_student.size(); i++){
      this->courses_of_student[i].~CourseInstance();
   }
   this->courses_of_student.clear();
}

Senior::Senior(const Senior& senior):Junior(senior.id, senior.fullname, senior.department) {
	// TODO
   this->department = senior.department;
   this->fullname = senior.fullname;
   this->gpa = senior.gpa;
   this->update = senior.update;
   this->id = senior.id;
   this->internship_1 = senior.internship_1;
   this->internship_2 = senior.internship_2;

   for (int i = 0; (unsigned)i < senior.courses_of_student.size(); i++){
      this->courses_of_student.push_back(senior.courses_of_student[i]);
   }
}

bool Senior::graduate() {
	// LEAVE EMPTY
	return true;
}

