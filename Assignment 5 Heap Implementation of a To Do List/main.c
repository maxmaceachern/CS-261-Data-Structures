#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
    char cmd[1] = " ";
    char  filename[128];
    FILE *a_file;

    int priority;
    char task[128];
    struct Task * tempTask;
    DynArr* mainList = createDynArr(10);

    printf("\n\n** TO-DO LIST APPLICATION **\n\n");

    do
        {
            printf("Press:\n"
                 "'l' to load to-do list from a file\n"
                 "'s' to save to-do list to a file\n"
                 "'a' to add a new task\n"
                 "'g' to get the first task\n"
                 "'r' to remove the first task\n"
                 "'p' to print the list\n"
                 "'e' to exit the program\n"
                 );
          /* get input command (from the keyboard) */
            scanf("%s", cmd);
          /* clear the trailing newline character */
            while (getchar() != '\n');

          /* Fixme:  Your logic goes here! */
            if(cmd[0] == 'l'){
                printf("Please enter a file name to load:");
                scanf("%s", filename);
                a_file = fopen(filename, "r");
                loadList(mainList, a_file);
                printf("File loaded\n");
                }

            else if(cmd[0] == 's'){
                printf("Please enter the file name:");
                scanf("%s", filename);
                a_file = fopen(filename, "w");
                saveList(mainList, a_file);
                printf("File saved.\n");
                }

            else if(cmd[0] == 'a'){
                printf("Please enter the task name: ");
                scanf("%s", task);
                printf("Please enter the task priority: ");
                scanf("%d", &priority);
                tempTask = createTask(priority, task);

                addHeap(mainList, tempTask, compare);
                }

            else if(cmd[0] == 'g'){
                if (sizeDynArr(mainList) > 0){
                    tempTask = getMinHeap(mainList);
                    printf("The first task on the list is: %s\n", tempTask->description);
                }
                else
                    printf("Your to-do list is empty.\n");
            }

            else if(cmd[0] == 'r'){

                if (sizeDynArr(mainList) > 0){
                    tempTask = getMinHeap(mainList);
                    removeMinHeap(mainList, compare);
                    printf("The first task (%s) has been removed from the list.\n", tempTask->description);
                    free(tempTask);
                  }
                else
                    printf("Your to-do list is empty, so nothing was removed.\n");
                }

            else if(cmd[0] == 'p'){
                if (sizeDynArr(mainList) > 0){
                    printDynArr(mainList, print_type);
                    }
                else
                    printf("Your to-do list is empty.\n");
                }
            } while(cmd[0] != 'e');
          /* Note: We have provided functions called printList(), saveList() and loadList() for you
             to use.  They can be found in toDoList.c */


      /* delete the list */
      deleteDynArr(mainList);

      return 0;
}
