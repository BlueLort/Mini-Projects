#include "member.h"

///                             SAVE to FILE
void saveMembers()
{
    FILE *f=NULL;
    f=fopen("members.txt","w");
    if(f==NULL)
    {
        //Do Something
        printf("Couldnt open file For Writing\n");
        return;
    }
    for(i=0; i<nMembersTmp; i++)
    {

        fprintf(f,"%u,%s,%s,%s,%s,%s,%s,%s,%u,%u\n",members[i].ID,members[i].email
                ,members[i].fname,members[i].lname
                ,members[i].address.street,members[i].address.zone,members[i].address.city
                ,members[i].phoneNumber,members[i].age,members[i].booksBorrowed);
    }
    fclose(f);
}

///                     LOADING from FILE

void loadMembers()
{

    FILE *f=NULL;
    char B[400];
    f=fopen("members.txt","r");
    if(f==NULL)
    {
        printf("Couldnt open \"members\" for Reading(Created File \"members\"");
        fopen("members.txt","w");
        return;
    }
    nMembersTmp=0;//make sure it loads to just nMembers
    while(!feof(f))
    {
        fgets(B,400,f);
        sscanf(B,"%u,%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%u,%u\n",&members[nMembersTmp].ID,&members[nMembersTmp].email
               ,&members[nMembersTmp].fname,&members[nMembersTmp].lname
               ,&members[nMembersTmp].address.street,&members[nMembersTmp].address.zone,&members[nMembersTmp].address.city
               ,&members[nMembersTmp].phoneNumber,&members[nMembersTmp].age,&members[nMembersTmp].booksBorrowed);
        nMembersTmp++;

    }
    --nMembersTmp;//there are a new line due to the last feof
    fclose(f);
}

///                         SHOWING DETAILS
void show_members()
{
    int l;
    system("cls");
    gotoxy(0,0);
    setColor(12);
    printf("Enter to View Member Details-F to Find a Member-R to Register-D to Remove");
    gotoxy(0,2);
    for(l=0; l<nMembersTmp; l++)
    {
        if(CHOOSEN==l)setColor(15);
        else setColor(8);
        printf("%s %s\n",members[l].fname,members[l].lname);
    }

}

void view_member(Member* MEMBER)
{
    int tmp=CHOOSEN;///to DELETE WITH IT if needed
    CHOOSEN=0;
SWITCH2://TO PREVENT USER FROM BREAKING OUT OF THIS FUNCTION OR FLICKER THE SCREEN
    system("cls");
    setColor(12);
    printf("Click Esc. To Return to Member Management\n");
    i=0;
    checkColor();
    printf("Last Name: %s\n",MEMBER->lname);
    i++;
    checkColor();
    printf("First Name: %s\n",MEMBER->fname);
    i++;
    checkColor();
    printf("Age: %u\n",MEMBER->age);
    i++;
    checkColor();
    printf("Phone Number: %s\n",MEMBER->phoneNumber);
    i++;
    checkColor();
    printf("ID: %u\n",MEMBER->ID);
    i++;
    checkColor();
    printf("Email: %s\n",MEMBER->email);
    i++;
    checkColor();
    printf("Books Borrowed: %u\n",MEMBER->booksBorrowed);
    i++;
    checkColor();
    printf("Address: %s-%s-%s \n",MEMBER->address.street,MEMBER->address.zone,MEMBER->address.city);
    setColor(10);
    printf("Borrowed Books:\n");
    setColor(14);
    for(i=0; i<nBorrowed; i++)
    {
        if(borrowed[i].memberID==MEMBER->ID)
        {
            putBorrowed(borrowed[i].bookISBN);
        }
    }
    switch(buffer=_getch()) /// VEIW Members LOGIC
    {
    case 'D':
    case 'd':
        if(SEARCHING)delete_book(searched_books[tmp]);
        else delete_book(tmp);
    case (char)27:
        system("cls");
        SYSTEM=MEMBERS;
        break;
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
            if (CHOOSEN < 8-1)CHOOSEN++;
        }
        goto SWITCH2;
        break;
    case (char)13:

        edit_member(MEMBER);
        break;
    default:
        goto SWITCH2;
        break;

    }

}

