#include "menuEventHandler.h"

///                            SYSTEM INIT FUNCTIONS
void progStart()
{
    srand(time(NULL));//SEED RANDOM WITH CURRENT TIME(GOOD METHOD CAUSE TIME IS ALWAYS CHANGING)
    system("title Library System");
    SYSTEM = MENU;
    FLAG=TITLE;
    ShowConsoleCursor(0);//to shut of the visibility of the cursor
    esc=0;// flag to check whether i'm still in the menu or i entered another one
    RUNNING=1;
    CHOOSEN = 1;//to scroll through main menu
    ///init lengths as 0
    nMembersTmp=0;
    SEARCHING=0;
    nTmp=0;
    nBorrowed=0;
    ///LOAD BOOKS MEMBERS BORROWED
    load_books();
    loadMembers();
    load_borrowed();
}

///                         SYSYTEM DESIGN RELATED STUFF

void Erase(int startR)
{
    int l;
    gotoxy(0,startR);
    setColor(8);
    for(l=0; l<80; l++) ///JUST MAKING SURE EVERYTHING IS ERASED WELL
    {

        printf("                                                                                                    \n");//100cols
    }
    gotoxy(0,startR);
}

///                         MENU STUFF AND LOGIC

void menuHandler()
{
    switch (SYSTEM)
    {
    case MENU:
        ShowConsoleCursor(0);///TO REHIDE IT IF USER RESIZED THE WINDOW
        CHOOSEN=1;
        esc=0;
        system("mode 80,25");
        system("cls");
        while (!esc)
        {
            int month,day,year;
            get_date(&month,&day,&year);
            setColor(14);
            gotoxy(1, 0);
            printf("Developed by Omar Nasr(Lort)");
            setColor(12);
            gotoxy(1, 1);
            printf("**Up/Down -Enter To choose**");
            setColor(11);
            printf("\t\tCurrent Date:%d/%d/%d",day,month,year);///I THOUGHT IT WAS COOL

            for ( i = 1; i < 7; i++)
            {
                if (i == CHOOSEN) setColor(15);
                else setColor(8);
                switch (i)
                {
                case 1:
                    gotoxy(1, i+1);
                    printf("Book Management");
                    break;
                case 2:
                    gotoxy(1, i+1);
                    printf("Member Management");
                    break;
                case 3:
                    gotoxy(1, i+1);
                    printf("Borrow Management");
                    break;
                case 4:
                    gotoxy(1, i+1);
                    printf("Administrative actions");
                    break;
                case 5:
                    gotoxy(1, i+1);
                    printf("Save Changes");
                    break;
                case 6:
                    gotoxy(1, i+1);
                    printf("Exit");
                    break;
                }
            }

            buffer = _getch();
            if (buffer == (char)13)
            {
                switch (CHOOSEN)
                {
                case 1:
                    SYSTEM = BOOKS;
                    esc =1;
                    break;
                case 2:
                    SYSTEM = MEMBERS;
                    esc = 1;
                    break;
                case 3:
                    SYSTEM = BORROW;
                    esc = 1;
                    break;
                case 4:
                    SYSTEM = ADMIN;
                    esc = 1;
                    break;
                case 5:
                    SYSTEM= SAVE;
                    esc=1;
                    break;

                case 6:
                    SYSTEM = EXIT;
                    esc = 1;
                    break;

                }
            }
            menuLogic();

        }
        break;

    case BOOKS:
        CHOOSEN = 0;
        system("CLS");
        setColor(7);
        esc = 0;
        while(!esc)
        {

            bubbleSortBOOK(books,nTmp,'a');
            show_books();
            books_logic(CHOOSEN);
        }


        break;

    case MEMBERS:
        CHOOSEN = 0;
        system("cls");
        setColor(7);
        esc = 0;
        while(!esc)
        {
            bubbleSortMEMBER(members,nMembersTmp);
            show_members();
            members_logic(CHOOSEN);
        }

        break;
    case BORROW:
        CHOOSEN = 0;
        system("cls");
        setColor(7);
        esc = 0;
        while(!esc)
        {
            show_borrowed();
            borrow_logic(CHOOSEN);
        }
        break;
    case ADMIN:
        esc=0;
        CHOOSEN=0;
        system("cls");


        while(!esc)
        {
            gotoxy(0,0);
            setColor(12);
            printf(" Press Enter To Choose-Esc. to Back");
            switch(CHOOSEN)
            {
            case 0:
                setColor(15);
                gotoxy(0,1);
                printf(" OverDue");
                setColor(8);
                gotoxy(0,2);
                printf(" Popular");
                break;
            case 1:
                setColor(8);
                gotoxy(0,1);
                printf(" OverDue");
                setColor(15);
                gotoxy(0,2);
                printf(" Popular");
                break;
            }
            admin_logic(CHOOSEN);
        }


        break;

    case SAVE:
        esc=0;
        save_books();
        saveMembers();
        save_borrowed();
        for(i=0; i<80; i++)
        {
            gotoxy(i,24);
            setColor(255);
            Sleep(10);
            printf(" ");
        }
        setColor(0);
        SYSTEM=MENU;


        break;
    case EXIT:
        RUNNING=0;
        gotoxy(0,8);
        setColor(10);
        printf(" Do You Want To Save The Changes ?(click y if yes)\n");
        buffer=_getch();
        if(buffer=='y'||buffer=='Y')
        {
            save_books();
            saveMembers();
            save_borrowed();
        }
        esc=1;
        setColor(8);

        break;
    }
}

