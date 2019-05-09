#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include "DictionaryTree.h"
#include "cmdNavigation.h"
#include <math.h>
#include <conio.h>
/**
*reads dictionary from a file into binary tree
*@param filePath
*           file path of the required file
*@param b
*           the binary tree which the data will be stored in
*@return
*           returns 1 if success 0 if not
*/
int readData(const char* filePath,BinaryTree* b);
/**
* recursively inserting elements
*
*@param b
*           the container
*
*@param data
*           the string array data
*@param nItems
*           length of the array
*
*/
void insertElements(BinaryTree* b,char data[][64],int l,int r);
/**
*counts dictionary words from a file
*@param filePath
*           file path of the required file
*@return
*           the number of lines it could read
*/
int countLines(const char* filePath);
/**
*PUBLIC
*gets the length of binaryTree
*@param b
*           the container
*@return
*           length of the binary tree
*/
int height(BinaryTree* b);
/**
*PRIVATE
*gets the length of certain node
*@param n
*           the container
*@return
*           length of the node
*/
 int lengthNode(node* n);
/**
*makes the search more friendly for the user
*@param b
*           the container
*/
void smartSuggestion(BinaryTree* b);

/**
*search for words in the tree from certain buffer
*@param b
*           the container
*@param buffer
*           the buffer
*/
void searchWords(BinaryTree* b,char* buffer);
#endif // UTILITY_H_INCLUDED
