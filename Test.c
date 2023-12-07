#include <stdio.h>
#include <stdlib.h>
//This is a binary search tree structure
struct node
{
    int data;             //Data value in a node
    int frequency;        //Data value's frequency that represents how many times it is searched
    struct node *left;    //Left child of a node
    struct node *right;   //Right child of a node
};
typedef struct node Node;

 //Necessary functions are defined
Node *insert(Node *root, int data, int frequency);
void preOrder(Node *root, int isChild);
void readingFile(FILE *file, Node **root);
void rotateTree(Node **node);
Node *rightChildToRoot(Node* root);
Node *leftChildToRoot(Node* root);


int main()
{

    Node *root = NULL;
    //Getting input values from a given file
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
 //Newly created nodes are inserted to BST in this function
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

    //Nodes are inserted to BST according to their values.
    if (data < root->data)
    {
        //Recursive function calls are used for inserting the nodes.
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
