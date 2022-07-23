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