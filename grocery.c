#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[128];
typedef enum { false, true } bool;
typedef struct {
    typeGroc type;
    int quantity;
    String name;
} Animal;

bool informGroc (Grocery* a);
void makeRoom (Grocery*** found, int* size);
void printList (Grocery** found, int size);


int main (void) {
    int maxSize = 1, currentIndex = -1;
    Grocery** found = malloc(sizeof(Grocery *));

    while (true) {
        Grocery* a = malloc(sizeof(Grocery));
        if (++currentIndex >= maxSize) {
            makeRoom(&found, &maxSize);
        }
        if (!informAnimal(a)) {
            break;
        } else {
            *(found + currentIndex) = a;
        }
    }

    printList(found, currentIndex);

    return 0;
}

// retrieves all data from the user
bool informGroc (Grocery* a) {
    String type;

    printf("Enter item information (\"exit\" as name to exit)\n");

    printf("What is the name: ");
    scanf("%s", a->name);

    if (!strcmp(a->name, "exit")) {
        return false;
    }

    printf("What is the price: ");
    scanf("%lf", &a->price);

    printf("How many are you buying?: ");
    scanf("%s", &a->quantity);

    return true;
}

// reallocates the space in the list multiplying by 2
void makeRoom (Grocery*** found, int* size) {
    *size *= 2;
    *found = realloc(*found, *size *sizeof(Grocery*));
    if (*found == NULL) {
        perror("memory could not be reallocated. exiting.");
        exit(-1);
    }
}

// prints out all the animal data
void printList (Grocery** found, int size) {
    int i;
    Grocery* a;
    printf("The following new species were found:\n");
    for (i = 0; i < size; i++) {
        a = *(found + i);
        printf("%-25s has size %5.2f and is a %s\n", a->name, a->size, stringFromType(a->type));
    }
}
