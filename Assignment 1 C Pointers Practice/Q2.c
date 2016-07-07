/* CS261- Assignment 1 - Q.2*/
/* Name: Max MacEachern
 * Date: 1-17-15
 * Solution description: Demonstrates the nature of pointers and how to change the value pointed to by  pointer rather than a local copy.
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    /*Set b to half its original value*/
    *b = *b / 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    /*Print the values of x, y and z*/
    printf("%d %d %d\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int result = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("%d\n", result);
    /*Print the values of x, y and z again*/
    printf("%d %d %d\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
    /*This is because the foo function accepts an integer number for c, rather than a pointer. Here it operates on a local copy
    of the variable. Afterward, the variable z still retains the previous value.*/
    return 0;
}