void menuLogic()
{

    switch (buffer)
    {
    case (char)224:
        buffer=_getch();
        if(buffer==(char)72)
        {
            if (CHOOSEN > 1)CHOOSEN--;///CAUSE we USE INFO ON 0
        }
        else if(buffer==(char)80)
        {
            if (CHOOSEN < 6)CHOOSEN++;
        }
        break;
    case (char)27:
        SYSTEM = EXIT;
        esc = 1;
        break;
    }
}

void books_logic(int k)
{
    switch (buffer=_getch())
    {
    case (char)224:
        buffer=_getch();
        ///UP
        if(buffer==(char)72)
        {
            if (CHOOSEN > 0)CHOOSEN--;
            ///DOWN
        }
        else if(buffer==(char)80)
        {
            if (CHOOSEN < nTmp-1)CHOOSEN++;
        }
        break;
    case 'i':
    case 'I':
        add_new_book();
        esc=1;//to break out of the loop and reenter BOOKS
        break;
    case 'd':
    case 'D':

        if(nTmp>0)delete_book(k);
        break;
    case 'f':
    case 'F':
        if(nTmp>0)
        {
            find_book();
            esc=1;
        }

        break;
    case (char)13:
        if(nTmp>0)
        {
            view_book(&books[k]);
            esc=1;//to break out of the loop and reenter BOOKS
        }
        break;
    case (char)27:
        SYSTEM = MENU;
        esc = 1;
        break;
    }
}

void members_logic(int k)
{
    switch (buffer=_getch())
    {
    case (char)224:
        buffer=_getch();
        ///UP
        if(buffer==(char)72)
        {
            if (CHOOSEN > 0)CHOOSEN--;
            ///DOWN
        }
        else if(buffer==(char)80)
        {
            if (CHOOSEN < nMembersTmp-1)CHOOSEN++;
        }
        break;
    case 'R':
    case 'r':
        registerMember();
        esc=1;//to break out of the loop and reenter BOOKS
        break;
    case 'd':
    case 'D':

        if(nMembersTmp>0)remove_member(k);
        break;
    case 'f':
    case 'F':
        if(nMembersTmp>0)
        {
            find_member();
            esc=1;
        }

        break;
    case (char)13:
        if(nMembersTmp>0)
        {
            view_member(&members[k]);
            esc=1;//to break out of the loop and reenter BOOKS
        }
        break;
    case (char)27:
        SYSTEM = MENU;
        esc = 1;
        break;
    }
}

void borrow_logic(int k)
{
    switch (buffer=_getch())
    {
    case (char)224:
        buffer=_getch();
        ///UP
        if(buffer==(char)72)
        {
            if (CHOOSEN > 0)CHOOSEN--;
            ///DOWN
        }
        else if(buffer==(char)80)
        {
            if (CHOOSEN < nBorrowed-1)CHOOSEN++;
        }
        break;

    case 'R':
    case 'r':
        if(nBorrowed>0)
        {
            return_book();
            esc=1;///to break out of the loop of Borrow and Reload it again
        }
        break;

    case (char)13:
        if(nBorrowed>0)
        {
            view_borrow(&borrowed[k]);
            esc=1;//to break out of the loop and reenter BOOKS
        }
        break;
    case (char)27:
        SYSTEM = MENU;
        esc = 1;
        break;
    }
}

