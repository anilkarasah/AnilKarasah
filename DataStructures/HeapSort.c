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
    int arr[MAX] = {30, 20, 18, 10, 12, 1, 1, 2, 3, 4};
    int i;
    for (i = 0; i < MAX; i++)
        h.arr[i] = arr[i];
    h.size = MAX;
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void heapify(int index)
{
    int largestChild = index;
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;

    if (leftChild < h.size && h.arr[leftChild] > h.arr[largestChild])
        largestChild = leftChild;

    if (rightChild < h.size && h.arr[rightChild] > h.arr[largestChild])
        largestChild = rightChild;

    if (largestChild != index)
    {
        swap(&h.arr[largestChild], &h.arr[index]);
        heapify(largestChild);
    }
}

void printHeap()
{
    int i;

    for (i = 0; i < MAX; i++)
        printf("%4d", i);
    printf("\n");
    for (i = 0; i < MAX; i++)
        printf("%4d", h.arr[i]);
    printf("\n\n");
}

void heapSort()
{
    int i;
    for (i = h.size - 1; i >= 0; i--)
    {
        swap(&h.arr[0], &h.arr[i]);

        h.size--;
        heapify(0);
    }
}

int main()
{
    initHeap();

    printf("Heap tree:\n");
    printHeap();

    heapSort();
    printf("Sorted tree:\n");
    printHeap();

    return 0;
}
