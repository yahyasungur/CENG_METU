#include <stdio.h>
#include <stdlib.h>
#include "master_ceng.h"

/*
Take an integer pointer to save size of the instructors. Reads input from stdin,
creates list of instructors.

size: integer pointer to save size of the instructors.
*/
float **create_instructors(int *size){
    float **instructors;
    int i,j;

    scanf(" %d",size);
    instructors = (float**)malloc(sizeof(float*)*(*size));
    for (i = 0; i < (*size); i++){
        instructors[i] = (float*)malloc(sizeof(float)*4);
    }

    for ( i = 0; i < (*size); i++){
        for ( j = 0; j < 4; j++){
           scanf(" %f",&instructors[i][j]);
        }
    }
    return instructors;
}

/*
Take an integer pointer to save size of the submissions. Reads input from stdin,
creates list of submissions.

size: integer pointer to save size of the submissions.
*/
int **create_submissions(int *size){   
    int i,j;
    int **submissions;

    scanf(" %d",size);
    submissions = (int**)malloc(sizeof(int*)*(*size));
    for ( i = 0; i < (*size); i++){
        submissions[i] = (int*)malloc(sizeof(int)*5);
    }
     
    for ( i = 0; i < (*size); i++){
        for ( j = 0; j < 5; j++){
           scanf(" %d",&submissions[i][j]);
        }
    }
    return submissions;
}

/*
Reads input from stdin and creates a jury team.

size: integer pointer to save size of the jury.
*/
int *create_jury(int *jury_size){
    int *jury,i;
    static int k = 0;
    if(k == 0){
        jury = (int*)malloc(1);
        k++;
    }
    scanf(" %d",jury_size);
    jury = (int*)realloc(jury,sizeof(int)*(*jury_size));
    for ( i = 0; i < (*jury_size); i++){
        scanf(" %d",&jury[i]);
    }
    return jury;
}

/*
Takes submissions and instructors as input. Calls create_jury function for each submission.
Calculates score of the submissions and saves into a list.

submissions: list of submissions
size: size of the submissions
instructors: list of instructors
*/
float *calculate_submission_scores(int **submissions, int size, float **instructors){
    int i,j,h,index,jury_size = 0;
    int *jury;
    float *scores;
    float temp;
    scores = (float*)malloc(sizeof(float)*size);
    for ( i = 0; i < size; i++){
        jury = create_jury(&jury_size);
        temp = 0.0;
        for (j = 0; j < 5; j++){
            index = submissions[i][j];
            for (h = 0; h < jury_size; h++){
                temp += instructors[jury[h]][index];
            }
        }
        scores[i] = temp;
    }
    free(jury);
    /* We cannot reach size of instructors at this point.
    So, we free the memory as much as possible. (jury_size)
    */
    for (i = 0; i < jury_size; i++){
        free(instructors[i]);
    }
    free(instructors);
    return scores;
}

/*
Takes scores and size of scores as input. Finds and returns average of the scores.

scores: list of scores
size: size of the scores
*/
float find_average_score(float *scores, int size){
    int i;
    float avg,sum = 0.0;
    for ( i = 0; i < size; i++){
        sum += scores[i];
    }
    avg = sum/(float)size;
    return avg;
}

/*
Takes submissions, scores and size of submissions as input. Finds and prints corresponding 
PLs of the projects of winner.

submissions: list of submissions
size: size of the submissions
scores: scores of the submissions
*/
void print_winner(int **submissions, int size, float *scores){
    int i,index;
    float max = 0.0;
    for ( i = 0; i < size; i++){
        if (scores[i] > max){
            max = scores[i];
            index = i;
        }
    }
    printf("Winner:");
    for ( i = 0; i < 5; i++){
        printf(" %d",submissions[index][i]);
    }
    printf("\n");
    
    free(scores);
    for (i = 0; i < size; i++){
        free(submissions[i]);
    }
    free(submissions);
}

/*
Takes a 2D array, an integer representing type and size of the array as input and print the array.

array: 2D array
type: 0->Instructors, 1->Submissions
size: row count of the array
*/

void print_instructors(float **array, int size){
    int i,j;   
    for (i = 0; i < size; i++){
        for ( j = 0; j < 4; j++){
            if (j == 3){
                printf("%.2f\n",array[i][j]);
            }
            else{
                printf("%.2f ",array[i][j]);
            }                
        }
    }
}
void print_submissions(int **array, int size){
    int i,j;   
    for (i = 0; i < size; i++){
        for ( j = 0; j < 5; j++){
            if (j == 4){
                printf("%d\n",array[i][j]);
            }
            else{
                printf("%d ",array[i][j]);
            }                
        }
    }
}


void print_double_array(void **array, int type, int size){
    if(type){
        print_submissions((int**)array,size);
    }
    else{
        print_instructors((float**)array,size);
    }
}
