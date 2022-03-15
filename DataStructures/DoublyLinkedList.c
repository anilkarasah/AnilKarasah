#include <stdio.h>
#include <stdlib.h>

// HAVEN'T FINISHED YET

typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} node;

typedef node *list;
list head = NULL;

void newNode(int value)
{
    list element = (list) malloc(sizeof(node));
    
    if (head == NULL) {
        head = element;
        head->value = value;
        head->prev = head->next = NULL;
        return;
    }

    element->value = value;
    element->next = head;
    element->prev = NULL;
    head->prev = element;
    head = element;
}

list findNode(int value)
{
    list tmp = head;
    while (tmp != NULL)
    {
        if (tmp->value == value)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void removeNode(int value)
{
    list tmp = head;
    list toDelete;

    if (head->value == value)
    {
        head = head->next;
        free(tmp);
        return;
    }

    while (tmp->next != NULL && tmp->next->value != value)
        tmp = tmp->next;

    if (tmp->next == NULL)
    {
        printf("Element not found in list!\n");
        return;
    }

    toDelete = tmp->next;
    tmp->next = toDelete->next;
    free(toDelete);
}

void traverseList()
{
    int menu;
    list tmp = head;
    do
    {
        printf("Current element: %d\n", tmp->value);
        
        if (tmp->next != NULL)
            printf("Enter 1 for next.\n");
        
        if (tmp->prev != NULL)
            printf("Enter 2 for previous.\n");

        printf("> ");
        scanf("%d", &menu);

        if (menu == 1)
            tmp = tmp->next;
        if (menu == 2)
            tmp = tmp->prev;
    } while ((menu == 1 || menu == 2) && tmp != NULL);

    printf("End of list!\n\n");
}

void printList()
{
    list tmp = head;
    printf("[");
    while (tmp != NULL)
    {
        printf("%d, ", tmp->value);
        tmp = tmp->next;
    }
    printf("]\n");
}

void freeList()
{
    list tmp;
    while (tmp != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    printf("Deallocation successful!\n");
}

int main()
{
    int menu;
    int userInput;
    list temp;

    newNode(5);
    newNode(17);
    newNode(22);
    newNode(13);
    newNode(-17);
    newNode(6);

    do
    {
        printf("Linked List\n");
        printf("\t1) Add node\n");
        printf("\t2) Find value\n");
        printf("\t3) Remove value\n");
        printf("\t4) Traverse list\n");
        printf("\t5) Print list\n\n\t> ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &userInput);
            newNode(userInput);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &userInput);
            temp = findNode(userInput);
            if (temp != NULL)
                printf("Element exists on the list!\n");
            else
                printf("Element does not exist!\n");
            break;
        case 3:
            printf("Enter value: ");
            scanf("%d", &userInput);
            removeNode(userInput);
            break;
        case 4:
            traverseList();
            break;
        case 5:
            printList();
            break;
        }
    } while (menu >= 1 && menu <= 5);

    freeList();

    return 0;
}