void admin_logic(int k)
{
    switch (buffer=_getch())
    {
    case (char)224:
        buffer=_getch();
        ///UP
        if(buffer==(char)72)
        {
            if (CHOOSEN > 0)CHOOSEN--;
            ///DOWN
        }
        else if(buffer==(char)80)
        {
            if (CHOOSEN < 1)CHOOSEN++;
        }
        break;
    case (char)27:
        SYSTEM = MENU;
        esc = 1;
        break;
    case (char)13:
        if(CHOOSEN==0)
        {
            overDue();
        }
        else
        {
            popularBooks();
        }
        break;

    }
}

void overDue()
{
    esc=0;
    system("cls");
    while(!esc)
    {
        show_borrowed_overDue();
        switch(buffer=_getch())
        {
            {
            case (char)224:
                buffer=_getch();
                ///UP
                if(buffer==(char)72)
                {
                    if (CHOOSEN > 0)CHOOSEN--;
                    ///DOWN
                }
                else if(buffer==(char)80)
                {
                    if (CHOOSEN < overdueLength-1)CHOOSEN++;
                }
                break;
            case (char)13:

                if(overdueLength>0)
                {
                    view_borrow(&borrowed[overdue_books[CHOOSEN]]);
                    SYSTEM=ADMIN;///because view_borrow has SYSTEM=BORROW in it
                }
                break;
            case (char)27:
                esc=1;
                break;
            }
        }
    }
}

void popularBooks()
{
    bubbleSortBOOK(books,nTmp,'p');
    system("cls");
    setColor(12);
    printf(" Press Esc. To Back\n");

    ///REQUIRED ONLY FIRST 5
    for(i=0; i<(nTmp<5?nTmp:5); i++)
    {
        setColor(15);
        printf(" %s",books[i].title);
        setColor(10);
        printf("\tBorrowed: %u Times\n",books[i].nBorrowed);
    }
SWITCH4:
    switch(buffer=_getch())
    {
    case (char)27:
        system("cls");
        break;
    default:
        goto SWITCH4;
        break;
    }
}

void checkColor()
{
    if(i==CHOOSEN)setColor(15);
    else setColor(8);
}

///                             SORTING STUFF
// sorting for better view
void bubbleSortBOOK(struct Book *arr,size_t s,char flag)
{
    char tmpo[256];
    int i,j,pass,sorted=0;
    if(flag=='a')
    {
        for(pass=0; pass<s; pass++)
        {
            if(sorted)break;
            sorted=1;
            for(j=0; j<s-1; j++)
            {
                if(strcmp(arr[j].title,arr[j+1].title)>0)
                {

                    swapBOOK(&arr[j],&arr[j+1]);



                    sorted=0;
                }

            }
        }
    }
    else if(flag=='p')
    {
        for(pass=0; pass<s; pass++)
        {
            if(sorted)break;
            sorted=1;
            for(j=0; j<s-1; j++)
            {
                if(arr[j].nBorrowed<arr[j+1].nBorrowed)
                {

                    swapBOOK(&arr[j],&arr[j+1]);

                    sorted=0;
                }

            }
        }
    }
}

void bubbleSortMEMBER(struct Member *arr,size_t s)
{
    char tmpo[256];
    char strCAT1[120];///TO CONCATENATE LAST AND FIRST NAME TO SORT
    char strCAT2[120];///TO CONCATENATE LAST AND FIRST NAME TO SORT
///FOR arr of j and j+1
    int i,j,pass,sorted=0;
    for(pass=0; pass<s; pass++)
    {
        if(sorted)break;
        sorted=1;
        for(j=0; j<s-1; j++)
        {
            strcat(strcat(strcat(strCAT1,arr[j].fname)," "),arr[j].lname);
            strcat(strcat(strcat(strCAT2,arr[j+1].fname)," "),arr[j+1].lname);
            if(strcmp(strCAT1,strCAT2)>0)
            {
                swapMEMBER(&arr[j],&arr[j+1]);
                sorted=0;
            }

        }
    }

}

void swapBOOK(Book *pr1,Book *pr2)
{
    Book tmp;
    tmp=*pr2;
    *pr2=*pr1;
    *pr1=tmp;
}

void swapMEMBER(struct Member *pr1,struct Member* pr2)
{
    Member tmp;
    tmp=*pr2;
    *pr2=*pr1;
    *pr1=tmp;
}

///                         VALIDATION STUFF

/*  this was used alot in the program so instead its a function and special cases are kept*/
int VALIDATIONS_LOOP(const char* message,char *input)
{
    int flag;
    do
    {
        fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
        setColor(12);
        printf(message);
        setColor(15);
        fgets(input,100,stdin);
        input[strlen(input)-1]='\0';
        flag=ValidateString(input);
    }
    while(flag<0);
    if(!flag)return 0;
    return 1;
}

