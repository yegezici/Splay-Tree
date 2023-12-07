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
void preOrder(Node *root, int isChild);
void readingFile(FILE *file, Node **root);
void rotateTree(Node **node);
Node *rightChildToRoot(Node* root);
Node *leftChildToRoot(Node* root);
void search(Node* root, int data);
int main()
{
    int dataToSearch;
    Node *root = NULL;
    char inputFile[25];
    scanf("%s", inputFile);
    FILE *file = fopen(inputFile, "r");
    readingFile(file, &root);
    printf("Pre-order traversal of constructed tree :");
    preOrder(root,0);
    printf("\n");
    while(1 == 1) {
        printf(("Enter a value to search: "));
        scanf("%d", &dataToSearch);
        search(root, dataToSearch);
        rotateTree(&root);
        printf("Pre-order traversal of constructed tree : ");
        preOrder(root,0);
        printf("\n");
    }
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
        root->left = NULL;
        root->right = NULL;
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


void preOrder(Node *root, int isChild)
{
    if (root != NULL)
    {
        if(isChild)
            printf(",");
        printf("(%d,%d)", root->data, root->frequency);
        preOrder(root->left,1);
        preOrder(root->right,1);

    }
}
void readingFile(FILE *file, Node **root){
    int data, frequency;
    while (fscanf(file, "%d", &data) == 1)
    {
        *root = insert(*root, data, 0);
    }
    fclose(file);
}
Node *rightChildToRoot(Node *root){
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}

Node *leftChildToRoot(Node * root){
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

void rotateTree(Node** node) {
    if ((*node)->left != NULL) {
        rotateTree(&(*node)->left);
        if ((*node)->frequency < (*node)->left->frequency) {

            (*node) = rightChildToRoot((*node));
        }
        if ((*node)->right != NULL)
            rotateTree(&(*node)->right);
    }
     if ((*node)->right != NULL) {
        rotateTree(&(*node)->right);
        if ((*node)->frequency < (*node)->right->frequency) {

            (*node) = leftChildToRoot((*node));

        }
        if ((*node)->left != NULL)
            rotateTree(&(*node)->left);
    }
}

void search(Node* root, int data){
    if((root)!= NULL) {
        if (data == (root)->data) {
            ((root)->frequency)++;
        } else if (data < (root)->data) {
            search(root->left, data);

        } else if (data > (root)->data) {
            search(root->right, data);
        }
    }
}
