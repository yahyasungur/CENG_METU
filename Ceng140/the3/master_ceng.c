#include <stdio.h>
#include <stdlib.h>
#include "master_ceng.h"

int num_subm =0;

char pl_names[4][10] = {
    "C",
    "C++",
    "Python",
    "Java"};

/*
Takes Instructors' linked list, name of the instructor and pl_ratings array
*/
void insert_instructor(Instructor **list, char *name, float *pl_ratings){
    Instructor *temp = (*list);

    if((*list) == NULL){
        (*list) = (Instructor*)malloc(sizeof(Instructor));
        (*list)->instructor_name = name;
        (*list)->pl_ratings = pl_ratings;
        (*list)->next = NULL;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = (Instructor*)malloc(sizeof(Instructor));
        temp->next->instructor_name = name;
        temp->next->pl_ratings = pl_ratings;
        temp->next->next = NULL;
    }
}

/*
Takes Submissions' linked list, name of the student and pl indexes of projects
*/
void insert_submission(Submission **list, char *name, int *pl_list){
    Submission *temp = (*list);
    int i;
    num_subm++;
    if((*list) == NULL){
        (*list) = (Submission*)malloc(sizeof(Submission));
        (*list)->student_name = name;
        (*list)->projects = (Project*)malloc(sizeof(Project)*5);
        for ( i = 0; i < 5; i++){
            (*list)->projects[i].pl_index = pl_list[i];
            (*list)->projects[i].project_index = i;
        }
        (*list)->next = NULL;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = (Submission*)malloc(sizeof(Submission));
        temp->next->student_name=name;
        temp->next->projects= (Project*)malloc(sizeof(Project)*5);
        for ( i = 0; i < 5; i++){
            (temp->next)->projects[i].pl_index = pl_list[i];
            (temp->next)->projects[i].project_index = i;
        }
        temp->next->next = NULL;
    }
}

/*
Takes Instructor linked list, Submission linked list, 
jury member indexes for each submission, number of jury members for each submission

return: Array of Score structure
*/
Score *calculate_submission_scores(Instructor *instructions, Submission *submissions, int **juries, int jury_size){
    Score *score = (Score*)malloc(sizeof(Score)*num_subm);
    Submission *sub_temp = submissions;
    Instructor *ins_temp = instructions;
    float sum = 0.0,score_array[5];
    int i,j,p,index;


    for (i = 0; i < num_subm; i++){
        sum = 0.0;
        for ( p = 0; p < 5; p++){
            score_array[p] = 0;
        }
    

        for (j = 0; j < jury_size; j++){
            index = juries[i][j];
            ins_temp = instructions;
            for ( p = 0; p < index; p++){
                ins_temp = ins_temp->next;
            }
            
            for ( p = 0; p < 5; p++){
                score_array[p] += ins_temp->pl_ratings[sub_temp->projects[p].pl_index];
            }
        }
        
        for ( p = 0; p < 5; p++){
            sum += score_array[p];
        }

        score[i].student_name = sub_temp->student_name;
        score[i].score = sum;

        sub_temp = sub_temp->next;
    }

    return score;
}

/*
Takes scores and size of scores as input. Finds and returns average of the scores.

return: average score of submissions
*/
float find_average_score(Score *scores, Submission *submissions){
    float sum = 0.0;
    int i;
    for ( i = 0; i < num_subm; i++){
        sum += scores[i].score;
    }
    return sum/(float)num_subm;
}

/*
Takes submissions and scores as input. Finds and returns corresponding Score instance of winner.

return: Score instance of best submission 
*/
Score find_winner(Score *scores, Submission *submissions){
    int i,index = 0;
    float max = scores[0].score;

    for ( i = 0; i < num_subm; i++){
        if (scores[i].score > max){
            max = scores[i].score;
            index = i;
        }
    }

    return scores[index];
}

/*
Prints instructors' linked list.
*/
void print_instructor(Instructor *instructors){
    Instructor *temp = instructors;
    int i;

    while (temp != NULL){
        printf("Name: %s\n",temp->instructor_name);
        printf("Ratings:");
        for ( i = 0; i < 4; i++){
            printf(" %.2f",temp->pl_ratings[i]);
        }
        printf("\n");
        temp = temp->next;
    }

}

/*
Prints submissions' linked list.
*/
void print_submission(Submission *submissions){
    Submission *temp = submissions;
    int i;

    while (temp != NULL){
        printf("Name: %s\n",temp->student_name);
        for ( i = 0; i < 5; i++){
            printf(" Project-%d: %s\n",i+1,pl_names[temp->projects[i].pl_index]);
        }
        temp = temp->next;
    }

}

/*
Prints array of Score structure.
*/
void print_scores(Submission *submissions, Score *scores){
    int i;
    for ( i = 0; i < num_subm; i++){
        printf("Score of %s: %.2f\n",scores[i].student_name,scores[i].score);
    }
}
