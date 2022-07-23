#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000

void getCommand(char *input, int inputSize) {
    int i;
    char c;
    for (i = 0; (c = getchar()) != '\n' && i < (inputSize - 1); i++) {
        input[i] = c;
    }
    input[i] = '\0';
}

void getInputNode(char *familyName, char *firstName, char *address, char *phoneNumber, char *doctorName, char *status, char *condition) {
    printf("\n  Family name: ");
    getCommand(familyName, MAX_SIZE);
    printf("  First name: ");
    getCommand(firstName, MAX_SIZE);
    printf("  Address: ");
    getCommand(address, MAX_SIZE);
    printf("  Phone number: ");
    getCommand(phoneNumber, MAX_SIZE);
    printf("  Status: ");
    getCommand(status, MAX_SIZE);
    printf("  Condition: ");
    getCommand(condition, MAX_SIZE);
}