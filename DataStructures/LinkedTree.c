#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *child;
    struct node *next;
} node;

node *initNode(int value);
void addChild(node *current, int value);
void printTree(node *root, int depth);
void printIndent(int amount);
void deallocTree(node *root);

int main()
{
    node *root = initNode(1000);
    node *traverse = root;
    int menu = 0, menu2, menu2flag;
    int value;

    // this is not required, but
    // i wanted it to be included
    // so you can test it easily
    root->child = initNode(20);
    root->child->next = initNode(17);
    root->child->next->next = initNode(35);
    root->child->next->next->child = initNode(200);
    root->child->next->next->child->child = initNode(81);
    root->child->next->child = initNode(400);
    root->child->next->child->child = initNode(65);
    root->child->next->child->child->next = initNode(91);
    root->child->next->child->next = initNode(5000);

    do
    {
        printf("\nCurrent node: %d\n\n", traverse->value);
        printf("Choose an operation:\n");
        printf("1) Traverse tree\n");
        printf("2) Add a child to the current node\n");
        printf("3) Print tree\n");
        printf("4) Traverse back to the root\n");
        printf("OTHERWISE Exit\n\n> ");

        scanf("%d", &menu);

        menu2flag = 1;
        switch (menu)
        {
        case 1:
            while (menu2flag)
            {
                printf("Value of current node: %d\n\n", traverse->value);
                menu2flag = 0;
                if (traverse->child == NULL)
                    printf("!! No child for this node.\n");
                else
                {
                    printf("1) Move to child node (its value: %d)\n", traverse->child->value);
                    menu2flag++;
                }
                if (traverse->next == NULL)
                    printf("!! No sibling for this node.\n");
                else
                {
                    printf("2) Move to next sibling node (its value: %d)\n", traverse->next->value);
                    menu2flag += 10;
                }
                printf("OTHERWISE Remain at this node.\n");
                if (menu2flag)
                {
                    printf("> ");
                    scanf("%d", &menu2);

                    if (menu2 == 1 && menu2flag % 10)
                        traverse = traverse->child;
                    else if (menu2 == 2 && menu2flag / 10)
                        traverse = traverse->next;
                    else
                        break;
                }
            }
            break;
        case 2:
            printf("Enter a value for the new node: ");
            scanf("%d", &value);

            addChild(traverse, value);

            break;
        case 3:
            printTree(root, 0);
            break;
        case 4:
            traverse = root;
            break;
        }
    } while (menu >= 1 && menu <= 4);

    deallocTree(root);

    return 0;
}

node *initNode(int value)
{
    node *newNode;
    if ((newNode = (node *)malloc(sizeof(node))) == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        exit(-1);
    }
    newNode->value = value;
    newNode->child = NULL;
    newNode->next = NULL;
    return newNode;
}

void addChild(node *current, int value)
{
    node *temp;
    node *newNode = initNode(value);

    temp = current->child;
    if (temp == NULL)
    {
        current->child = newNode;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void printTree(node *root, int depth)
{
    node *temp = root;
    if (root == NULL)
        return;

    printIndent(depth);
    printf("%d", root->value);
    printTree(root->next, depth);

    if (root->child == NULL)
        return;
    printf("\n\n--- Children of %d ---", root->value);
    printTree(root->child, depth + 1);
}

void printIndent(int amount)
{
    // prints indentation to the console
    // for visualizing children on nodes
    int i;
    printf("\n");
    for (i = 0; i < amount; i++)
        printf("\t");
}

void deallocTree(node *root)
{
    if (root == NULL)
        return;

    deallocTree(root->next);
    deallocTree(root->child);
    free(root);
}