/*      this one like the above one but for numbers */
int VALIDATIONS_LOOP_NUMBERS(const char* message,char *input)
{
    int flag;
    do
    {
        fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
        setColor(12);
        printf(message);
        setColor(15);
        fgets(input,100,stdin);
        input[strlen(input)-1]='\0';
        flag=checkIfNumber(input);
    }
    while(flag<0);
    return flag;

}

int VALIDATIONS_LOOP_NOTSYMBOLS(const char* message,char *input)
{

    int flag;
    do
    {
        fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
        setColor(12);
        printf(message);
        setColor(15);
        fgets(input,100,stdin);
        input[strlen(input)-1]='\0';
        flag=ValidateString(input);
    }
    while(flag==-2);
    if(!flag)return 0;
    return 1;

}


int ValidateString(const char* str)
{
    char *forbiddenChars=",!@#$%^&*()=+\//";///i dont want those symbols in my string
    char *forbiddenNums="1234567890";///CHECKING IF STRING HAS NUMBERS
    int forbiddenString_length=strlen(forbiddenChars);
    int string_length=strlen(str);
    if(!strcmp(str,"cancel"))return 0;///OPERATION CANCELLED
    if(string_length<=1) return -2;
///check for forbidden chars like numbers commas
    int l,p,maxASCII=0;
    for(l=0; l<string_length; l++)
    {
        for(p=0; p<forbiddenString_length; p++)
        {
            if(str[l]==forbiddenChars[p])return -2;
            if(maxASCII<(int)str[l])maxASCII=(int)str[l];
        }
    }
    forbiddenString_length=strlen(forbiddenNums);
    for(l=0; l<string_length; l++)
    {
        for(p=0; p<forbiddenString_length; p++)
        {
            if(str[l]==forbiddenNums[p])return -1;
            if(maxASCII<(int)str[l])maxASCII=(int)str[l];
        }
    }
    if(maxASCII==13||maxASCII==32)return -2;///CANT BE JUST SPACES or Enter
//if(!strcmp(str,"cancel"))return 0;///OPERATION CANCELLED
    return 1;//indicates its okay
}

int ValidatePhoneNumber(const char* str)
{
///01123456789 so its 11 numbers including first 0 and 1
///CHECKING IF ITS ONLY NUMBERS
    int l;
    int string_length=strlen(str);
    if(!strcmp(str,"cancel"))return 0;///OPERATION CANCELLED
    if(string_length!=11) return -1;///NOT VALID NUMBER
    if(str[0]!='0'||str[1]!='1')return -1;
    for(l=2; l<string_length; l++) ///as 0,1 index are 01
    {
        if((int)str[l]>57||(int)str[l]<48)return -1;///DIDNT ENTER NUMBERS
    }
    return 1;//VALID PHONE NUMBER
}

int ValidateAge(const uint u)
{
    if(u>110||u<7)return 0;///REASONABLE AGE from 7 to 110
    return 1;//VALID AGE
}

int ValidateDate(const uint d,const uint m,const uint y)
{
///MONTH AND YEAR CHECKING
    if(m<1||m>12)return -1;// MONTH CHECKING
    if(y>2040)return -1;//SO FAR YEAR
///FEBRUARY CHECKING
    if(m==2&&(d>28||d<1))return -2;//FEB COMMON YEAR
    if(m==2&&y%4!=0&&d==29)return -2;//LAST DAY OF FEB LEAP YEAR
///DAYS CHECKING
    if(m<8&&m%2==1&&(d>31||d<1)) return -3;// WORNG DAY
    else if(m<8&&m%2==0&&(d>30||d<1))return -3;
    if(m>8&&m%2==0&&(d>31||d<1)) return -3;
    else if(m>8&&m%2==1&&(d>30||d<1))return -3;
    return 1;///ITS VALID DATE
}

uint checkIfNumber(const char* str)
{

    int string_length=strlen(str);
    int l;
    if(!strcmp(str,"cancel"))return 0;///OPERATION CANCELLED
    if(string_length==0)return -1;
    for(l=0; l<string_length; l++)
    {
        if((int)str[l]>57||(int)str[l]<48) return -1;//its not a number
    }

    if(atoi(str)==0)return -100;///AS FLAG I CAN HANDLE
// As 0 is used to flag cancel
    return atoi(str);///its a number so we have to return it

}
