#include <stdio.h>
#include <stdlib.h>
//Online version of this project is implemented in almost same way.
/* Binary Search Tree structure is implemented.
 * data -> A node's data value
 * frequency -> Data value's frequency which means how many times it is searched
 * left -> left child of a node
 * right -> right childe of a node
 */
struct node
{
    int data;
    int frequency;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

//Functions are defined firstly.
Node *insert(Node *root, int data, int frequency);
void preOrder(Node *root, int isChild);
void readingFile(FILE *file, Node **root);
void rotateTree(Node **node);
Node *rightChildToRoot(Node* root);
Node *leftChildToRoot(Node* root);
void search(Node* root, int data);
int main()
{
    int dataToSearch; //Number which is going to be searched
    Node *root = NULL;
    char inputFile[25];
    printf("Enter the name of the input file:");
    scanf("%s", inputFile);
    //Initial numbers in the BST are got from a input file.
    FILE *file = fopen(inputFile, "r");
    readingFile(file, &root);
    printf("Pre-order traversal of constructed tree :");
    preOrder(root,0);
    printf("\n");
    while(1 == 1) {
        //The user is constantly prompted which number to search for.
        printf(("Enter a value to search: "));
        scanf("%d", &dataToSearch);
        //The number is searched.
        search(root, dataToSearch);
        //All the necessary rotations are done and the new BST is printed.
        rotateTree(&root);
        printf("Pre-order traversal of constructed tree : ");
        preOrder(root,0);
        printf("\n");
    }
    return 0;
}

/* All initial values in the input file are inserted to BST in this "insert" function.
 * It takes Node pointer, data value and frequency of that node as parameters.
 * Frequency is taken as 0 initially in the online version.
 */
Node *insert(Node *root, int data, int frequency)
{
    //A node pointer is created and the given values are assigned that node.
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

    //Recursive insert function calls are used to insert the data value in an available node.
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

//This function makes pre-order traversal.
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
//This function reads input from a file then invokes insert function to create nodes
//In this function, double pointers are used for changing pointer's value.
void readingFile(FILE *file, Node **root){
    int data, frequency;
    while (fscanf(file, "%d", &data) == 1)
    {
        *root = insert(*root, data, 0);
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

            (*node) = rightChildToRoot((*node));
        }
        //To check right child of left child.
        if ((*node)->right != NULL)
            rotateTree(&(*node)->right);
    }
    if ((*node)->right != NULL) {
        rotateTree(&(*node)->right);
        //If frequency value of root's right child is bigger than root, their positions are changed.
        if ((*node)->frequency < (*node)->right->frequency) {

            (*node) = leftChildToRoot((*node));

        }
        //To check left child of right child.
        if ((*node)->left != NULL)
            rotateTree(&(*node)->left);
    }
}
/*This "search" function search the given value in the BST.
 * If it is found, its frequency is incremented by 1.
 */
void search(Node* root, int data){
   //The root is checked if it is null or not.
    if((root)!= NULL) {
        //If it is found, frequency is increasing.
        if (data == (root)->data) {
            ((root)->frequency)++;
        //If it is not found, it searches the left child of that node first.
        //It searches recursively
        } else if (data < (root)->data) {
            search(root->left, data);
        //The given value is not matched the left child of that node then it searches right child of that node.
        } else if (data > (root)->data) {
            search(root->right, data);
        }
    }
}
