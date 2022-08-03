#include "Course.h"
#include "Student.h"
#include "Metu.h"

/********** GLOBALS *********/
Metu* metu;

vector<Freshman*> freshmans;
vector<Sophomore*> sophomores;
vector<Junior*> juniors;
vector<Senior*> seniors;

vector<Course*> courses;
/********** ******* *********/

void defineStudents();
void defineCourses();

int main()
{
	metu = new Metu();
	defineStudents();
	defineCourses();

	OpenCourse& open_ceng111 = metu->openCourse(*courses[0], "2020-1", 10, freshmans, sophomores, juniors, seniors);
	for (int i=0; i<freshmans.size(); i++) {
		cout << "Student " << freshmans[i]->getId() << " has taken the followings:" << endl;
		for (int j=0; j<freshmans[i]->listCourses().size(); j++)
		  cout << freshmans[i]->listCourses()[j]->getName() << endl;
	}

    delete metu;

    return 0;
}

void defineStudents() {

	for (int i=1234567, j=0; j<1; i++, j++) {
		Freshman* freshman = new Freshman(i, "Freshman Human", "CENG");
    	metu->registerStudent(freshman);
    	freshmans.push_back(freshman);
	}
/*
	for (int i=2345671, j=0; j<10; i++, j++) {
		Sophomore* sophomore = new Sophomore(i, "Sophomore Human", "CENG");
    	metu->registerStudent(sophomore);
    	sophomores.push_back(sophomore);
	}

	for (int i=3456712, j=0; j<10; i++, j++) {
		Junior* junior = new Junior(i, "Junior Human", "CENG");
    	metu->registerStudent(junior);
    	juniors.push_back(junior);
	}

	for (int i=4567123, j=0; j<10; i++, j++) {
		Senior* senior = new Senior(i, "Senior Human", "CENG");
    	metu->registerStudent(senior);
    	seniors.push_back(senior);
	}
*/	
}

void defineCourses() {

	Course* ceng111 = new Course("Introduction To Computer Engineering Concepts");
    metu->registerCourse(*ceng111);
    courses.push_back(ceng111);

    Course* ceng140 = new Course("C Programming");
    metu->registerCourse(*ceng140);
    courses.push_back(ceng140);
/* 
	Course* math119 = new Course("Calculus with Analytic Geometry");
    metu->registerCourse(*math119);
    courses.push_back(math119);  

    Course* math120 = new Course("Calculus of Functions of Several Variables");
    math120->addPrerequisite(*math119);
    metu->registerCourse(*math120);
    courses.push_back(math120); 

    Course* math219 = new Course("Introduction To Differential Equations");
    math219->addPrerequisite(*math120);
    metu->registerCourse(*math219);
    courses.push_back(math219);   

    Course* math260 = new Course("Basic Linear Algebra");
    metu->registerCourse(*math260);
    courses.push_back(math260); 

    Course* ceng213 = new Course("Data Structures");
    ceng213->addPrerequisite(*ceng140);
    metu->registerCourse(*ceng213);
    courses.push_back(ceng213);

    Course* ceng223 = new Course("Discrete Computational Structures");
    metu->registerCourse(*ceng223);
    courses.push_back(ceng223);

    Course* ceng232 = new Course("Logic Design");
    ceng232->addPrerequisite(*ceng111);
    metu->registerCourse(*ceng232);
    courses.push_back(ceng232);

    Course* ceng242 = new Course("Programming Language Concepts");
    ceng242->addPrerequisite(*ceng111);
    ceng242->addPrerequisite(*ceng213);
    metu->registerCourse(*ceng242);
    courses.push_back(ceng242);

    Course* ceng280 = new Course("Formal Languages and Abstract Machines");
    ceng280->addPrerequisite(*ceng223);
    metu->registerCourse(*ceng280);
    courses.push_back(ceng280);

    Course* ceng315 = new Course("Algorithms");
    ceng315->addPrerequisite(*ceng213);
    metu->registerCourse(*ceng315);
    courses.push_back(ceng315);

    Course* ceng331 = new Course("Computer Organization");
    ceng331->addPrerequisite(*ceng232);
    metu->registerCourse(*ceng331);
    courses.push_back(ceng331);

    Course* ceng334 = new Course("Introduction To Operating Systems");
    ceng334->addPrerequisite(*ceng331);
    metu->registerCourse(*ceng334);
    courses.push_back(ceng334);

    Course* ceng336 = new Course("Introduction To Embedded Systems Development");
    ceng336->addPrerequisite(*ceng232);
    metu->registerCourse(*ceng336);
    courses.push_back(ceng336);

    Course* ceng350 = new Course("Software Engineering");
    ceng350->addPrerequisite(*ceng213);
    metu->registerCourse(*ceng350);
    courses.push_back(ceng350);

    Course* ceng351 = new Course("Data Management and File Structures");
    ceng351->addPrerequisite(*ceng213);
    metu->registerCourse(*ceng351);
    courses.push_back(ceng351);

    Course* ceng384 = new Course("Synals and Systems For Computer Engineers");
    ceng384->addPrerequisite(*math219);
    metu->registerCourse(*ceng384);
    courses.push_back(ceng384);

    Course* ceng435 = new Course("Data Communications and Networking");
    metu->registerCourse(*ceng435);
    courses.push_back(ceng435);

    Course* ceng477 = new Course("Introduction To Computer Graphics");
    metu->registerCourse(*ceng477);
    courses.push_back(ceng477);

    Course* ceng491 = new Course("Computer Engineering Design I");
    ceng491->addPrerequisite(*ceng350);
    metu->registerCourse(*ceng491);
    courses.push_back(ceng491);

    Course* ceng492 = new Course("Computer Engineering Design II");
    ceng492->addPrerequisite(*ceng491);
    metu->registerCourse(*ceng492);
    courses.push_back(ceng492); */
}

enum Grade learnGrade(string course_name, int student_id) {

    return AA;
}