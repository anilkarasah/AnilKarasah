#include <stdio.h>
#define MAX 100

int array[MAX];
int address[MAX] = {-2};
int n;
int head = 0;
int i;

void addToList(int input)
{
	int j;

	if (address[0] == -2)
	{
		// no elements on the list
		address[0] = -1;
		return;
	}

	if (input <= array[head])
	{
		// new element should be added before the head
		address[i] = head;
		head = i;
		return;
	}

	j = head;
	while (address[j] != -1 && input >= array[address[j]])
		j = address[j];

	address[i] = address[j];
	address[j] = i;
}

void printList()
{
	int j;
	printf("  ARRAY ADDRESS");
	for (j = 0; j < n; ++j)
	{
		printf("\n%d:%5d %6d", j, array[j], address[j]);
	}
	printf("\n\n");
	j = head;
	while (j != -1)
	{
		printf("%4d", array[j]);
		j = address[j];
	}

	printf("\n\nhead: %d", head);
}

int main()
{
	int input;

	printf("n = ");
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
	{
		scanf("%d", &array[i]);
		addToList(array[i]);
	}

	printList();

	printf("\n\nEnter new element: ");
	scanf("%d", &input);
	addToList(input);
	array[n] = input;
	n++;

	printList();

	return 0;
}