#ifndef __COURSE_H__
#define __COURSE_H__


#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Student;

//////////////////////////////////////////////////////
//    DO NOT CHANGE *PUBLIC PARTS* IN THIS FILE!    //
//////////////////////////////////////////////////////

enum Grade {
	AA = 100,
	BA = 85,
	BB = 80,
	CB = 75,
	CC = 70,
	DC = 65,
	DD = 60,
	FF = 1,
	NA = 0
};

/****************************************************/
/****               *** COURSE ***               ****/
class Course {

private:
	friend class Student;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;
	friend class Metu;
	friend class CourseInstance;
	friend class OpenCourse;
	string name;
	vector<Course> prerequests;

	// You can add your own variables/methods here.

protected:
	void setName(string name){
		this->name = name;
	}
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	Course(string);
	~Course();
	Course(const Course&);

	void addPrerequisite(const Course&);
	const vector<const Course*> getPrerequisites() const;
	string getName() const;
	bool operator== (const Course&) const;

};


/****************************************************/
/****             *** OPEN COURSE ***            ****/
class OpenCourse : public Course {

private:
	//friend class Student;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;
	friend class Metu;
	friend class Course;
	friend class CourseInstance;

	string term;
	int course_index;
	int quota;
	vector<Student> students;
	// You can add your own variables/methods here.

protected:
	
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	OpenCourse(const Course&, string, int, int);
	~OpenCourse();
	OpenCourse(const OpenCourse&);
	const vector<int> showStudentList() const;
	void finalize();

};


/****************************************************/
/****          *** COURSE INSTANCE ***           ****/
class CourseInstance : public OpenCourse {

private:
	friend class Student;
	friend class Freshman;
	friend class Sophomore;
	friend class Junior;
	friend class Senior;
	friend class Metu;
	friend class Course;
	friend class OpenCourse;

	Grade grade;
	Student* student;
	// You can add your own variables/methods here.

protected:
	
	// You can add your own variables/methods here.

public:

	// Do NOT change the below part.
	CourseInstance(const OpenCourse&, Student&);
	~CourseInstance();
	void setGrade(enum Grade);
	enum Grade getGrade() const;

};

#endif

