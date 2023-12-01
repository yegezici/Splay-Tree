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
void rotateTree(Node **node);
Node *leftRotation(Node* node);
Node *rightRotation(Node* node);
void searchA(Node* root, int data);
int main()
{
    int dataToSearch;
    Node *root = NULL;
    FILE *file = fopen("input.txt", "r");
    readingFile(file, &root);
    while(1 == 1) {
        printf(("Enter a value to search: \n"));
        scanf("%d", &dataToSearch);
        if(dataToSearch == 0){
            break;
        }
        //printf("%d   ", dataToSearch);
        searchA(root, dataToSearch);
        rotateTree(&root);
        printf("Pre-order traversal of constructed tree : ");
        preOrder(root);
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
    while (fscanf(file, "%d", &data) == 1)
    {
        *root = insert(*root, data, 0);
    }
    fclose(file);
}
Node *leftRotation(Node *node){
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

Node *rightRotation(Node * node){
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

void rotateTree(Node** node) {
    //printf("%d \n",(*node)->data);
    if ((*node)->left != NULL) {
        rotateTree(&(*node)->left);
        if ((*node)->frequency < (*node)->left->frequency) {

            (*node) = rightRotation((*node));
        }
        if ((*node)->right != NULL)
            rotateTree(&(*node)->right);
    }
    if ((*node)->right != NULL) {
        rotateTree(&(*node)->right);
        if ((*node)->frequency < (*node)->right->frequency) {

            (*node) = leftRotation((*node));

        }
        if ((*node)->left != NULL)
            rotateTree(&(*node)->left);
    }
}

void searchA(Node* root, int data){
    if((root)!= NULL) {
        if (data == (root)->data) {
            ((root)->frequency)++;
            printf("%d \n",(root)->frequency);

        } else if (data < (root)->data) {
            searchA(root->left, data);

        } else if (data > (root)->data) {
            searchA(root->right, data);
        }
    }
}
