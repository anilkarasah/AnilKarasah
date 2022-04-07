#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int bytes;
    int isSigned;
} INPUT;

typedef struct
{
    int size;
    int top;
    int *arr;
} STACK;

STACK stack;

INPUT initInput(int value);
void initStack(INPUT input);
int isEmpty();
int isFull();
void push(int value);
int pop();
int peek();
void printBits(char *bits, int size);

int main()
{
    INPUT input;
    int value;
    int i;
    int bitSize;
    int counter = 0;
    char *bits;

    printf("Please enter an integer: ");
    scanf("%d", &value);

    input = initInput(value);
    initStack(input);

    value = input.value;
    bitSize = input.bytes * 8;

    bits = (char *)calloc(bitSize + 1, sizeof(char));
    if (bits == NULL)
    {
        printf("Malloc failure!\n");
        return -1;
    }

    // Pushing bits to stack
    for (i = 0; i < bitSize; i++)
    {
        push(!!(value % 2));
        value >>= 1;
    }

    // Popping bits and saving them to the string
    for (i = 0; i < bitSize; i++)
    {
        value = pop();
        bits[i] = '0' + value;

        // Counting the number of 0's which are popped from stack
        if (value == 0)
            counter++;
        else
            counter--;
    }

    printBits(bits, bitSize);
    // printf("%s\n", bits);
    if (counter == 0)
        printf("Equal amount of 0's and 1's\n");
    else if (counter > 0)
        printf("More 0's. %d more 1 is required.\n", counter);
    else
        printf("More 1's. %d more 0 is required.\n", -counter);

    free(bits);
    free(stack.arr);

    return 0;
}

void initStack(INPUT input)
{
    stack.top = -1;
    stack.size = input.bytes * 8;
    stack.arr = (int *)malloc(sizeof(int) * stack.size);
    if (stack.arr == NULL)
    {
        printf("Malloc failure!\n");
        exit(-1);
    }
}

int isEmpty()
{
    if (stack.top == -1)
        return 1;

    return 0;
}

int isFull()
{
    if (stack.top == stack.size - 1)
        return 1;

    return 0;
}

void push(int value)
{
    if (isFull())
    {
        printf("Can't push due to stack is full!\n");
        return;
    }

    stack.top++;
    stack.arr[stack.top] = value;
}

int pop()
{
    int value;

    if (isEmpty())
    {
        printf("Can't pop due to stack is empty!\n");
        return;
    }

    value = stack.arr[stack.top];
    stack.top--;

    return value;
}

int peek()
{
    return stack.arr[stack.top];
}

INPUT initInput(int value)
{
    INPUT input;
    int temp = value;
    int byteCounter = 0;

    input.value = value;

    if (value < 0)
    {
        input.isSigned = 1;

        if (value >= -0x80)
            byteCounter = 1;
        else if (value >= -0x8000)
            byteCounter = 2;
        else if (value >= -0x800000)
            byteCounter = 3;
        else
            byteCounter = 4;
    }
    else
    {
        input.isSigned = 0;

        if (value <= 0xFF)
            byteCounter = 1;
        else if (value <= 0xFFFF)
            byteCounter = 2;
        else if (value <= 0xFFFFFF)
            byteCounter = 3;
        else
            byteCounter = 4;
    }

    input.bytes = byteCounter;

    return input;
}

void printBits(char *bits, int size)
{
    int i;
    printf("\n");
    for (i = 0; i < size; i++)
    {
        if (i != 0 && i % 8 == 0)
            printf(" ");
        printf("%c", bits[i]);
    }
    printf("\n");
}
