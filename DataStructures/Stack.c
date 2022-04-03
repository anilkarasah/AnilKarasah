#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct
{
    int top;
    int arr[MAX];
} STACK;

typedef struct
{
    int value;
    short errorFlag;
} result;

STACK s;

void initStack();
int isEmpty();
int isFull();
int push(int value);
result pop();
result peek();

int main()
{
    int menuSelector;
    int value;
    short errorFlag; // 1: Error, 0: No error
    result res;
    initStack();

    printf("Stack Implementation\n");
    do
    {
        printf("1) Push element to stack\n");
        printf("2) Pop element from stack\n");
        printf("3) See the top of the stack\n");
        printf("OTHERWISE Exit\n");

        printf("\n> ");
        scanf("%d", &menuSelector);

        switch (menuSelector)
        {
        case 1:
            printf("\n\t> Enter value: ");
            scanf("%d", &value);
            errorFlag = push(value);

            if (errorFlag)
                printf("\n\t!!! Can't push item because stack is full !!!\n");
            else
                printf("\n\tPushed element.\n");

            break;
        case 2:
            res = pop();

            if (res.errorFlag)
                printf("\n\t!!! Can't pop item because stack is empty !!!\n");
            else
                printf("\n\tPopped element: %d\n", res.value);

            break;
        case 3:
            res = peek();

            if (res.errorFlag)
                printf("\n\t!!! Can't peek item because stack is empty !!!\n");
            else
                printf("\n\tElement at the top of the stack: %d\n", res.value);

            break;
        }
    } while (menuSelector > 0 && menuSelector <= 3);

    return 0;
}

void initStack()
{
    s.top = -1;
}

int isEmpty()
{
    if (s.top == -1)
        return 1;

    return 0;
}

int isFull()
{
    if (s.top == MAX - 1)
        return 1;

    return 0;
}

int push(int value)
{
    if (isFull())
        return 1;

    s.arr[++s.top] = value;

    return 0;
}

result pop()
{
    result res;

    if (isEmpty())
    {
        res.errorFlag = 1;
        return res;
    }

    res.errorFlag = 0;
    res.value = s.arr[s.top--];

    return res;
}

result peek()
{
    result res;

    if (isEmpty())
    {
        res.errorFlag = 1;
        return res;
    }

    res.errorFlag = 0;
    res.value = s.arr[s.top];

    return res;
}