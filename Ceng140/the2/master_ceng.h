#ifndef __MASTER_CENG__H__
#define __MASTER_CENG__H__

/*
Take an integer pointer to save size of the instructors. Reads input from stdin,
creates list of instructors.

size: integer pointer to save size of the instructors.
*/
float **create_instructors(int *size);

/*
Take an integer pointer to save size of the submissions. Reads input from stdin,
creates list of submissions.

size: integer pointer to save size of the submissions.
*/
int **create_submissions(int *size);

/*
Reads input from stdin and creates a jury team.

size: integer pointer to save size of the jury.
*/
int *create_jury();

/*
Takes submissions and instructors as input. Calls create_jury function for each submission.
Calculates score of the submissions and saves into a list.

submissions: list of submissions
size: size of the submissions
instructors: list of instructors
*/
float *calculate_submission_scores(int **submissions, int size, float **instructors);

/*
Takes scores and size of scores as input. Finds and returns average of the scores.

scores: list of scores
size: size of the scores
*/
float find_average_score(float *scores, int size);

/*
Takes submissions, scores and size of submissions as input. Finds and prints corresponding 
PLs of the projects of winner.

submissions: list of submissions
size: size of the submissions
scores: scores of the submissions
*/
void print_winner(int **submissions, int size, float *scores);

/*
Takes a 2D array, an integer as type and size of the array as input and print the array.

array: 2D array
type: 0->Instructors, 1->Submissions
size: row count of the array
*/
void print_double_array(void **array, int type, int size);

#endif
