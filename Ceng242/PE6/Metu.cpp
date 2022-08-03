#include "Metu.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****                *** METU ***                ****/

/* Constructor : Initialize your own variables if you
   need.
*/
using namespace std;

Metu::Metu() {
	// TODO
}

/* Destructor  : It is responsible of the destruction of
   the Course and OpenCourse objects and the registered
   students, and the constrcuted seating plan, if any.
*/
Metu::~Metu() {
	// TODO
   for (int i = 0; (unsigned)i < this->students.size(); i++){
      this->students[i].~Student();
   }
   this->students.clear();

   this->courses.clear();
   for (int i = 0; (unsigned)i < this->seating_plan.size(); i++){
      this->seating_plan[i].clear();
   }
   this->seating_plan.clear();


   delete sop;
   delete open_course;
   delete jun;
   delete sen;   
}

/* This method returns the student whose id is given
   in the argument. You need to find the corresponding
   student among the registered students.
*/
Student& Metu::getStudent(int id) {
	// TODO
   int index = -1;
   for (int i = 0; (unsigned)i < this->students.size(); i++){
      if (this->students[i].getId() == id){
         return this->students[i];
         index = i;
      }
   }
   return this->students[index];
}

/* This method directly adds (without creating a copy)
   the given student to the list of registered students.
*/
void Metu::registerStudent(Student* student) {
	// TODO
   this->students.push_back(*student);
}

/* This method directly adds (without creating a copy)
   the given course to the list of base course objects
   (not among the derived ones).
*/
void Metu::registerCourse(const Course& course) {
	// TODO
   this->courses.push_back(course);
}

/* This method constructs a new OpenCourse object by deriving
   from the Course object given in the first argument and
   using the <term> and <quota> values given in the second
   and third arguments, respectively.
   Also, for each student given in the corresponding lists as
   function arguments, the newly created OpenCourse is tried 
   to be added in order.
   Note that the priority order is given from greater to less
   as follows: Seniors > Juniors > Sophomores > Freshmans.
   After the priority ordering, you should try to add the
   course for each student of the same type in the order inside
   the corresponding list.
   Also, during the course addition, you should take the course
   quota in consider.
   In the end, there may be left the students who could not add
   the course because of the quota or the course prerequisite.
   Finally, you should return the created OpenCourse object.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/

OpenCourse& Metu::openCourse(const Course& course, string term, int quota, 
							vector<Freshman*> freshmans, vector<Sophomore*> sophomores, vector<Junior*> juniors, vector<Senior*> seniors) {
	// TODO
   open_course = new OpenCourse(course, term, course_index++, quota);
   
   for (int i = 0; (unsigned)i < seniors.size(); i++){
      if (quota > 0 && seniors[i]->addCourse((*open_course))){
         quota--;
      }
   }

   for (int i = 0; (unsigned)i < juniors.size(); i++){
      if (quota > 0 && juniors[i]->addCourse((*open_course))){
         quota--;
      }
   }

   for (int i = 0; (unsigned)i < sophomores.size(); i++){
      if (quota > 0 && sophomores[i]->addCourse((*open_course))){
         quota--;
      }
   }

   for (int i = 0; (unsigned)i < freshmans.size(); i++){
      if (quota > 0 && freshmans[i]->addCourse((*open_course))){
         quota--;
      }
   }
   
   return (*open_course);
}

/* This method upgrades the given Freshman object to
   the Sophomore status by constructing a new Sophomore
   object with the properties of the given Freshman.
   You should delete the given Freshman and place the 
   newly created Sophomore object to its location in the 
   students array of Metu object.
   In the end, you should return the created Sophomore.

   By the way; of course it would be nicer to define 
   this method in "virtual" in order to use it for different 
   types of Students. However, we do not want to test 
   you with "virtual" keyword in this PE. We've left it 
   to next PE.
*/

Sophomore* Metu::upgradeStudent(Freshman& student) {
	// TODO
   sop = new Sophomore(student);
   
   int id = student.getId();
   for (int i = 0; (unsigned)i < this->students.size(); i++){
      if(this->students[i].getId() == id){
         this->students.erase(this->students.begin() + i);
         break;
      }
   }
   this->students.push_back(*sop);

   return sop;
}

/* This method upgrades the given Sophomore object to
   the Junior status by constructing a new Junior
   object with the properties of the given Sophomore.
   You should delete the given Sophomore and place the
   newly created Junior object to its location in the
   students array of Metu object.
   In the end, you should return the created Junior.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/

Junior* Metu::upgradeStudent(Sophomore& student) {
	// TODO
   jun = new Junior(student);
   
   int id = student.getId();
   for (int i = 0; (unsigned)i < this->students.size(); i++){
      if(this->students[i].getId() == id){
         this->students.erase(this->students.begin() + i);
         break;
      }
   }
   this->students.push_back(*jun);

   return jun;
}

/* This method upgrades the given Junior object to
   the Senior status by constructing a new Senior
   object with the properties of the given Junior.
   You should delete the given Junior and place the
   newly created Senior object to its location in the
   students array of Metu object.
   In the end, you should return the created Senior.

   By the way; of course it would be nicer to define
   this method in "virtual" in order to use it for different
   types of Students. However, we do not want to test
   you with "virtual" keyword in this PE. We've left it
   to next PE.
*/

