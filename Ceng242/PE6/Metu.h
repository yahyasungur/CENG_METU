#ifndef __METU_H__
#define __METU_H__


#include "Course.h"
#include "Student.h"

//////////////////////////////////////////////////////
//    DO NOT CHANGE *PUBLIC PARTS* IN THIS FILE!    //
//////////////////////////////////////////////////////

/****************************************************/
/****                *** METU ***                ****/

class Metu {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Student;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;
	// You can add your own variables/methods here.

	vector<Student> students;
	vector<Course> courses;
	int course_index = 0;

	vector<vector<int>> seating_plan;
	int row_size = 0;
	int column_size = 0;

	void initialize_seating(int, int);
	pair<int,int> check_student(int id);
	void construct_seating();

	vector<pair<pair<int,int>,string>> cheating;

	Sophomore *sop = NULL;
	Junior *jun = NULL;
	Senior *sen= NULL;
	OpenCourse * open_course= NULL;

public:

	// Do NOT change the below part.
	Metu();
	~Metu();

	Student& getStudent(int);
	void registerStudent(Student*);
	void registerCourse(const Course&);
	OpenCourse& openCourse(const Course&, string, int, vector<Freshman*>, vector<Sophomore*>, vector<Junior*>, vector<Senior*>);

	Sophomore* upgradeStudent(Freshman&);
	Junior* upgradeStudent(Sophomore&);
	Senior* upgradeStudent(Junior&);

	void setClassroomSize(int, int);
	void addCheatInfo(int, int, string);
	void printSeatingPlan();

};

#endif
