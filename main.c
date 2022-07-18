#include <stdio.h>
#include <ctype.h>
#include "getInput.c"
#include "textDisplay.c"
#define MAX_SIZE 1000

void getCommand(char *input, int inputSize);

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    printf("%s", introString);
    printf("%s\n\n", functionString);

    printf("Enter command: ");
    getCommand(input, MAX_SIZE);
    command = toupper(input[0]);
    

    return 0;
}
