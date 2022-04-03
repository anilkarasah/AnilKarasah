#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct
{
    int front;
    int rear;
    int arr[MAX];
} QUEUE;

typedef struct
{
    int value;
    short errorFlag;
} result;

QUEUE q;

void initQueue();
int isEmpty();
int isFull();
int enqueue(int value);
result dequeue();
result peek();

int main()
{
    int menuSelector;
    int value;
    short errorFlag; // 1: Error, 0: No error
    result res;
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
                printf("\n\t!!! Can't add item because queue is full !!!\n");
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
    return 0;
}

void initQueue()
{
    q.front = q.rear = 0;
}

int isEmpty()
{
    if (q.rear == q.front)
        return 1;

    return 0;
}

int isFull()
{
    if (q.rear > MAX - 1)
        return 1;

    return 0;
}

int enqueue(int value)
{
    if (isFull())
        return 1;

    q.arr[q.rear++] = value;
    return 0;
}

result dequeue()
{
    result res;

    if (isEmpty())
        res.errorFlag = 1;
    else
    {
        res.errorFlag = 0;
        res.value = q.arr[q.front++];
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
        res.value = q.arr[q.front];
    }

    return res;
}