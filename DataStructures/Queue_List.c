#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct
{
    node *front;
    node *rear;
} queue;

typedef struct
{
    int value;
    short errorFlag;
} result;

queue q;

void initQueue();
int isEmpty();
int enqueue(int value);
result dequeue();
result peek();
void freeList();

int main()
{
    int menuSelector;
    int value;
    short errorFlag; // 1: Error, 0: No error
    result res;
    int i;
    initQueue();

    printf("Queue Implementation\n");
    do
    {
        printf("1) Add element to queue\n");
        printf("2) Remove element from queue\n");
        printf("3) See the next element of the queue\n");
        printf("OTHERWISE Exit\n");

        printf("\n> ");
        scanf("%d", &menuSelector);

        switch (menuSelector)
        {
        case 1:
            printf("\n\t> Enter value: ");
            scanf("%d", &value);
            errorFlag = enqueue(value);

            if (errorFlag)
                printf("\n\t!!! Can't add item because memory allocation failed !!!\n");
            else
                printf("\n\tAdded element.\n");

            break;
        case 2:
            res = dequeue();

            if (res.errorFlag)
                printf("\n\t!!! Can't remove item because queue is empty !!!\n");
            else
                printf("\n\tRemoved element: %d\n", res.value);

            break;
        case 3:
            res = peek();

            if (res.errorFlag)
                printf("\n\t!!! Can't show next item because queue is empty !!!\n");
            else
                printf("\n\tNext element of the queue: %d\n", res.value);

            break;
        }
    } while (menuSelector > 0 && menuSelector <= 3);

    freeList();

    return 0;
}

void initQueue()
{
    q.front = q.rear = NULL;
}

int isEmpty()
{
    return (q.front == NULL);
}

int enqueue(int value)
{
    node *temp = (node *)malloc(sizeof(node));
    if (temp == NULL)
        return 1;

    if (isEmpty())
    {
        q.front = q.rear = temp;
        q.front->value = value;
        q.front->next = NULL;
        return 0;
    }

    q.rear->next = temp;
    q.rear = temp;
    q.rear->value = value;
    q.rear->next = NULL;
    return 0;
}

result dequeue()
{
    node *temp;
    result res;

    if (q.front == NULL)
    {
        res.errorFlag = 1;
    }
    else
    {
        res.errorFlag = 0;
        res.value = q.front->value;
        temp = q.front;
        q.front = q.front->next;
        free(temp);
    }

    return res;
}

result peek()
{
    result res;

    if (isEmpty())
        res.errorFlag = 1;
    else
    {
        res.errorFlag = 0;
        res.value = q.front->value;
    }
    return res;
}

void freeList()
{
    node *nextNode = q.front;
    while (nextNode != NULL)
    {
        nextNode = q.front->next;
        free(q.front);
        q.front = nextNode;
    }
    printf("List cleared from the memory!\n");
}
