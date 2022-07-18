#include <string.h>

void getCommand(char *input, int inputSize) {
    int i;
    char c;
    for (i = 0; (c = getchar()) != '\n' && i < (inputSize - 1); i++) {
        input[i] = c;
    }
    input[i] = '\0';
}