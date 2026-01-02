#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ========= STRUCTURE =========


struct Node {
    char* key;
    float time;
    int FB;
    struct Node* right;
    struct Node* left;
};
typedef struct Node Node;


// ======== GLOBAL VAR =========


int comparisons = 0;
int rotations = 0;


// ========= PROTOTYPES =========


// AVL
Node* case1(Node* a, int* ok);
Node* case2(Node* a, int* ok);
Node* rotateRight(Node* p);
Node* rotateLeft(Node* p);
Node* rotateDoubleRight(Node* p);
Node* rotateDoubleLeft(Node* p);
Node* insertAVL(Node* a, char* name, float hours, int* ok);

// BST
Node* insertBST(Node* a, char* name, float hours);

// GENERAL
void preOrderTraversal(Node* a, int level);
Node* consult(Node* a, char* key);
int countHeight(Node *a);
int countNodes(Node* a);


// ============ AVL ============


// verify if rotation to the right needed
Node* case1(Node* a, int* ok)
{
    Node* z = a->left;
    if (z->FB == 1)
        a = rotateRight(a);
    else
        a = rotateDoubleRight(a);
    rotations++;

    a->FB = 0;
    *ok = 0;
    return a;
}


// verify if rotation to the left needed
Node* case2(Node* a, int* ok)
{
    Node* z = a->right;
    if (z->FB == -1)
        a = rotateLeft(a);
    else
        a = rotateDoubleLeft(a);
    rotations++;

    a->FB = 0;
    *ok = 0;
    return a;
}


// simples rotation to the right
Node* rotateRight(Node* p)
{
    Node* u = p->left;

    p->left = u->right;
    u->right = p;
    p->FB = 0;

    p = u;
    return p;
}


// simple rotation to the left
Node* rotateLeft(Node* p)
{
    Node* z = p->right;

    p->right = z->left;
    z->left = p;
    p->FB = 0;
    
    p = z;
    return p;
}


// double rotation to the right
Node* rotateDoubleRight(Node* p)
{
    Node* u = p->left;
    Node* v = u->right;

    u->right = v->left;
    v->left = u;
    p->left = v->right;
    v->right = p;

    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;

    p = v;
    return p;
}


