#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int value;
    struct treenode *left;
    struct treenode *right;
} tree;

tree *root = NULL;

tree *initNode(int value);
tree *addNode(tree *node, int value);
tree *findNode(tree *node, int value);
void printInorder(tree *node);

int main()
{
    int menuSelector;
    int value;
    tree *node;

    addNode(root, 10);
    addNode(root, 12);
    addNode(root, 17);
    addNode(root, 3);
    addNode(root, 20);
    addNode(root, 18);
    addNode(root, 25);

    printf("Binary Search Tree Implementation\n");
    do
    {
        printf("1) Add element to the tree\n");
        printf("2) Find value in the tree\n");
        printf("3) Print tree (in-order)\n");
        printf("OTHERWISE Exit\n");

        printf("\n> ");
        scanf("%d", &menuSelector);

        switch (menuSelector)
        {
        case 1:
            printf("\n\t> Enter value: ");
            scanf("%d", &value);

            addNode(root, value);

            break;
        case 2:
            printf("\n\t> Enter value: ");
            scanf("%d", &value);

            node = findNode(root, value);

            if (node == NULL)
                printf("Element not found!\n");
            else
                printf("%d is found!\n", node->value);

            break;
        case 3:
            printInorder(root);
            printf("\n");
            break;
        }
    } while (menuSelector > 0 && menuSelector <= 3);
    return 0;
}

tree *initNode(int value)
{
    tree *node = (tree *)malloc(sizeof(tree));
    node->value = value;
    node->left = node->right = NULL;

    return node;
}

tree *addNode(tree *node, int value)
{
    // tree *node = findNode(root, value);
    // tree *temp = initNode(value);

    // if (node == NULL)
    // {
    //     // Then, the tree is not initialized yet
    //     // So, we must allocate the root node
    //     root = temp;
    //     return;
    // }

    // if (node->value <= value)
    // {
    //     node->right = temp;
    //     return;
    // }
    // else
    //     node->left = temp;
    if (node == NULL)
        return initNode(value);

    if (value > node->value)
        node->left = addNode(node->left, value);
    else if (value > node->value)
        node->right = addNode(node->right, value);

    return node;
}

tree *findNode(tree *currNode, int value)
{
    if (currNode == NULL)
        return NULL;

    if (currNode->value == value)
        return currNode;

    if (currNode->value > value)
    {
        if (currNode->left == NULL)
            return currNode;
        else
            return findNode(currNode->left, value);
    }

    if (currNode->value < value)
    {
        if (currNode->right == NULL)
            return currNode;
        else
            return findNode(currNode->right, value);
    }
}

void printInorder(tree *node)
{
    if (node == NULL)
        return;

    printInorder(node->left);

    printf("%4d ", node->value);

    printInorder(node->right);
}
