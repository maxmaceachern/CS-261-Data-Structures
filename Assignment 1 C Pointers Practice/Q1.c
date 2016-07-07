/* CS261- Assignment 1 - Q.1*/
/* Name: Max MacEachern
 * Date: 1/17/15
 * Solution description: Allocates memory for an array of students (structure), generates IDs and scores for them, and then outputs the lowest, highest and average score.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student* stud = malloc(10*sizeof(struct student));

     /*return the pointer*/
    return stud;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     int i, k;
     for(i=0;i<10;i++){
        students[i].id = ((rand() % 10) + 1);
        for(k=0;k<i;k++){
            if (students[i].id == students[k].id){
                students[i].id = (rand() % 10 + 1);
                k = -1;
            }
        }
     students[i].score = (rand() % 100 + 1);
     }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int i;
    for(i=0;i<10;i++){
        printf("%i %i\n", students[i].id, students[i].score);
    }


}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int minScore, maxScore, aveScore, i;
     minScore, maxScore, aveScore = students[0].score;
     for(i=1;i<10;i++){
        if (students[i].score < minScore)
            minScore = students[i].score;
        if (students[i].score > maxScore)
            maxScore = students[i].score;
        aveScore = aveScore + students[i].score;
     }
     aveScore = aveScore / 10;
     printf("The minimum score is %d\n", minScore);
     printf("The maximum score is %d\n", maxScore);
     printf("The average score is %d\n", aveScore);

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