void putBorrowed(const char* str)
{
    int l=0;

    for(l=0; l<nTmp; l++)
    {
        /// WE ARE COMPARING STR WHICH IS ISBN WITH BOOKS ISBN(cause its unique)
        if(!strcmp(books[l].ISBN,str))
        {
            puts(books[l].title);
            return;
        }
    }
    printf("**Book Name Wasn't Found**\n");///IF BOOK SOMETHING HAPPENED TO THE BOOK I WANT TO MAKE SURE IT PRINTS NEW LINE

}
///                     SOME LOGIC FUNCTIONS REGISTER REMOVING
void registerMember()
{
    system("cls");
    char B[100];
    int flag;
    fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
    i=0;
    Member tmp;
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    flag=VALIDATIONS_LOOP("Last Name:",B);
    if(!flag)return;
    strcpy(tmp.lname,B);
    flag=VALIDATIONS_LOOP("First Name:",B);
    if(!flag)return;
    strcpy(tmp.fname,B);
    setColor(10);
    printf("Address\n");
    flag=VALIDATIONS_LOOP_NOTSYMBOLS("Street:",B);
    if(!flag)return;
    strcpy(tmp.address.street,B);
    flag=VALIDATIONS_LOOP("Zone:",B);
    if(!flag)return;
    strcpy(tmp.address.zone,B);
    flag=VALIDATIONS_LOOP("City:",B);
    if(!flag)return;
    strcpy(tmp.address.city,B);
    do
    {
        fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
        setColor(12);
        printf("Phone Number:");
        setColor(15);
        fgets(B,100,stdin);
        B[strlen(B)-1]='\0';
        flag=ValidatePhoneNumber(B);
    }
    while(flag<0);
    if(!flag)return;
    strcpy(tmp.phoneNumber,B);
    do
    {
        flag=VALIDATIONS_LOOP_NUMBERS("Your Age Can't Excess 110 or be less than 7\nAge:",B);
        if(!flag)return;
        if(flag==-100)flag=0;
    }
    while(!ValidateAge(flag));
    tmp.age=flag;
    fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER by mistake
    setColor(12);
    printf("Email:");
    setColor(15);
    fgets(B,40,stdin);
    B[strlen(B)-1]='\0';
    strcpy(tmp.email,B);
    flag=verifyEmail(tmp.email);
    while(flag<0)
    {
        setColor(14);
        printf("Invalid Email Address(unavailable or invalid domain)\nNote That We accept gmail,yahoo and hotmail only");
        setColor(12);
        printf("Email:");
        setColor(15);
        fgets(B,40,stdin);
        B[strlen(B)-1]='\0';
        strcpy(tmp.email,B);
        flag=verifyEmail(tmp.email);
        if(!flag)return;
    }
    tmp.ID=generateID();
    tmp.booksBorrowed=0;
    members[nMembersTmp++]=tmp;
}

void edit_member(Member* member)
{
///THERE ARE 8-1 things to edit so 8 cases for 0 to 7
    char B[100];
    int l;
    int flag;
    fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
    system("cls");
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    switch(CHOOSEN)
    {
    case 0:

        flag=VALIDATIONS_LOOP("Last Name:",B);
        if(!flag)return;
        strcpy(member->lname,B);
        break;
    case 1:
        flag=VALIDATIONS_LOOP("First Name:",B);
        if(!flag)return;
        strcpy(member->fname,B);
        break;
    case 2:
        do
        {
            flag=VALIDATIONS_LOOP_NUMBERS("Your Age Can't Excess 110 or be less than 7\nAge:",B);
            if(!flag)return;
            if(flag==-100)flag=0;
        }
        while(!ValidateAge(flag));
        member->age=flag;
        break;
    case 3:
        do
        {
            fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER HOTKEYS
            setColor(12);
            printf("Phone Number:");
            setColor(15);
            fgets(B,100,stdin);
            B[strlen(B)-1]='\0';
            flag=ValidatePhoneNumber(B);
        }
        while(flag<0);
        if(!flag)return;
        strcpy(member->phoneNumber,B);
        break;
    case 4:
        setColor(14);
        printf("You Can't Modify Your ID...");
        Sleep(2000);
        break;
    case 5:
        setColor(12);
        fflush(stdin);//TO MAKE SURE NOT TAKING ANY INPUT FROM USER by mistake
        printf("Email:");
        setColor(15);
        fgets(B,40,stdin);
        B[strlen(B)-1]='\0';
        flag=verifyEmail(B);
        if(!flag)return;
        while(flag<0)
        {
            setColor(14);
            printf("Invalid Email Address(unavailable or invalid domain)\nNote That We accept gmail,yahoo and hotmail only\n");
            setColor(12);
            printf("Email:");
            setColor(15);
            fgets(B,40,stdin);
            B[strlen(B)-1]='\0';
            flag=verifyEmail(B);
            if(!flag)return;
        }
        strcpy(member->email,B);

        while(!verifyEmail(member->email))
        {
            setColor(14);
            printf("\nInvalid Email Address(unavailable or invalid domain)\nNote That We accept gmail,yahoo and hotmail only\n");
            gotoxy(0,i++);
            setColor(12);
            printf("Email:");
            setColor(15);
            fgets(B,40,stdin);
            B[strlen(B)-1]='\0';
            strcpy(member->email,B);
        }
        break;
    case 6:
        setColor(14);
        printf("You Can't Modify That...");
        Sleep(2000);
        break;
    case 7:
        flag=VALIDATIONS_LOOP_NOTSYMBOLS("Street:",B);
        if(!flag)return;
        strcpy(member->address.street,B);
        flag=VALIDATIONS_LOOP("Zone:",B);
        if(!flag)return;
        strcpy(member->address.zone,B);
        flag=VALIDATIONS_LOOP("City:",B);
        if(!flag)return;
        strcpy(member->address.city,B);
        break;
    }
    view_member(member);

}

