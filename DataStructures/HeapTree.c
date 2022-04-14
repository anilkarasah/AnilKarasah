#include <stdio.h>
#include <stdlib.h>

#define MAX 10
typedef struct
{
    int arr[MAX];
    int size;
} heap;

heap h;

void initHeap()
{
    h.size = 0;
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void heapify(int index)
{
    int i = (index - 1) / 2;
    while (index > 0 && h.arr[index] > h.arr[i])
    {
        swap(&h.arr[i], &h.arr[index]);
        index = i;
        i = (i - 1) / 2;
    }
}

void addToHeap(int value)
{
    h.arr[h.size] = value;
    heapify(h.size);
    h.size++;
}

void printHeap()
{
    int i;

    for (i = 0; i < h.size; i++)
        printf("%4d", i);
    printf("\n");
    for (i = 0; i < h.size; i++)
        printf("%4d", h.arr[i]);
    printf("\n\n");
}

int main()
{
    int arr[MAX] = {20, 12, 18, 2, 4, 1, 1, 3, 10, 30};
    int i;

    initHeap();

    for (i = 0; i < MAX; i++)
        printf("%4d", i);
    printf("\n");
    for (i = 0; i < MAX; i++)
        printf("%4d", arr[i]);

    printf("\n\n");

    for (i = 0; i < MAX; i++)
    {
        addToHeap(arr[i]);
    }
    printHeap();

    return 0;
}
