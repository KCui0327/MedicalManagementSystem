#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getInput.c"
#include "textDisplay.c"
#define MAX_SIZE 1000

void getCommand(char *input, int inputSize);

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    char *familyName, *firstName, *address, *phoneNumber, *doctorName, *status, *condition;
    printf("%s", introString);
    printf("%s\n\n", functionString);



    do {
        printf("Enter command: ");
        getCommand(input, MAX_SIZE);
        command = toupper(input[0]);

        familyName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        firstName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        address = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        phoneNumber = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        doctorName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        status = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        condition = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);

        switch(command) {
            case 'I':
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
