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


int main()
{
    Node *root = NULL;
    char inputFile[25];
    scanf("%s", inputFile);
    FILE *file = fopen(inputFile, "r");
    readingFile(file, &root);
    printf("Pre-order traversal of constructed tree : ");
    rotateTree(&root);
    preOrder(root, 0);
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

//This function makes preorder traversal.
void preOrder(Node *root, int isChild)
{
    if (root != NULL)
    {
        if(isChild)
            printf(",");
        printf("%d", root->data);
        preOrder(root->left,1);
        preOrder(root->right,1);

    }
}
//This function reads input from a file then invokes insert function to create nodes
//In this function, double pointers are used for changing pointer's value.
void readingFile(FILE *file, Node **root){
    int data, frequency;
    while (fscanf(file, "%d, %d", &data, &frequency) == 2)
    {
        *root = insert(*root, data, frequency);
    }
    fclose(file);
}
//This function makes the right child the new root. Previous root is left child of new root.
Node *rightChildToRoot(Node *root){
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
//This function makes the left child the new root. Previous root is right child of new root.
Node *leftChildToRoot(Node * root){
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}
/*This function changes the pointers of nodes to update this tree
 * with frequency values of nodes. The double pointer is required
 * to change pointer's pointer value*/
void rotateTree(Node** node) {
    //Until find the leaves, this function makes recursive calls.
    if ((*node)->left != NULL) {
        rotateTree(&(*node)->left);
        //If frequency value of root's left child is bigger than root, their positions are changed.
        if ((*node)->frequency < (*node)->left->frequency) {
            (*node) = leftChildToRoot((*node));
        }
        //To check right child of left child.
        if ((*node)->right != NULL)
            rotateTree(&(*node)->right);
    }
    if ((*node)->right != NULL) {
       rotateTree(&(*node)->right);
        //If frequency value of root's right child is bigger than root, their positions are changed.
        if ((*node)->frequency < (*node)->right->frequency) {
            (*node) = rightChildToRoot((*node));
        }
        //To check left child of right child.
        if ((*node)->left != NULL)
            rotateTree(&(*node)->left);
    }
}
