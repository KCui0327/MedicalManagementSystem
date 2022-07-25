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
void getInputNode(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition2);
Node* createNode(Node *next, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void printList(LinkedList *list);
void printNode(LinkedList *list, char *familyName, char *firstName);
bool isEmpty(LinkedList *list);
void addNodeFront(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
bool deletePatient(LinkedList *list, char *familyName, char *firstName);
bool searchPatient(LinkedList *list, char *familyName, char *firstName);
bool searchPhoneNumber(LinkedList *list, char *phoneNumber);
void addNodeInorder(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void removeNodes(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void freeVariables(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    char *familyName, *firstName, *address, *phoneNumber, *status, *condition;
    const char introString[] 
    = "Medical Management System.\n\n";
const char functionString[] 
    = "List of Commands: \n\t - Insert (I) \n\t - Delete (D) \n\t - S (search by patient's name) \n\t "
      "- N (search by phone number) \n\t - Print (P) \n\t - Reset (R) \n\t - Exit (E)";

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
                getInputNode(familyName, firstName, address, phoneNumber, status, condition);
                if (searchPatient(list, familyName, firstName) == false) {
                    addNodeInorder(list, familyName, firstName, address, phoneNumber, status, condition);
                } else {
                    printf("\nPatient already exists.\n");
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'D':
                printf("  Family name: ");
                getCommand(familyName, MAX_SIZE);
                printf("  First name: ");
                getCommand(firstName, MAX_SIZE);
                if (searchPatient(list, familyName, firstName)) {
                    deletePatient(list, familyName, firstName);
                } else {
                    printf("\nThere is no such patient named %s %s", firstName, familyName);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'S':
                printf("  Family name: ");
                getCommand(familyName, MAX_SIZE);
                printf("  First name: ");
                getCommand(firstName, MAX_SIZE);
                if (searchPatient(list, familyName, firstName)) {
                    printNode(list, familyName, firstName);
                } else {
                    printf("\nThere is no such patient named %s %s", firstName, familyName);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'N':
                printf("  Phone number: ");
                getCommand(phoneNumber, MAX_SIZE);
                if (searchPhoneNumber(list, phoneNumber)) {
                    printList(list);
                } else {
                    printf("\nThere is no patient with this phone number %s", phoneNumber);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'P':
                if (list->head != NULL) {
                    printList(list);
                } else {
                    printf("\nThere is no patient in the list.");
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                break;
            case 'R':
                removeNodes(list, familyName, firstName, address, phoneNumber, status, condition);
                printf("\nSystem has been reset.\n");
                break;
            case 'E':
                removeNodes(list, familyName, firstName, address, phoneNumber, status, condition);
                printf("\nSystem has been exited.\n");
                break;
            default:
                printf("\nInvalid command.\n\n");
                puts(functionString);
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

void getInputNode(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
        printf("  Family name: ");
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

Node *createNode(Node *next, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->familyName = familyName;
        newNode->firstName = firstName;
        newNode->address = address;
        newNode->phoneNumber = phoneNumber;
        newNode->status = status;
        newNode->condition = condition;
        newNode->next = next;
    }
    return newNode;
}

bool isEmpty(LinkedList *list) {
    return list->head == NULL;
}

void printList(LinkedList *list) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        printf("%s\n", currentNode->familyName);
        printf("%s\n", currentNode->firstName);
        printf("%s\n", currentNode->address);
        printf("%s\n", currentNode->phoneNumber);
        printf("%s\n", currentNode->status);
        printf("%s\n", currentNode->condition);
        currentNode = currentNode->next;
    }
}

void printNode(LinkedList *list, char *familyName, char *firstName) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(familyName, currentNode->familyName) == 0 && strcmp(firstName, currentNode->firstName) == 0) {
            printf("%s\n", currentNode->familyName);
            printf("%s\n", currentNode->firstName);
            printf("%s\n", currentNode->address);
            printf("%s\n", currentNode->phoneNumber);
            printf("%s\n", currentNode->status);
            printf("%s\n", currentNode->condition);
        }
        currentNode = currentNode->next;
    }
}

void addNodeFront(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list)) {
        list->head = createNode(list->head, familyName, firstName, address, phoneNumber, status, condition);
        return;
    } 

    Node *temp = createNode(list->head, familyName, firstName, address, phoneNumber, status, condition);
    if (temp != NULL) {
        temp->next = list->head;
        list->head = temp;
    }
}

void addNodeInorder(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list) || strcmp(familyName, list->head->familyName) < 0) {
        return addNodeFront(list, familyName, firstName, address, phoneNumber, status, condition);
    }

    Node *currentNode = list->head;
    while (currentNode->next != NULL) {
        if (strcmp(familyName, currentNode->familyName) < 0) {
            break;
        }
        currentNode = currentNode->next;
    }
    Node *newNode = createNode(currentNode->next, familyName, firstName, address, phoneNumber, status, condition);
    if (newNode == NULL) {
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
}

bool searchPatient(LinkedList *list, char *familyName, char *firstName) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(currentNode->familyName, familyName) == 0 && strcmp(firstName, currentNode->firstName) == 0) {
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

bool deletePatient(LinkedList *list, char *familyName, char *firstName) {
    if (isEmpty(list)) {
        return false;
    }
    if (strcmp(familyName, list->head->familyName) == 0 && strcmp(firstName, list->head->firstName) == 0) {
        Node *temp = list->head->next;
        free(list->head);
        list->head = temp;
        return true;
    }
    Node *currentNode = list->head;

    while (currentNode->next != NULL && strcmp(familyName, currentNode->next->familyName) != 0 && strcmp(firstName, currentNode->next->firstName) != 0) {
        currentNode = currentNode->next;
    }

    if (currentNode->next != NULL) {
        Node *temp = currentNode->next;
        currentNode->next = temp->next;
        return true;
    }
    return false;
}

void deleteFrontNode(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list)) {
        return;
    }
    Node *temp = list->head->next;
    free(list->head->familyName);
    list->head->familyName = NULL;
    free(list->head->firstName);
    list->head->firstName = NULL;
    free(list->head->address);
    list->head->address = NULL;
    free(list->head->phoneNumber);
    list->head->phoneNumber = NULL;
    free(list->head->status);
    list->head->status = NULL;
    free(list->head->condition);
    list->head->condition = NULL;
    free(list->head);
    list->head = temp;
}

void removeNodes(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    while (isEmpty(list) == false) {
        deleteFrontNode(list, familyName, firstName, address, phoneNumber, status, condition);
    }
    list->head = NULL;
}

void freeVariables(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    free(familyName);
    familyName = NULL;
    free(firstName);
    firstName = NULL;
    free(address);
    address = NULL;
    free(phoneNumber);
    phoneNumber = NULL;
    free(status);
    status = NULL;
    free(condition);
    condition = NULL;
}
