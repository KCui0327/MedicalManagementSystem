#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getInput.c"
#include "textDisplay.c"
#include "nodeOperations.c"
#define MAX_SIZE 1000

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    char *familyName, *firstName, *address, *phoneNumber, *doctorName, *status, *condition;

    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;

    printf("%s", introString);
    printf("%s\n\n", functionString);
    
    do {
        printf("\nEnter command: ");
        getCommand(input, MAX_SIZE + 1);
        command = toupper(input[0]);

        familyName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        firstName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        address = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        phoneNumber = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        status = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        condition = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);

        switch(command) {
            case 'I':
                getInputNode(familyName, firstName, address, phoneNumber, doctorName, status, condition);
                // insertNodeInOrder(list, familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'D':
                break;
            case 'S':
                break;
            case 'P':
                break;
            case 'R':
                break;
            case 'E':
                break;
        }

    } while (command != 'E');

    return 0;
}
