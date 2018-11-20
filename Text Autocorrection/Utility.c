#include "Utility.h"
#include <math.h>

int readData(const char* filePath,BinaryTree* b)
{
    int lines=countLines(filePath);
    FILE* fp=NULL;
    fp=fopen(filePath,"r");
    char NODES[lines][64];//READ & STORE ALL THE ELEMENTS(3000NODE in order)
    if(fp==NULL)return 0;
    char Buffer[64];
    int i,k=0;
    while(!feof(fp))
    {
        fscanf(fp,"%s",Buffer);
        ///ENSURE ALL LOWER CASE
        for(i=0;i<64;i++){
            Buffer[i]=tolower(Buffer[i]);
        }
        strcpy(NODES[k++],Buffer);
    }


    insertElements(b,NODES,0,lines-1);


    fclose(fp);
    return 1;

}
    ///BALANCE THE TREE BY TAKING THE middle element as root
    ///and start going right and left (BALANCING TREE)
void insertElements(BinaryTree* b,char data[][64],int l,int r){

    if(r>=l){
    int mid=(l+r)/2;
    insertString(&b->root,data[mid]);
    insertElements(b,data,l,mid-1);
    insertElements(b,data,mid+1,r);
    }
}
int countLines(const char* filePath){
    FILE* fp=NULL;
    fp=fopen(filePath,"r");
    if(fp==NULL)return 0;
    char Buffer[64];
    int num=0;
    while(!feof(fp))
    {
        fscanf(fp,"%s",Buffer);//GET LINE TO MOVE THE READ POINTER PLACE
        num++;
    }
    fclose(fp);
    return num;
}
int lengthNode(node* n)
{
    if(n==NULL)
    {
        return -1;
    }
    else
    {
        int l1=lengthNode(n->left);
        int l2=lengthNode(n->right);
        return 1+(l1>=l2?l1:l2);
    }

}
int height(BinaryTree* b)
{
    return lengthNode(b->root);
}
void smartSuggestion(BinaryTree* b){
     ShowConsoleCursor(0);//HIDE THE CONSOLE CURSOR
     FREE_TYPING=1;
    char search_key[1024][64]= {0};//1024 word in a sentence *64 letters in a word
    char tmp;
    int k=0;
    int ite=0;
    while(1){
            gotoxy(0,6);
            ///SPACES TO ERASE LAST WRITTEN WORD
            int i;
            for(i=0;i<=ite;i++){
        printf("%s ",search_key[i]);
            }
    printf("                                               ");///ERASE
        tmp=_getch();
        ///ESC
        if(tmp==(char)27)
        {
            gotoxy(0,8);//proper return process shape
            exit(0);//CLOSE ON ESC
        }
        ///ARROWS VIRTUAL CALL
         else if(tmp==(char)224)
        {
            tmp=_getch();//IGNORE THE ARROW GARBAGE input KEYS
        }///ENTER
         else if(tmp==(char)13)
        {


        }
        else if(tmp==(char)8)
        {
            if(k>0)
            {
                search_key[ite][--k]='\0';
            }else{
                if(ite>0)ite--;
                k=strlen(search_key[ite]);
            }
        }else if(tmp==' '){
            ite++;
            k=0;
            printf(" ");
        }

        else
        {
            ///ALL POSSIBLE LETTERS
            if(k<40&&(tmp>=32&&tmp<=126))
            {
                search_key[ite][k++]=tmp;
            }
        }

         searchString(b,search_key[ite]);//SEARCH FOR ELEMENT   -> DictionaryTree.c
           if(k==0){
            gotoxy(0,7);
            ///ERASE THE LINE
            printf("                                                                          ");
        }
    }
}
void searchWords(BinaryTree* b,char* buffer){
    char* word=strtok(buffer," ");
    while(word!=NULL){
        searchString(b,word);
        word=strtok(NULL," ");
    }

}
