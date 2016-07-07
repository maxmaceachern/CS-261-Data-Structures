/* CS261- Assignment 1 - Q. 0*/
/* Name: Max MacEachern
 * Date: 1/17/16
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
    printf("%d\n", *iptr);
     /*Print the address pointed to by iptr*/
    printf("%p\n", iptr);
     /*Print the address of iptr itself*/
    printf("%p\n", &iptr);
}

int main(){
    /*declare an integer x*/
    int x;
    /*print the address of x*/
    printf("The memory address of x is %i\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("The value of x is %i\n", x);
    return 0;
}
