#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "node.c"

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

void addNodeFront(LinkedList *list, char *familyName, char *firstName, char *address, char *phoneNumber, char *status, char *condition) {
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



