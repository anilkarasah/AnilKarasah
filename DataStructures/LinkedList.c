#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef node *list;

void newNode(list *head, int value)
{
    list newNode = (list)malloc(sizeof(node));

    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}

list findNode(list head, int value)
{
    while (head != NULL)
    {
        if (head->value == value)
            return head;
        head = head->next;
    }
    return NULL;
}

void removeNode(list *head, int value)
{
    list tmp = *head;
    list toDelete;

    if ((*head)->value == value)
    {
        *head = (*head)->next;
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

void traverseList(list head)
{
    int menu;
    do
    {
        printf("Current element: %d\nEnter 1 for next.\n> ", head->value);
        scanf("%d", &menu);
        if (menu == 1)
            head = head->next;
    } while (menu == 1 && head != NULL);

    printf("End of list!\n");
}

void printList(list head)
{
    printf("[");
    while (head != NULL)
    {
        printf("%d, ", head->value);
        head = head->next;
    }
    printf("]\n");
}

void freeList(list head)
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
    list head = NULL;
    list temp;

    newNode(&head, 5);
    newNode(&head, 17);
    newNode(&head, 22);
    newNode(&head, 13);
    newNode(&head, -17);
    newNode(&head, 6);

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
            newNode(&head, userInput);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &userInput);
            temp = findNode(head, userInput);
            if (temp != NULL)
                printf("Element exists on the list!\n");
            else
                printf("Element does not exist!\n");
            break;
        case 3:
            printf("Enter value: ");
            scanf("%d", &userInput);
            removeNode(&head, userInput);
            break;
        case 4:
            traverseList(head);
            break;
        case 5:
            printList(head);
            break;
        }
    } while (menu >= 1 && menu <= 5);

    freeList(head);

    return 0;
}