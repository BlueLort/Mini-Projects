#include <stdio.h>
#include <stdlib.h>
#include "Utility.h"

///THESE ARE FUNCTIONS USED TO MAKE THE APPLICATION MORE FRIENDLY
///setColor(int) -> function to change cmd color depends of 8bit color values known in the cmd(windows.h library)
///gotoxy(int x,int y) ->function used to go to certain location in the cmd (windows.h library)
///showConsoleCursor(bool) ->disable or enable showing console cursor
int main()
{

    ///INITIALIZING THE TREE
    BinaryTree* x=newBinaryTree();//DictionaryTree.h
    setColor(12);
    printf("There Are Free Typing Technique After Testing your Test Case give it a try\n");
    setColor(14);
    printf("(Suggestions : Parent Successor Predecessor)\n");
    setColor(7);
    if(readData("English Dictionary.txt",x))//Utility.c
    {
        printf("INSERTED SUCCESSFULLY\n");
    }
    printf("Height:%d\n", height(x));// DictionaryTree.c
    char Buffer[1024];
    printf("Sentence:");
    fgets(Buffer,1024,stdin);
    Buffer[strlen(Buffer)-1]='\0';//ELIMINATE NEW LINE FROM FGETS
    //Search for each word in the sentence
    searchWords(x,Buffer);
    ///BONUS FEATURE !!
    setColor(15);
    printf("Now you Can Try The Free Typing Feature \n");
    setColor(7);
    system("pause");
    system("cls");
    setColor(12);
    printf("Start Typing to Test the Free Typing Method\n");
    setColor(10);
    printf( "**Note That you can continue typing and new suggestions will appear**\n");
    setColor(14);
    printf("Press ESC to End(Suggestions : Parent Successor Predecessor)\n");
    setColor(7);
    ///FUNCTION THAT WORK ON THAT FREE TYPING
    smartSuggestion(x);


    return 0;
}
