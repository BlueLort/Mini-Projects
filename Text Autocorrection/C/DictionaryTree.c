#include "DictionaryTree.h"
   int FREE_TYPING=0;
struct BinaryTree* newBinaryTree()
{

    struct BinaryTree* b = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    b->root=NULL;
    return b;
}
struct node* newNode(const char* data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->data,data);
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void insertString(node** n,const char* data)
{

    if(*n==NULL)
    {
        *n=newNode(data);
    }
    else
    {
        if(strcmp(data,(*n)->data)>0)
        {
            insertString(&(*n)->right,data);
        }
        else if(strcmp(data,(*n)->data)<0)
        {
            insertString(&(*n)->left,data);
        }else{
            return; //if it's inside the tree don't do anything
        }
    }
}
void searchString(BinaryTree* b,const char* input)
{
 ///WE IGNORE CAPITAL AND SMALL CASE BECAUSE IT'S A DICTIONARY AND YET THE PDF DIDN'T SEPCIFY WHAT TO DO
   ///WITH SMALL OR CAPITAL LETTERS
    char BUFF[64];
    strcpy(BUFF,input);
    int i;
    for(i=0;i<64;i++){
        BUFF[i]=tolower(BUFF[i]);//all lower case to match up with read words
    }

    // Base case
    if (b->root == NULL)  return ;
    node* ite=b->root;
    node* parent=ite;
     while(ite)
        {
           parent=ite;
            if(!strcmp(BUFF,ite->data)){
                break;
            }
            else if(strcmp(BUFF,ite->data)>0)
            {
                ite=ite->right;
            }
            else
            {
                ite=ite->left;
            }
    }
    if(ite!=NULL){
        if(FREE_TYPING)    gotoxy(0,7);
            ///ALOT OF SPACES TO ERASE SUGGESTIONS
        printf("%s is a Correct Word!!                                 \n",ite->data);
    }else{
        node* suc=NULL;
        node* pre=NULL;
           if(FREE_TYPING) gotoxy(0,7);
        printf("Suggestion:%s     ",parent->data);
        getPreSuc(b->root,  pre,  suc,  parent->data);


    }

}
void getPreSuc(node* root, node* pre, node* suc, const char* input){
       if (root == NULL)  return ;
    //Found Key
    if (!strcmp(input,root->data))
    {
          // the minimum value in right branch is successor
        if (root->right != NULL)
        {
            node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        // the maximum value in left branch is predecessor
        if (root->left != NULL)
        {
            node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
        if(suc)printf("%s     ",suc->data);
       if(pre)printf("%s",pre->data);
       ///spaces to erase last written words
       printf("                                                      \n");
        return ;
    }

    // If input  is bigger than root's data, go to right branch
    if (strcmp(input,root->data) > 0)
    {
        pre = root ;
        getPreSuc(root->right, pre, suc, input) ;
    }
    // go to left branch
    else if(strcmp(input,root->data) < 0)
    {
        suc = root ;
        getPreSuc(root->left, pre, suc, input) ;
    }


}
