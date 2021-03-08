#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[128];
typedef enum { false, true } bool;
typedef enum { bird, fish, insect, mammal } typeAnimal;
typedef struct {
    typeAnimal type;
    double size;
    String name;
} Animal;

bool informAnimal (Animal* a);
typeAnimal typeFromString (String type);
char* stringFromType (typeAnimal type);
void makeRoom (Animal*** found, int* size);
void printAnimals (Animal** found, int size);


int main (void) {
    int maxSize = 1, currentIndex = -1;
    Animal** found = malloc(sizeof(Animal *));

    while (true) {
        Animal* a = malloc(sizeof(Animal));
        if (++currentIndex >= maxSize) {
            makeRoom(&found, &maxSize);
        }
        if (!informAnimal(a)) {
            break;
        } else {
            *(found + currentIndex) = a;
        }
    }

    printAnimals(found, currentIndex);

    return 0;
}

// retrieves all data from the user
bool informAnimal (Animal* a) {
    String type;

    printf("Enter animal information (\"exit\" as name to exit)\n");

    printf("What is the name: ");
    scanf("%s", a->name);

    if (!strcmp(a->name, "exit")) {
        return false;
    }

    printf("What is the size: ");
    scanf("%lf", &a->size);

    printf("What is the type: ");
    scanf("%s", type);

    a->type = typeFromString(type);

    return true;
}

// finds type from input
typeAnimal typeFromString (String type) {
    if (!strcmp(type, "bird")) {
        return bird;
    } else if (!strcmp(type, "fish")) {
        return fish;
    } else if (!strcmp(type, "insect")) {
        return insect;
    } else if (!strcmp(type, "mammal")) {
        return mammal;
    } else {
        perror("invalid animal type. exiting");
        exit(-1);
    }
}

// finds whichever string it is
char* stringFromType (typeAnimal type) {
    switch (type) {
        case bird:      return "bird";
        case fish:      return "fish";
        case insect:    return "insect";
        case mammal:    return "mammal";
        default:        return "error";
    }
}

// reallocates the space in the list multiplying by 2
void makeRoom (Animal*** found, int* size) {
    *size *= 2;
    *found = realloc(*found, *size *sizeof(Animal*));
    if (*found == NULL) {
        perror("memory could not be reallocated. exiting.");
        exit(-1);
    }
}

// prints out all the animal data
void printAnimals (Animal** found, int size) {
    int i;
    Animal* a;
    printf("The following new species were found:\n");
    for (i = 0; i < size; i++) {
        a = *(found + i);
        printf("%-25s has size %5.2f and is a %s\n", a->name, a->size, stringFromType(a->type));
    }
}
