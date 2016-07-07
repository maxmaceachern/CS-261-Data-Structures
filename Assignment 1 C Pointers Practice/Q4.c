/* CS261- Assignment 1 - Q.4*/
/* Name: Max MacEachern
 * Date: 1-17-15
 * Solution description: Allocates memory for an array of struct students, each with an ID and score. Sorts on score.
 */

#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
     int i, j;
     struct student temp;

     for (i=0; i < n - 1; ++i)
     {
         for (j = i + 1; j < n; ++j){
             if (students[i].score > students[j].score){
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
                }
         }
     }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;
    /*Allocate memory for n students using malloc.*/
    struct student *myStudents = malloc(n * sizeof(struct student));
    /*Generate random IDs and scores for the n students, using rand().*/
    int k = 0;
    for(k=0;k<n;k++){
        myStudents[k].id = ((rand() % 10) + 1);
        myStudents[k].score = (rand() % 100 + 1);
    }
    /*Print the contents of the array of n students.*/
    for (k = 0; k < n; k++)
        printf("%d %d\n",myStudents[k].id, myStudents[k].score);
    /*Pass this array along with n to the sort() function*/
    sort(myStudents, n);
    /*Print the contents of the array of n students.*/
    for (k = 0; k < n; k++)
        printf("%d %d\n",myStudents[k].id, myStudents[k].score);
    return 0;
}
