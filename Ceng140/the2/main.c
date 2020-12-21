#include <stdio.h>
#include "master_ceng.h"

int main(int argc, char const *argv[])
{   
    int i,ins_size = 0,sub_size = 0;
    float **instructors,avg;
    float *scores;
    int **submissions;
    
    instructors = create_instructors(&ins_size);
    printf("Instructors:\n");
    print_double_array((void **)instructors,0,ins_size);

    submissions = create_submissions(&sub_size);
    printf("Submissions:\n");
    print_double_array((void **)submissions,1,sub_size);

    scores = calculate_submission_scores(submissions,sub_size,instructors);
    for (i = 0; i < sub_size; i++)
    {
        printf("Sub-%d: %.2f\n",i+1,scores[i]);
    }

    avg = find_average_score(scores,sub_size);
    printf("Average: %.2f\n", avg);

    print_winner(submissions,sub_size,scores);

    return 0;
}
