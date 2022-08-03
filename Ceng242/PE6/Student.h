#ifndef __STUDENT_H__
#define __STUDENT_H__


#include "Course.h"

//////////////////////////////////////////////////////
//    DO NOT CHANGE *PUBLIC PARTS* IN THIS FILE!    //
//////////////////////////////////////////////////////

enum Grade learnGrade(string course_name, int student_id);

/****************************************************/
/****               *** STUDENT ***              ****/
class Student {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Metu;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;

	int id;
	string fullname;
	string department;
	bool update;
	float gpa;

	vector<CourseInstance> courses_of_student;

	int graded_course_num = 0;
	// You can add your own variables/methods here.
	

protected:
	//Student();
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Student(int id, string fullname, string department);
	~Student();
	Student(const Student&);
	int getId() const;
	float getGPA() const;
	vector<const CourseInstance*> listCourses() const;
	void gradeCourse(const OpenCourse& openCourse);
	void setUpgradeStatus();

};

/****************************************************/
/****              *** FRESHMAN ***              ****/
class Freshman : public Student {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Metu;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;
	// You can add your own variables/methods here.

protected:
	//Freshman();
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Freshman(int id, string fullname, string department);
	~Freshman();
	Freshman(const Freshman&);
	bool addCourse(const OpenCourse&);
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.

};

/****************************************************/
/****              *** SOPHOMORE ***             ****/
class Sophomore : public Freshman {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Metu;
	friend class Freshman;
	friend class Junior;
	friend class Senior;
	// You can add your own variables/methods here.

	bool internship_1;
	bool internship_2;

protected:
	//Sophomore();
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Sophomore(int id, string fullname, string department);
	Sophomore(const Freshman&);
	~Sophomore();
	Sophomore(const Sophomore&);
	void doAnInternship(int);
	bool getInternshipStatus(int);
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};

/****************************************************/
/****                *** JUNIOR ***              ****/
class Junior : public Sophomore {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Metu;
	friend class Freshman;
	friend class Sophomore;
	friend class Senior;
	// You can add your own variables/methods here.

	bool internship_1;
	bool internship_2;
protected:
	//Junior();
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Junior(int, string, string);
	Junior(const Sophomore&);
	~Junior();
	Junior(const Junior&);
	void selectElectiveCourse();
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};

/****************************************************/
/****                *** SENIOR ***              ****/
class Senior : public Junior {

private:
	friend class Course;
	friend class CourseInstance;
	friend class OpenCourse;
	friend class Metu;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	// You can add your own variables/methods here.

	bool internship_1;
	bool internship_2;
protected:
	//Senior();
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Senior(int, string, string);
	Senior(const Junior&);
	~Senior();
	Senior(const Senior&);
	bool graduate();
	void printTranscript() const;	// Do not confuse. This will be implemented by the PE admin.
};

#endif