Senior* Metu::upgradeStudent(Junior& student) {
	// TODO
   sen =  new Senior(student);
   
   int id = student.getId();
   for (int i = 0; (unsigned)i < this->students.size(); i++){
      if(this->students[i].getId() == id){
         this->students.erase(this->students.begin() + i);
         break;
      }
   }
   this->students.push_back(*sen);

   return sen;
}


/* This method sets the number of rows and number of columns in a
   standard Metu classroom with the given arguments, respectively.
*/
void Metu::initialize_seating(int row, int column){
   for (int i = 0; i < row; i++){
      vector<int> vec(column,-1);
      this->seating_plan.push_back(vec);
   }
   
}


void Metu::setClassroomSize(int row_size, int column_size) {
	// TODO
   this->row_size = row_size;
   this->column_size = column_size;
   this->initialize_seating(row_size, column_size);
}

/* This method tries to construct the 2D seating plan by using
   the given information as function argument one-by-one.
   The information consists of 2 integers and 1 string argument.
   The string parameter can be either "|" or "-".
   If it is "|", then it means location of the student whose id 
   given in the first argument is <row_id, column_id> whereas
   location of the student whose id given in the second argument
   is <row_id + 1, column_id>.
   If it is "-", then it means location of the student whose id 
   given in the first argument is <row_id, column_id> whereas
   location of the student whose id given in the second argument
   is <row_id, column_id + 1>.
*/
pair<int,int> Metu::check_student(int id){
   pair<int,int> p;
   for (int i = 0; i < this->row_size; i++){
      for (int j = 0; j < this->column_size; j++){
         if (id == this->seating_plan[i][j]){
            p.first = i;
            p.second = j;
            return p;
         }
      }
   }
   
   p.first = -1;
   p.second = -1;
   return p;
}


void Metu::addCheatInfo(int from_student_id, int to_student_id, string dir) {
	// TODO
   pair<int,int> ids;
   ids.first = from_student_id;
   ids.second = to_student_id;
   
   pair<pair<int,int>,string> element;
   element.first = ids;
   element.second = dir;

   this->cheating.push_back(element);

}

/* This method prints the given seating plan, in
   other words the 2D array. Between each seat,
   print an empty space, i.e. " " character.
   Also, put an empty space to the end of each row.
   After each row (including the last one), print a
   new line, i.e. "\n" character.
   For the empty seats, print a "X" character (uppercase).
   For non-empty seats, print the id of the student
   sitting there.
*/
void Metu::construct_seating(){
   
   // find initial element
   int initial_id = -1;
   for (int i = 0; (unsigned)i < this->cheating.size(); i++){
      int first_id = this->cheating[i].first.first;
      int second_id = this->cheating[i].first.second;
      
      bool is_initial = true;


      //kimsenin sağında veya altında değil bunu geçerse
      for (int j = 0; (unsigned)j < cheating.size(); j++){
         if(this->cheating[j].first.second == first_id){
            is_initial = false;
            break;
         }
      }

      //kimsenin sağında veya altında değil (first_id hariç) yanındaki bunu geçerse
      for (int j = 0; (unsigned)j < cheating.size(); j++){
         if(this->cheating[j].first.second == second_id){
            if (i == j){
               continue;
            }else{         
               is_initial = false;
               break;
            }
         }
      }

      if (is_initial == true){
         initial_id = first_id;
         break;
      }
   }

   this->seating_plan[0][0] = initial_id;


   int last_seated = initial_id;
   int size = this->cheating.size();
   for (int i = 0; i < size; i++){

      for (int j = 0; (unsigned)j < this->cheating.size(); j++){
         if (this->cheating[j].first.first == last_seated){
            pair<int, int> location = check_student(last_seated);
            int to_id = this->cheating[j].first.second;

            if (this->cheating[j].second == "-"){
               this->seating_plan[location.first][location.second+1] = to_id;
            }
            else if(this->cheating[j].second == "|"){
               this->seating_plan[location.first+1][location.second] = to_id;
            }
            
            last_seated = to_id;
            this->cheating.erase(this->cheating.begin()+ j);
            break;
         }
      }
      
   }

   size = this->cheating.size();
   for (int i = 0; i < size; i++){

      for (int j = 0; (unsigned)j < this->cheating.size(); j++){
         if (this->cheating[j].first.second == last_seated){
            pair<int, int> location = check_student(last_seated);
            int from_id = this->cheating[j].first.first;

            if (this->cheating[j].second == "-"){
               this->seating_plan[location.first][location.second-1] = from_id;
            }
            else if(this->cheating[j].second == "|"){
               this->seating_plan[location.first-1][location.second] = from_id;
            }
            
            last_seated = from_id;
            this->cheating.erase(this->cheating.begin()+ j);
            break;
         }
      }
      
   }
   
}


void Metu::printSeatingPlan() {
	// TODO
   this->construct_seating();

   for (int i = 0; i < this->row_size; i++){
      for (int j = 0; j < column_size; j++){
         if (this->seating_plan[i][j] == -1){
            printf("X ");
         }
         else{
            cout << this->seating_plan[i][j] << " ";
         }
      }
      printf("\n");
   }
   
}
