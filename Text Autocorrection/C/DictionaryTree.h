#ifndef DICTIONARYTREE_H_INCLUDED
#define DICTIONARYTREE_H_INCLUDED
#include <stdio.h>
#include <string.h>
/** TREE :)
      String
      /   \
    NULL  NULL
*/
extern int FREE_TYPING; //TO CHECK if i should use gotoxy or just print the result because i have 2 ways
// of getting input one required and one as a feature
typedef struct node
{
    char data[64];//64 char string
    struct node *left;
    struct node *right;
} node;
typedef struct BinaryTree
{
    node* root;
} BinaryTree;
///return empty binarytree to the user
struct BinaryTree* newBinaryTree();
///INIT THE NODE WITH DATA
struct node* newNode(const char* data);
/**
* inserts element into the BinaryTree
*
*@param b
*           the container
*
*@param data
*           the string data to be put
*/
void insertString(node** b,const char* data);

/**
* search for element into the BinaryTree
*
*@param b
*           the container
*
*@param data
*           the string input
*/
void searchString(BinaryTree* b,const char* input);
static void getPreSuc(node* root, node* pre, node* suc, const char* input);


#endif // DICTIONARYTREE_H_INCLUDED