// double rotation to the left
Node* rotateDoubleLeft(Node* p)
{
    Node* z = p->right;
    Node* y = z->left;

    z->left = y->right;
    y->right = z;
    p->right = y->left;
    y->left = p;

    if(y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    
    p = y;
    return p;
}


// insert Nodes in the AVL
// key: name of the games
Node* insertAVL(Node* a, char* name, float hours, int* ok)
{
    // insertion in leaf node
    if (a == NULL)
    {
        a = (Node*)malloc(sizeof(Node));
        a->key = strdup(name);
        a->time = hours;
        a->right = NULL;
        a->left = NULL;
        a->FB = 0;
        *ok = 1;
    }

    // if insert on the left
    else if (strcasecmp(name, a->key) < 0)
    {
        a->left = insertAVL(a->left, name, hours, ok);
        // update balance of father node
        if (*ok)
        {
            // if inconsistent balance, rotate
            switch(a->FB)
            {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = 1;
                    break;
                case 1:
                    a = case1(a, ok);
                    break;
            }
        }
    }

    // if insert on the right
    else
    {
        a->right = insertAVL(a->right, name, hours, ok);
        // update balance of father node
        if (*ok)
        {
            // if inconsistent balance, rotate
            switch(a->FB)
            {
                case 1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = -1;
                    break;
                case -1:
                    a = case2(a, ok);
                    break;
            }
        }
    }

    return a;   
}


// ============ BST ============


// insert Nodes in binary search tree
// key: name of the games
Node* insertBST(Node* a, char* name, float hours)
{
    if (a == NULL) {
        a = (Node*)malloc(sizeof(Node));
        a->key = strdup(name);
        a->time = hours;
        a->FB = 0;
        a->right = NULL;
        a->left = NULL;
    }

    else if (strcasecmp(name, a->key) < 0) {
        a->left = insertBST(a->left, name, hours);
    }

    else
        a->right = insertBST(a->right, name, hours);

    return a;
}


// =========== GENERAL ===========


// visualizes the tree
void preOrderTraversal(Node* a, int level)
{
    if (a != NULL) {
        for (int i = 0; i < level; i++)
            printf("=");
        printf("%s\n", a->key);
        preOrderTraversal(a->left, level + 1);
        preOrderTraversal(a->right, level + 1);
    }    
    return;
}

// searches for a game in a tree
Node* consult(Node* a, char* name)
{
    while (a != NULL)
    {
        comparisons++;
        if (strcasecmp(a->key, name) == 0)
            return a;
        else if (strcasecmp(a->key, name) > 0)
            a = a->left;
        else
            a = a->right;
    }
    return NULL;
}


// calculates the height of a tree
int countHeight (Node *a)
{
    int Height_left, Height_right;

    if (a == NULL)
        return 0;

    Height_left = countHeight(a->left);
    Height_right = countHeight(a->right);

    if (Height_left > Height_right)
        return (1 + Height_left);
    else
        return (1 + Height_right);
}


// return the number of Nodes in a tree
int countNodes(Node* a)
{
    if (a != NULL) {
        return 1 + countNodes(a->left) + countNodes(a->right);
    }
    else
        return 0;
}


// ============ MAIN ============


int main(int argc, char *argv[])
{
    clock_t start, end;

    if (argc != 4)
    {
        printf("Incorrect number of arguments. To execute the program, type: datastructures-project <inputCSV> <inputTXT> <exitTXT>\n");
        return 1;
    }

    // open .csv and .txt files
    FILE* inputCSV = fopen(argv[1], "r");
    if (inputCSV == NULL)
    {
        printf("Cannot open file %s", argv[1]);
        return 1;
    }

    FILE* inputTXT = fopen(argv[2], "r");
    if (inputTXT == NULL)
    {
        printf("Cannot open file %s", argv[2]);
        return 1;
    }

    FILE* exitTXT = fopen(argv[3], "w");
    if (exitTXT == NULL)
    {
        printf("Cannot open file %s", argv[3]);
        return 1;
    }


    // inicialize pointers to trees and variables
    Node* BSTTree = NULL;
    Node* AVLTree = NULL;
    int ok = 0;
    float totalhours = 0.0;

    start = clock();

    // read each line of the .csv file and create the BST and AVL Tree
    char line[256];
    while(fgets(line, sizeof(line), inputCSV) != NULL)
    {
        char* name = strtok(line, ",");
        char* hoursStr = strtok(NULL, ",");
        // converts string to float
        float hours = strtof(hoursStr, NULL);
        BSTTree = insertBST(BSTTree, name, hours);
        AVLTree = insertAVL(AVLTree, name, hours, &ok);
    }

    // read inputTXT and calculate total estimated game hours with BST
    Node* game;
    while(fgets(line, sizeof(line), inputTXT) != NULL)
    {
        // remove "\n" at the end of the line for correct comparison
        line[strcspn(line, "\n")] = 0;
        // find the game in the tree
        game = consult(BSTTree, line);
        if (game != NULL)
            totalhours += (game->time);
    }
    
    // preOrderTraversal(BSTTree, 1);

    fprintf(exitTXT, "Total estimated time: %.2f\n", totalhours);
    
    fprintf(exitTXT, "\n========== STATISTICS BST ==========\n");
    fprintf(exitTXT, "Number of Nodes in the tree: %d\n", countNodes(BSTTree));
    fprintf(exitTXT, "Height: %d\n", countHeight(BSTTree));
    fprintf(exitTXT, "Rotations: 0\n");
    fprintf(exitTXT, "Comparisons: %d\n", comparisons);

    // reset variables and .txt file
    comparisons = 0;
    totalhours = 0;
    rewind(inputTXT);

    // read inputTXT and calculate total estimated game hours with AVL
    while(fgets(line, sizeof(line), inputTXT) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        game = consult(AVLTree, line);
    }

    fprintf(exitTXT, "\n========== STATISTICS AVL ==========\n");
    fprintf(exitTXT, "Number of Nodes in the tree: %d\n", countNodes(AVLTree));
    fprintf(exitTXT, "Height: %d\n", countHeight(AVLTree));
    fprintf(exitTXT, "Rotations: %d\n", rotations);
    fprintf(exitTXT, "Comparisons: %d\n", comparisons);

    end = clock();
    float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000;

    fprintf(exitTXT, "\nTotal time of execution: %.2f ms\n", miliseconds);
    
    printf("exitTXT file sucessfuly created!\n");
    
    fclose(inputCSV);
    fclose(inputTXT);
    fclose(exitTXT);
}