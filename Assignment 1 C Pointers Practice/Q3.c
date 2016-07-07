/* CS261- Assignment 1 - Q.3*/
/* Name: Max MacEachern
 * Date: 1-17-15
 * Solution description: Fills an int array with random numbers and sorts the numbers from smallest to largest.
 */

#include <stdio.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
     int i, j, temp;

     for (i=0; i < n - 1; ++i)
     {
         for (j = i + 1; j < n; ++j){
             if (number[i] > number[j]){
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
                }
         }
     }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    int a,b,c;
    /*Allocate memory for an array of n integers using malloc.*/
    int *intArray = malloc(n*sizeof(int));
    /*Fill this array with random numbers, using rand().*/
    for (a = 0; a < n; a++)
        intArray[a] = rand();
    /*Print the contents of the array.*/
    for (b = 0; b < n; b++)
        printf("%i\n",intArray[b]);
    /*Pass this array along with n to the sort() function of part a.*/
    sort(intArray,n);
    /*Print the contents of the array.*/

    for (c = 0; c < n; c++)
        printf("%i\n",intArray[c]);

    return 0;
}
