#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ever (;;)

typedef char String[128];
typedef enum { false, true } bool;
typedef struct node {
    String name;
    struct node* next;
    struct node* bff;
} LLNode;

bool        addNation               (LLNode * head, LLNode * newNode);
void        addBestFriendsFiveEver  (LLNode * head);
LLNode*     findAllyInList          (LLNode * head, String name);
void        printAndFreeNodes       (LLNode * head);


int main (void) {
    LLNode * head = malloc(sizeof(LLNode));

    head->next = NULL;

    printf("enter -1 to stop entering nations\n");

    while ( addNation(head, malloc(sizeof(LLNode))) ) ;

    if (head->next == NULL) {
        printf("\nyou did not enter any nodes! ='( exiting program.\n");
        free(head);
        return -1;
    }

    addBestFriendsFiveEver(head);

    printf("\nThe battle credentials were leaked! Here is the information.\n\n");

    printAndFreeNodes(head);

    return 0;
}

bool addNation (LLNode * head, LLNode * newNode) {
    printf("Enter nation name:\t");
    scanf("%s", newNode->name);

    if (!strcmp(newNode->name, "-1")) {
        free(newNode);
        return false;
    } else {
        newNode->next = head->next;
        head->next = newNode;
        return true;
    }
}

void addBestFriendsFiveEver (LLNode * head) {
    String nameOfAlly;
    LLNode* foundAlly = NULL;
    LLNode* dummy = head;

    while (dummy->next != NULL) {
        dummy = dummy->next;

        for ever {
            printf("Enter the closest ally for %s:\t", dummy->name);
            scanf("%s", nameOfAlly);

            if (!strcmp(nameOfAlly, dummy->name)) {
                printf("You can't be allies with yourself in this program. Sorry!\n");
            } else if ((foundAlly = findAllyInList(head, nameOfAlly)) == NULL) {
                printf("That ally does not exist. Try again!\n");
            } else {
                break;
            }
        }
        dummy->bff = foundAlly;
    }
}

LLNode* findAllyInList (LLNode * head, String name) {
    LLNode* dummy = head;
    while (dummy->next != NULL) {
        dummy = dummy->next;
        if (!strcmp(name, dummy->name)) return dummy;
    }
    return NULL;
}

void printAndFreeNodes (LLNode * head) {
    int i = 0;
    LLNode* dummy;
    while (head->next != NULL) {
        dummy = head->next;
        free(head);
        head = dummy;
        printf("%d.  %s is\t\tallies with\t\t%s\n", ++i, head->name, head->bff->name);
    }
    free(head);
}