void remove_member(int k)
{

    if(members[k].booksBorrowed!=0)
    {
        setColor(10);
        printf("This Member has Borrowed Some Books From The Library So Member Can't Be Deleted\n");
        system("pause");
        return;
    }


    Member tmp;
    for(i=k; i<nMembersTmp-1; i++)
    {
        tmp=members[i];
        members[i] =members[i+1];
        members[i+1]=tmp;
    }
    if(CHOOSEN>0)CHOOSEN--;
    else CHOOSEN++;
    show_members();
    nMembersTmp--;
}

uint generateID()
{

    char B[400];
    uint r;
    int l;
REGEN://goto label
    r=rand()%10000;
    r+=90000;

    for(l=0; l<nMembersTmp; l++)
    {
        if(r==members[l].ID)
        {
            goto REGEN;
        }
        return r;
    }
}

///                                     SEARCHING FUNCTIONS
void find_member()
{
    system("cls");
    char search_key[40]= {0};
    CHOOSEN=0;
    char tmp;
    int tmpo=0;//tmp for search results
    SEARCHING=1;
    int k=0;

    while(1)
    {
        tmpo=search_member(search_key);
        setColor(14);
        gotoxy(0,1);
        for(i=0; i<k; i++)printf("%c",search_key[i]);
//TO ERASE PREVIOUS CHARS if BackSpace Was Clicked
        printf(" ");
        setColor(12);
        gotoxy(0,0);
        printf("Click Esc to Cancel");

        tmp=_getch();
        if(tmp==(char)27)
        {
            SEARCHING=0;
            break;
        }
        else if(tmp==(char)8)
        {
            if(k>0)
            {
                search_key[--k]='\0';
            }
        }
        else if(tmp==(char)224)
        {
            tmp=_getch();
            if(tmp==(char)72)
            {
                if(CHOOSEN>0)CHOOSEN--;
            }
            else if(tmp==(char)80)
            {
                if(CHOOSEN<tmpo-1)CHOOSEN++;//lets make it like that for now
            }
        }
        else if(tmp==(char)13)
        {
            int l;
            for(l=0; l<tmpo; l++)
            {
                if(l==CHOOSEN)
                {
                    view_member(&members[searched_members[CHOOSEN]]);
                }
            }


        }
        else
        {
            if(k<40&&(tmp>33&&tmp<126))
            {
                search_key[k++]=tmp;
            }
        }
    }
}

int search_member(const char* str)
{
    int k=0;
    int notFound=1;
    int results=0;
    char name[80];///to concatenate the name of the member to search
    setColor(12);
    Erase(k+2);//to clear previous search table
    int Counter;
    for(Counter=0; Counter<nMembersTmp; Counter++)
    {
        if(k==CHOOSEN) setColor(15);
        else setColor(8);
        if(smart_search(strcat(strcat(strcat(name,members[Counter].fname)," "),members[Counter].lname),str))
        {
            notFound=0;
            gotoxy(0,k+2);
            k++;
            printf("%s %s\n",members[Counter].fname,members[Counter].lname);
            searched_members[results]=Counter;
            results++;
        }
    }
    if(notFound)
    {
        setColor(12);
        printf("Sorry,but your search did not match any documents.!!\n");
    }
    return results;
}

///                         VALIDATION STUFF

int verifyUserID(uint ID)
{
    int l;
    for(l=0; l<nMembersTmp; l++)
    {
        if(members[l].ID==ID)
        {
            if(members[l].booksBorrowed<3)
            {
                members[l].booksBorrowed++;
                return 1;//Indicates true
            }
            else
            {
                return -1;//indicates user has max books limit
            }
        }

    }
    return 0;//indicates false
}

int verifyUserBorrowedID(uint ID,const char* str)
{
    int l;
    /// str represents book isbn
    for(l=0; l<nBorrowed; l++)
    {
        if(borrowed[l].memberID==ID&&!strcmp(borrowed[l].bookISBN,str))
            return l;//Indicates true and index for that thing to return

    }
    return -1;//indicates false
}

int verifyEmail(const char* str)
{
    int str_length=strlen(str);
    int l;
    for(l=0; l<str_length; l++)
    {
        if(str[l]==' ')return -1;///email cant be spaces
    }
    char tmpEmailDomain[40];
    if(!strcmp(str,"cancel"))return 0;///OPERATION CANCELLED
    sscanf(str,"%[^@]%s",&tmpEmailDomain,&tmpEmailDomain);
    if(!strcmp(tmpEmailDomain,"@gmail.com")||!strcmp(tmpEmailDomain,"@hotmail.com")||!strcmp(tmpEmailDomain,"@yahoo.com"))
    {
        for(l=0; l<nMembersTmp; l++)
        {
            if(!strcmp(members[l].email,str))
            {
                return 0;// EMAIL IS UNAVAILABLE
            }
        }
        return 1;//EMAIL IS OKAY
    }
    else
    {
        return -1;//INVALID DOMAIN NAME
    }
}



