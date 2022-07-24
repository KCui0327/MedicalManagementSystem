#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 1000

typedef struct node {
    char *familyName;
    char *firstName;
    char *address;
    char *phoneNumber;
    char *status;
    char *condition;
    struct node *next;
} Node;

typedef struct linkedList {
    Node *head;
} LinkedList;

void getCommand(char *input, int inputSize);
void getInputNode(
            char *familyName, char *firstName, char *address,
            char *phoneNumber, char *doctorName, char *status, char *condition
        );
Node* createNode(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void printNode(LinkedList *list);
bool isEmpty(LinkedList *list);
void addNodeFront(
            LinkedList *list, char *familyName, char *firstName,
            char *address, char *phoneNumber, char *status, char *condition
        );

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    char *familyName, *firstName, *address, *phoneNumber, *doctorName, *status, *condition;
    const char introString[] 
    = "Medical Management System.\n\n";
const char functionString[] 
    = "List of Commands: \n\t - Insert (I) \n\t - Delete (D) \n\t - S (search by name) \n\t "
      "- P (search by phone number) \n\t - Print (P) \n\t - Reset (R) \n\t - Exit (E)";

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
                if (searchFamilyName(list, familyName)) {
                    addNodeFront(list, familyName, firstName, address, phoneNumber, status, condition);
                } else {
                    printf("\nFamily name already exists.\n");
                }
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

void getCommand(char *input, int inputSize) {
    int i;
    char c;
    for (i = 0; (c = getchar()) != '\n' && i < (inputSize - 1); i++) {
        input[i] = c;
    }
    input[i] = '\0';
}

void getInputNode(
        char *familyName, char *firstName, char *address,
        char *phoneNumber, char *doctorName, char *status, char *condition
        ) {
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

Node* createNode(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->familyName = familyName;
        newNode->firstName = firstName;
        newNode->address = address;
        newNode->phoneNumber = phoneNumber;
        newNode->status = status;
        newNode->condition = condition;
        newNode->next = NULL;
    }
    return newNode;
}

void printNode(LinkedList *list) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        printf("\n  Family name: %s", currentNode->familyName);
        printf("\n  First name: %s", currentNode->firstName);
        printf("\n  Address: %s", currentNode->address);
        printf("\n  Phone number: %s", currentNode->phoneNumber);
        printf("\n  Status: %s", currentNode->status);
        printf("\n  Condition: %s", currentNode->condition);
        currentNode = currentNode->next;
    }
}

bool isEmpty(LinkedList *list) {
    return list->head == NULL;
}

void addNodeFront(
            LinkedList *list, char *familyName, char *firstName,
            char *address, char *phoneNumber, char *status, char *condition
        ) {

    if (isEmpty(list)) {
        list->head = createNode(familyName, firstName, address, phoneNumber, status, condition);
        return;
    } 

    Node *temp = createNode(familyName, firstName, address, phoneNumber, status, condition);
    if (temp != NULL) {
        temp->next = list->head;
        list->head = temp;
    }
}

void addNodeInorder(
            LinkedList *list, char *familyName, char *firstName,
            char *address, char *phoneNumber, char *status, char *condition
        ) {

    if (isEmpty(list) || strcmp(familyName, list->head->familyName) < 0) {
        return addNodeFront(list, familyName, firstName, address, phoneNumber, status, condition);
    }
    Node *newNode = createNode(familyName, firstName, address, phoneNumber, status, condition);
    if (newNode == NULL) {
        Node *currentNode = list->head;
        while (currentNode != NULL) {
            if (strcmp(familyName, currentNode->familyName) < 0) {
                break;
            }
            currentNode = currentNode->next;
        }
        newNode->next = currentNode->next;
        currentNode->next = newNode;
        return;
    }
}

bool searchFamilyName(LinkedList *list, char *familyName) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(familyName, currentNode->familyName) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

bool searchPhoneNumber(LinkedList *list, char *phoneNumber) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(phoneNumber, currentNode->phoneNumber) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

bool deleteFamilyName(LinkedList *list, char *familyName) {
    if (isEmpty(list)) {
        return false;
    }
    if (strcmp(familyName, list->head->familyName) == 0) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        return true;
    }
    Node *currentNode = list->head;
    while (currentNode->next != NULL) {
        if (strcmp(familyName, currentNode->next->familyName) == 0) {
            Node *temp = currentNode->next;
            currentNode->next = currentNode->next->next;
            free(temp);
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

void deleteFrontNode(
            LinkedList *list, char *familyName, char *firstName,
            char *address, char *phoneNumber, char *status, char *condition
        ) {
    if (isEmpty(list)) {
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
}

void removeNodes(
            LinkedList *list, char *familyName, char *firstName,
            char *address, char *phoneNumber, char *status, char *condition
        ) {

    while (isEmpty(list) == false) {
        deleteFrontNode(list, familyName, firstName, address, phoneNumber, status, condition);
    }
    list->head = NULL;
}
