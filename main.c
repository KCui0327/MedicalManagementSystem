/*
* Project: Medical Management System
* File: main.c
* Date: July 25, 2022
* Name: Kenny Cui
* -------------------------------------------------------------------
* Description: This program composes of a medical management system that
* allows the user to create, modify, and delete patients, and their
* medical records. The user can also view the records of all patients.
* -------------------------------------------------------------------
*/

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
Node *createNode(Node *next, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void printList(LinkedList *list);
void printNodePatientName(LinkedList *list, char *familyName, char *firstName);
bool isEmpty(LinkedList *list);
void addNodeFront(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
bool deletePatient(LinkedList *list, char *familyName, char *firstName);
bool searchPatient(LinkedList *list, char *familyName, char *firstName);
bool searchPhoneNumber(LinkedList *list, char *phoneNumber);
bool searchStatus(LinkedList *list, char *status);
bool searchCondition(LinkedList *list, char *condition);
void printNodeStatus(LinkedList *list, char *status);
void printNodeCondition(LinkedList *list, char *phoneNumber);
void printNodePhoneNumber(LinkedList *list, char *phoneNumber);
void addNodeInorder(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void removeNodes(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);
void freeVariables(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition);

int main(int argc, char* argv[]) {
    char input[MAX_SIZE + 1], command;
    char *familyName, *firstName, *address, *phoneNumber, *status, *condition;
    const char introString[]
            = "Medical Management System.\n\n";
    const char functionString[]
            = "List of Commands: \n - Insert (I) \n - Delete (D) \n - S (search by patient's name) \n "
              "- L (search by status) \n - O (search by condition) \n"
              " - N (search by phone number) \n - Print (P) \n - Reset (R) \n - Exit (E)";

    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;

    printf("%s", introString);
    printf("%s\n", functionString);

    do {
        printf("\nEnter command: ");
        getCommand(input, MAX_SIZE + 1); // get command from user
        command = toupper(input[0]);

        familyName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        firstName = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        address = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        phoneNumber = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        status = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);
        condition = (char *)malloc((sizeof(char)) * MAX_SIZE + 1);

        switch(command) { // determines action from command
            case 'I': // insert
                getInputNode(familyName, firstName, address, phoneNumber, status, condition);
                if (searchPatient(list, familyName, firstName)) {
                    printf("\nPatient already exists.\n");
                    freeVariables(familyName, firstName, address, phoneNumber, status, condition);
                } else {
                    addNodeInorder(list, familyName, firstName, address, phoneNumber, status, condition);
                }
                break;
            case 'D': // delete
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
            case 'S': // search by name
                printf("  Family name: ");
                getCommand(familyName, MAX_SIZE);
                printf("  First name: ");
                getCommand(firstName, MAX_SIZE);
                if (searchPatient(list, familyName, firstName)) { // if patient exists, print node
                    printNodePatientName(list, familyName, firstName);
                } else { // if patient does not exist, print message
                    printf("\nThere is no such patient named %s %s", firstName, familyName);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition); // free variables
                break;
            case 'L': // search by status
                printf("  Status: ");
                getCommand(status, MAX_SIZE); // get status from user
                if (searchStatus(list, status)) { // if status exists, print nodes with that status
                    printNodeStatus(list, status);
                } else { // if status does not exist, print message
                    printf("\nThere is no patient with status \"%s\"", status);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition); // free variables
                break;
            case 'O': // search by condition
                printf("  Condition: ");
                getCommand(condition, MAX_SIZE); // get condition from user
                if (searchCondition(list, condition)) { // if condition exists, print nodes with that condition
                    printNodeCondition(list, condition);
                } else { // if condition does not exist, print message
                    printf("\nThere is no patient with condition \"%s\"", condition);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition); // free variables
                break;
            case 'N': // search by phone number
                printf("  Phone number: ");
                getCommand(phoneNumber, MAX_SIZE);
                if (searchPhoneNumber(list, phoneNumber)) { // if phone number exists, print node
                    printNodePhoneNumber(list, phoneNumber);
                } else { // if phone number does not exist, print message
                    printf("\nThere is no patient with this phone number %s", phoneNumber);
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition); // free variables
                break;
            case 'P': // print
                if (list->head != NULL) { // if list is not empty, print list
                    printList(list);
                } else { // if list is empty, print message
                    printf("\nThere is no patient in the list.");
                }
                freeVariables(familyName, firstName, address, phoneNumber, status, condition); // free variables
                break;
            case 'R': // reset
                removeNodes(list, familyName, firstName, address, phoneNumber, status, condition); // remove all nodes
                printf("\nSystem has been reset.\n");
                break;
            case 'E': // exit
                removeNodes(list, familyName, firstName, address, phoneNumber, status, condition); // remove all nodes
                break;
            default:
                printf("\nInvalid command.\n\n");
                puts(functionString);
                break;
        }

    } while (command != 'E'); // exit when command is 'E'

    removeNodes(list, familyName, firstName, address, phoneNumber, status, condition);
    free(list); // free list

    printf("\nSystem has been exited.\n");

    return 0; // exit program
}

// get command from user
void getCommand(char *input, int inputSize) {
    int i, maxSize = inputSize - 1;
    char c;
    for (i = 0; i < maxSize && ((c = getchar()) != '\n'); i++) {
        input[i] = c; // store command in input
    }
    input[i] = '\0'; // add null terminator
}

// get input from user and store in node
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

// create new node
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

// check if list is empty
bool isEmpty(LinkedList *list) {
    return list->head == NULL;
}

// print list
void printList(LinkedList *list) {
    Node *currentNode = list->head;
    printf("\n");
    while (currentNode != NULL) {
        printf("%s\n", currentNode->familyName);
        printf("%s\n", currentNode->firstName);
        printf("%s\n", currentNode->address);
        printf("%s\n", currentNode->phoneNumber);
        printf("%s\n", currentNode->status);
        printf("%s\n", currentNode->condition);
        if (currentNode->next != NULL) {
            printf("\n");
        }
        currentNode = currentNode->next;
    }
}

// print node if family name and first name match
void printNodePatientName(LinkedList *list, char *familyName, char *firstName) {
    Node *currentNode = list->head;
    printf("\n");
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

// print node if status matches
void printNodeStatus(LinkedList *list, char *status) {
    Node *currentNode = list->head;
    printf("\n");
    while (currentNode != NULL) {
        if (strcmp(status, currentNode->status) == 0) {
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

// print node if condition matches
void printNodeCondition(LinkedList *list, char *condition) {
    Node *currentNode = list->head;
    printf("\n");
    while (currentNode != NULL) {
        if (strcmp(condition, currentNode->condition) == 0) {
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

// print node if phone number matches
void printNodePhoneNumber(LinkedList *list, char *phoneNumber) {
    Node *currentNode = list->head;
    printf("\n");
    while (currentNode != NULL) {
        if (strcmp(phoneNumber, currentNode->phoneNumber) == 0) {
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

// add nodes to front of the list
void addNodeFront(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list)) { // if list is empty
        list->head = createNode(list->head, familyName, firstName, address, phoneNumber, status, condition);
        return;
    }

    Node *temp = createNode(list->head, familyName, firstName, address, phoneNumber, status, condition); // create new node
    if (temp != NULL) {
        temp->next = list->head; // set next node to head
        list->head = temp; // set head to new node
    }
}

// add nodes to end of the list
void addNodeInorder(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list) == true || strcmp(familyName, list->head->familyName) < 0) { // if list is empty or family name is less than head
        return addNodeFront(list, familyName, firstName, address, phoneNumber, status, condition); // add node to front of list
    }

    Node *currentNode = list->head;

    // traverse list until family name is less than current node family name
    while (currentNode->next != NULL) {
        if (strcmp(familyName, currentNode->familyName) < 0 && strcmp(familyName, currentNode->next->firstName) < 0) {
            break;
        }
        currentNode = currentNode->next;
    }

    Node *newNode = createNode(currentNode->next, familyName, firstName, address, phoneNumber, status, condition);
    if (newNode != NULL) {
        newNode->next = currentNode->next; // set next node to current node next
        currentNode->next = newNode; // set current node next to new node
    }
}

// searches if family name and first name match
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

// searches if status matches
bool searchStatus(LinkedList *list, char *status) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(currentNode->status, status) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

// searches if condition matches
bool searchCondition(LinkedList *list, char *condition) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (strcmp(currentNode->condition, condition) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

// searches if phone number matches
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

// deletes node if family name and first name match
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

// deletes nodes at the front of the list
void deleteFrontNode(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    if (isEmpty(list)) {
        return;
    }
    Node *temp = list->head->next; //
    free(list->head->familyName); //
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

// deletes nodes all nodes in list
void removeNodes(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    while (isEmpty(list) == false) { // while list is not empty
        deleteFrontNode(list, familyName, firstName, address, phoneNumber, status, condition); // delete front node
    }
    list->head = NULL; // set head to NULL
}

// frees all variables declared
void freeVariables(char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
    free(familyName);
    free(firstName);
    free(address);
    free(phoneNumber);
    free(status);
    free(condition);
}