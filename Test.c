#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int frequency;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

Node *insert(Node *root, int data, int frequency);
void preOrder(Node *root);
void readingFile(FILE *file, Node **root);


int main()
{
    Node *root = NULL;
    FILE *file = fopen("input.txt", "r");
    readingFile(file, &root);
    printf("Pre-order traversal of constructed tree : ");
    preOrder(root);
    return 0;
}


Node *insert(Node *root, int data, int frequency)
{
   
    if (root == NULL)
    {
        root = (Node *)malloc(sizeof(Node));
        if (root == NULL)
            return 0;
        

        root->data = data;
        root->frequency = frequency;
        root->left = root->right = NULL;
        return root;
    }

  
    if (data < root->data)
    {
        root->left = insert(root->left, data, frequency);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data, frequency);
    }
  

    return root;
}


void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%d,", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void readingFile(FILE *file, Node **root){
    int data, frequency;
    while (fscanf(file, "%d, %d", &data, &frequency) == 2)
    {
        *root = insert(*root, data, frequency);
    }
    fclose(file);
}

