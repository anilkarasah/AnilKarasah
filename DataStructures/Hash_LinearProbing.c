#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 50
#define DATASET_SIZE 25

#define TRUE 1
#define FALSE 0

typedef struct {
    int isNull;
    int value;
} hashelement;

void initHashTable(hashelement hashtable[TABLE_SIZE]);
void createRandomArray(int arr[DATASET_SIZE], int from, int to);
void doesValueExist(hashelement hashtable[TABLE_SIZE], int key);
void addToHashset(hashelement hashtable[TABLE_SIZE], int key);
int hash(int key);
int hashFunction(int key, int i);
void printArray(int arr[DATASET_SIZE]);
void printHashTable(hashelement hashtable[TABLE_SIZE]);

int main() {
    srand(time(NULL));
    int arr[DATASET_SIZE];
    int menu;
    hashelement hashtable[TABLE_SIZE];

    while (TRUE) {
        printf("HASH TABLE using LINEAR PROBING approach\n");
        printf("Choose an operation *------------------*\n");
        printf("1) Generate a random integer array\n");
        printf("2) Provide your integer array\n");
        printf("OTHERWISE Exit\n");
        printf("> ");
        scanf("%d", &menu);

        if (menu == 1) {
            // Generate random array
            int from, to;
            printf("Lower limit of random integers: ");
            scanf("%d", &from);
            printf("Higher limit of random integers: ");
            scanf("%d", &to);
            createRandomArray(arr, from, to);
        } else if (menu == 2) {
            printf("You must provide %d integer values!\n", DATASET_SIZE);
            for (int i = 0; i < DATASET_SIZE; i++) {
                printf("array[%d]: ", i);
                scanf("%d", &arr[i]);
            }
        } else {
            break;
        }

        // Initialize hash table and fill it with the given integer values
        printf("\n>>   Hash table is now being generated   <<\n");
        initHashTable(hashtable);
        for (int i = 0; i < DATASET_SIZE; i++)
            addToHashset(hashtable, arr[i]);
        printf(">> Hash table has generated successfully <<\n\n");

        do {
            printf("\nChoose an operation:\n");
            printf("1) Print the integer array\n");
            printf("2) Find an element\n");
            printf("3) Print hash table\n");
            printf("OTHERWISE Reselect values for integer array\n");
            printf("> ");
            scanf("%d", &menu);

            int searchingFor;
            switch (menu) {
                case 1:
                    printArray(arr);
                    break;
                case 2:
                    // printf("WIP\n");
                    printf("Which value you are searching for: ");
                    scanf("%d", &searchingFor);
                    doesValueExist(hashtable, searchingFor);
                    break;
                case 3:
                    printHashTable(hashtable);
                    break;
            }
        } while (menu >= 1 && menu <= 3);
    }

    return 0;
}

void initHashTable(hashelement hashtable[TABLE_SIZE]) {
    for (int i = 0; i < TABLE_SIZE; i++)
        hashtable[i].isNull = TRUE;
}

void createRandomArray(int arr[DATASET_SIZE], int from, int to) {
    int range = to - from;
    for (int i = 0; i < DATASET_SIZE; i++)
        arr[i] = rand() % range + from;
}

void addToHashset(hashelement hashtable[TABLE_SIZE], int key) {
    int i = 0;
    int adr;
    do {
        adr = hashFunction(key, i);
        i++;
    } while (!(hashtable[adr].isNull) && hashtable[adr].value != key && i < TABLE_SIZE);

    if (i == TABLE_SIZE) {
        printf("Table is full!\n");
    } else if (hashtable[adr].isNull) {
        hashtable[adr].value = key;
        hashtable[adr].isNull = FALSE;
    } else {
        printf("This key(%d) already exists!\n", key);
    }
}

void doesValueExist(hashelement hashtable[TABLE_SIZE], int key) {
    int i = 0;
    int adr;

    do {
        adr = hashFunction(key, i);
        i++;
    } while (!(hashtable[adr].isNull) && hashtable[adr].value != key && i < TABLE_SIZE);

    if (hashtable[adr].value == key) {
        printf(">> %d exists!\n", key);
    } else {
        printf(">> %d does not exist!\n", key);
    }
}

int hash(int key) {
    return key % TABLE_SIZE;
}

int hashFunction(int key, int i) {
    return (key + i) % TABLE_SIZE;
}

void printArray(int arr[DATASET_SIZE]) {
    for (int i = 0; i < DATASET_SIZE; i++)
        printf("%4d", arr[i]);
    printf("\n");
}

void printHashTable(hashelement hashtable[TABLE_SIZE]) {
    printf("NULLFLAG    VALUE");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("\n%3d) ", i);
        if (hashtable[i].isNull)
            printf("    null");
        else
            printf("not null %8d", hashtable[i].value);
    }
}
