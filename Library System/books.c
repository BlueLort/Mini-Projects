#include "books.h"

///                              SAVE to FILE

void save_books()
{
    FILE *f=NULL;
    f=fopen("books.txt","w");
    if(f==NULL)
    {
        //Do Something
        printf("Couldnt open file For Writing\n");
        return;
    }

    for(i=0; i<nTmp; i++)
    {
        fprintf(f,"%s,%s,%s,%s,%s,%u,%u,%u,%u/%u/%u\n",books[i].title,books[i].author,
                books[i].publisher,books[i].ISBN,books[i].type,books[i].nCopies
                ,books[i].available,books[i].nBorrowed,books[i].publicationDate.day,books[i].publicationDate.month
                ,books[i].publicationDate.year);


    }
    fclose(f);
}

void save_borrowed()
{
    FILE *f=NULL;
    f=fopen("borrowed.txt","w");
    if(f==NULL)
    {
        //Do Something
        printf("Couldnt open file For Writing\n");
        return;
    }

    for(i=0; i<nBorrowed; i++)
    {
        fprintf(f,"%s,%u,%u/%u/%u,%u/%u/%u,%u/%u/%u\n",borrowed[i].bookISBN,borrowed[i].memberID
                ,borrowed[i].issued.day,borrowed[i].issued.month,borrowed[i].issued.year
                ,borrowed[i].dueToReturn.day,borrowed[i].dueToReturn.month,borrowed[i].dueToReturn.year
                ,borrowed[i].returned.day,borrowed[i].returned.month,borrowed[i].returned.year);


    }
    fclose(f);
}

///                                     LOADING from FILE


void load_books()
{
    FILE *f=NULL;
    char B[400];
    f=fopen("books.txt","r");
    if(f==NULL)
    {
        printf("Couldnt open \"books\" for Reading(Created File \"books\"");
        fopen("books.txt","w");
        return;
    }
    nTmp=0;//to make sure loads to n only
    while(!feof(f))
    {
        fgets(B,400,f);

        sscanf(B," %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c %u , %u , %u , %u/%u/%u",&books[nTmp].title,&books[nTmp].author,
               &books[nTmp].publisher,&books[nTmp].ISBN,&books[nTmp].type,&books[nTmp].nCopies
               ,&books[nTmp].available,&books[nTmp].nBorrowed,&books[nTmp].publicationDate.day,&books[nTmp].publicationDate.month
               ,&books[nTmp].publicationDate.year);
        nTmp++;
    }
    --nTmp;//there are a new line due to the last feof
    fclose(f);
}

void load_borrowed()
{
    FILE *f=NULL;
    char B[400];
    f=fopen("borrowed.txt","r");
    if(f==NULL)
    {
        printf("Couldnt open \"borrowed\" for Reading(Created File \"borrowed\"");
        fopen("borrowed.txt","w");
        return;
    }
    nBorrowed=0;//to make sure loads to nBorrowed only
    while(!feof(f))
    {
        fgets(B,400,f);

        sscanf(B," %[^,]%*c%u,%u/%u/%u,%u/%u/%u,%u/%u/%u",&borrowed[nBorrowed].bookISBN,&borrowed[nBorrowed].memberID
               ,&borrowed[nBorrowed].issued.day,&borrowed[nBorrowed].issued.month,&borrowed[nBorrowed].issued.year
               ,&borrowed[nBorrowed].dueToReturn.day,&borrowed[nBorrowed].dueToReturn.month,&borrowed[nBorrowed].dueToReturn.year
               ,&borrowed[nBorrowed].returned.day,&borrowed[nBorrowed].returned.month,&borrowed[nBorrowed].returned.year);
        nBorrowed++;
    }
    --nBorrowed;//there are a new line due to the last feof
    fclose(f);

}

///                                     SHOWING DETAILS

void show_books()
{
    int l;
    system("cls");
    gotoxy(0,0);
    setColor(12);
    printf("Enter to View Book Details-F to Find a book-I to insert a new Book-D to Remove");
    gotoxy(0,2);
    for(l=0; l<nTmp; l++)
    {
        if(CHOOSEN==l)setColor(15);
        else setColor(8);
        puts(books[l].title);
    }

}

void show_borrowed()
{
    int l;
    system("cls");
    setColor(12);
    printf("Enter to View Details-R to Return a Book\nBook ISBN\n");
    for(l=0; l<nBorrowed; l++)
    {
        if(CHOOSEN==l)setColor(15);
        else setColor(8);
        puts(borrowed[l].bookISBN);
    }

}

void show_borrowed_overDue()
{
    int l;
    overdueLength=0;
    system("cls");
    setColor(12);
    printf("Enter to View Details -Esc. to Back\nBook ISBN\n");
    for(l=0; l<nBorrowed; l++)
    {
        if(CHOOSEN==overdueLength)setColor(15);
        else setColor(8);
        if(!validateReturnDate(borrowed[l].dueToReturn.month,borrowed[l].dueToReturn.day,borrowed[l].dueToReturn.year))
        {
            puts(borrowed[l].bookISBN);
            overdue_books[overdueLength++]=l;
        }
    }

}

void view_book(Book* book)
{
    int tmp=CHOOSEN;///to delete book if needed
    CHOOSEN=0;

SWITCH1:
    i=0;
    system("cls");
    setColor(12);
    printf("Click Esc. To Return to Book Management - B to Borrow book if possible\n");

    checkColor();
    printf("Book Title: %s\n",book->title);
    i++;

    checkColor();
    printf("Author: %s\n",book->author);
    i++;
    checkColor();
    printf("Publisher: %s\n",book->publisher);
    i++;
    checkColor();
    printf("Book ISBN: %s\n",book->ISBN);
    i++;
    checkColor();
    printf("Category: %s\n",book->type);
    i++;
    checkColor();
    printf("Copies: %u\n",book->nCopies);
    i++;
    checkColor();
    printf("Available: %u\n",book->available);
    i++;
    checkColor();
    printf("Publication Date: %u/%u/%u \n",book->publicationDate.day,book->publicationDate.month,book->publicationDate.year);
//TO PREVENT USER FROM BREAKING OUT OF THIS FUNCTION
    switch(buffer=_getch()) /// VEIW BOOKS LOGIC
    {
    case 'B':
    case 'b':
        if(book->available>0)borrow_book(book);
        break;
    case 'D':
    case 'd':
        if(SEARCHING)delete_book(searched_books[tmp]);
        else delete_book(tmp);
    case (char)27:
        system("cls");
        SYSTEM=BOOKS;
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
        goto SWITCH1;
        break;
    case (char)13:

        edit_book(book);
        break;
    default:
        goto SWITCH1;
        break;

    }

}

void view_borrow(Borrowed* borrow)
{
    system("cls");
    setColor(10);
    printf("Click Esc. To Return to Borrow Management\n");

    setColor(12);
    printf("Book Title:");
    putBorrowed(borrow->bookISBN);
    ///FINDING MEMBER OF THAT ID
    printf("Member Name:");
    char fullName[200]= {0};
    int l;
    for(l=0; l<nMembersTmp; l++)
    {
        /// WE ARE COMPARING ID WITH MEMBERS IDs(cause its unique)
        if(borrow->memberID==members[l].ID)
        {
            strcat(strcat(strcat(fullName,members[l].fname)," "),members[l].lname);
            puts(fullName);
            break;
        }
        if(l==nMembersTmp-1)
        {
            printf("**Member Was Removed**\n");///if user was deleted we want to make sure it prints a new line
        }
    }
    setColor(15);
    printf("Book ISBN: %s\n",borrow->bookISBN);
    setColor(15);
    printf("Member ID: %u\n",borrow->memberID);
    setColor(14);
    printf("Issued: %u/%u/%u\n",borrow->issued.day,borrow->issued.month,borrow->issued.year);
    setColor(14);
    printf("Due To Return Date: %u/%u/%u\n",borrow->dueToReturn.day,borrow->dueToReturn.month,borrow->dueToReturn.year);
    if(borrow->returned.year)
    {
        setColor(14);
        printf("Return Date: %u/%u/%u \n",borrow->returned.day,borrow->returned.month,borrow->returned.year);
    }
    else
    {
        setColor(11);
        printf("Not Returned Yet!");
    }
    switch(buffer=_getch()) /// VEIW Borrow LOGIC
    {
    case (char)27:
        system("cls");
        SYSTEM=BORROW;
        break;
    default:
        view_borrow(borrow);
        break;
    }


}

///             SOME LOGIC FUNCTIONS ADDING REMOVING GETTING DATE BORROW RETURNING

void add_new_book()
{
    int flag;
    system("CLS");
    Book b;
    char B[100];
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    flag=VALIDATIONS_LOOP_NOTSYMBOLS("Enter Book Title:",B);
    if(!flag)return;
    strcpy(b.title,B);
    flag=VALIDATIONS_LOOP("Enter Author Name:",B);
    if(!flag)return;
    strcpy(b.author,B);
    flag=VALIDATIONS_LOOP("Enter Publisher Name:",B);
    if(!flag)return;
    strcpy(b.publisher,B);

    do
    {
        flag=VALIDATIONS_LOOP_NOTSYMBOLS("Enter ISBN:",B);
        if(!flag)return;
    }
    while(!check_isbn(B));
    strcpy(b.ISBN,B);
    flag=VALIDATIONS_LOOP("Category:",B);
    if(!flag)return;
    strcpy(b.type,B);
    flag=VALIDATIONS_LOOP_NUMBERS("Number Of Copies:",B);
    if(flag==-100)flag=0;
    b.nCopies=flag;
    b.available=flag;
    setColor(10);
    printf("Publication Date\n");
    do
    {
        flag=VALIDATIONS_LOOP_NUMBERS("Day:",B);
        if(!flag)return;
        if(flag==-100)flag=0;
        b.publicationDate.day=flag;
        flag=VALIDATIONS_LOOP_NUMBERS("Month:",B);
        if(!flag)return;
        if(flag==-100)flag=0;
        b.publicationDate.month=flag;
        flag=VALIDATIONS_LOOP_NUMBERS("Year:",B);
        if(!flag)return;
        if(flag==-100)flag=0;
        b.publicationDate.year=flag;
        flag=ValidateDate(b.publicationDate.day,b.publicationDate.month,b.publicationDate.year);
    }
    while(flag<0); ///LOOP TILL MEMBER TYPES "cancel" OR USING VALID DATE
    b.nBorrowed=0;
    books[nTmp] = b;
    nTmp++;
    system("cls");
}

void edit_book(Book* book)
{
    ///THERE ARE 8-1 things to edit so 8 cases for 0 to 7
    char B[100];
    int flag;
    system("cls");
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    switch(CHOOSEN)
    {
    case 0:
        flag=VALIDATIONS_LOOP_NOTSYMBOLS("Enter Book Title:",B);
        if(!flag)return;
        strcpy(book->title,B);
        break;
    case 1:
        flag=VALIDATIONS_LOOP("Enter Author Name:",B);
        if(!flag)return;
        strcpy(book->author,B);
        break;
    case 2:
        flag=VALIDATIONS_LOOP("Enter Publisher Name:",B);
        if(!flag)return;
        strcpy(book->publisher,B);
        break;
    case 3:
        do
        {
            flag=VALIDATIONS_LOOP_NOTSYMBOLS("Enter ISBN:",B);
            if(!flag)return;
        }
        while(!check_isbn(B));
        strcpy(book->ISBN,B);
        break;
    case 4:
        flag=VALIDATIONS_LOOP("Category:",B);
        if(!flag)return;
        strcpy(book->type,B);
        break;
    case 5:
    case 6:

        printf("You Cant Modify Copies or Available\ninstead You Can Add More Books\n");
        flag=VALIDATIONS_LOOP_NUMBERS("Number Of Copies:",B);
        if(flag==-100)flag=0;
        if(flag>=0)///CHECKING BECAUSE OF PREVIOUS CASE DIDNT RECHECK OF IT
        {
            books->nCopies+=flag;
            books->available+=flag;
        }
        break;
    case 7:
        printf("Publication Date:\n");
        do
        {
            flag=VALIDATIONS_LOOP_NUMBERS("Day:",B);
            if(flag==-100)flag=0;
            book->publicationDate.day=flag;
            flag=VALIDATIONS_LOOP_NUMBERS("Month:",B);
            if(flag==-100)flag=0;
            book->publicationDate.month=flag;
            flag=VALIDATIONS_LOOP_NUMBERS("Year:",B);
            if(flag==-100)flag=0;
            book->publicationDate.year=flag;
            flag=ValidateDate(book->publicationDate.day,book->publicationDate.month,book->publicationDate.year);
        }
        while(flag<0); ///LOOP TILL MEMBER TYPES "cancel" OR USING VALID DATE
        break;
    }
    view_book(book);

}

void delete_book(int k)
{
    if(books[k].nCopies!=books[k].available)
    {
        setColor(10);
        printf("This Book Was Borrowed So You Can't Delete It\n");
        system("pause");
        return;
    }
    int l;
    Borrowed borrowTmp;
    for(l=0; l<nBorrowed; l++)
    {

        if(!strcmp(borrowed[l].bookISBN,books[k].ISBN))
        {

            for(i=l; i<nBorrowed-1; i++)
            {
                borrowTmp=borrowed[i];
                borrowed[i] = borrowed[i+1];
                borrowed[i+1]=borrowTmp;
            }
            nBorrowed--;
            if(l>0) l--;
        }
    }

    Book tmp;
    for(i=k; i<nTmp-1; i++)
    {
        tmp=books[i];
        books[i] = books[i+1];
        books[i+1]=tmp;
    }

    show_books();

    nTmp--;
}

void apply_return_changes(const char *str,uint ID)
{
    int l;
    for(l=0; l<nTmp; l++)
    {
        if(!strcmp(books[l].ISBN,str))
        {
            books[l].available++;
        }
    }
    for(l=0; l<nMembersTmp; l++)
    {
        if(members[l].ID==ID)
        {
            members[l].booksBorrowed--;
        }
    }

}

void get_date(  int * month,int * day, int * year )
{
    struct tm *current;
    time_t timenow;
    time(&timenow);
    current = localtime(&timenow);
    *month = current->tm_mon+1;///cause its from 0 to 11 maps to 1->12
    *day = current->tm_mday;
    *year = current->tm_year+1900;///cause at 1900 it gives 0 so we add 1900
}

void borrow_book(Book* book)
{
    int flag;
    uint ID;
    char B[100];
    system("cls");
    fflush(stdin);//to make sure the buffer is empty
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    flag=VALIDATIONS_LOOP_NUMBERS("Enter Your ID:",B);
    if(!flag)return;
    if(flag==-100)flag=0;
    int tmP=verifyUserID(flag);
    if(tmP==-1)
    {
        setColor(12);
        printf("You Can't Borrow More Than 3 Books..\n");
        system("pause");
        return;
    }
    while(!tmP)
    {
        flag=VALIDATIONS_LOOP_NUMBERS("Wrong ID Re-Enter Your ID or Enter \"cancel\" to Back\nEnter Your ID:",B);
        if(!flag)return;
        if(flag==-100)flag=0;
        tmP=verifyUserID(flag);
        if(tmP==-1)
        {
            setColor(12);
            printf("You Can't Borrow More Than 3 Books..\n");
            system("pause");
            return;
        }
    }
    ID=flag;
    int month,day,year;

    get_date(&month,&day,&year);
    borrowed[nBorrowed].issued.day=day;
    borrowed[nBorrowed].issued.month=month;
    borrowed[nBorrowed].issued.year=year;
    setColor(10);
    printf("Enter Date Due To Return Date\n");
    do
    {
        do
        {
            flag=VALIDATIONS_LOOP_NUMBERS("Day:",B);
            if(!flag)return;
            if(flag==-100)flag=0;
            day=flag;
            flag=VALIDATIONS_LOOP_NUMBERS("Month:",B);
            if(!flag)return;
            if(flag==-100)flag=0;
            month=flag;
            flag=VALIDATIONS_LOOP_NUMBERS("Year:",B);
            if(!flag)return;
            year=flag;
            flag=ValidateDate(day,month,year);
        }
        while(flag<0); ///LOOP TILL MEMBER TYPES "cancel" OR USING VALID DATE
        setColor(15);

    }
    while(!validateReturnDate(day,month,year));
    borrowed[nBorrowed].dueToReturn.day=day;
    borrowed[nBorrowed].dueToReturn.month=month;
    borrowed[nBorrowed].dueToReturn.year=year;
    book->available--;
    book->nBorrowed++;
    strcpy(borrowed[nBorrowed].bookISBN,book->ISBN);
    borrowed[nBorrowed].memberID=ID;
    ///0 MEANS NOT RETURNED YET
    borrowed[nBorrowed].returned.day=0;
    borrowed[nBorrowed].returned.month=0;
    borrowed[nBorrowed].returned.year=0;
    nBorrowed++;
}

void return_book()
{
    system("cls");
    char B[100];
    char B2[100];
    int flag=0;
    setColor(10);
    printf("Type \"cancel\" to Cancel The Process\n");
    do
    {
        flag=VALIDATIONS_LOOP_NOTSYMBOLS("Enter ISBN:",B);
        if(!flag)return;
    }
    while(check_isbn(B));///check if its valid ISBN (exist in our library)
    flag=VALIDATIONS_LOOP_NUMBERS("Enter Your ID:",B2);
    if(!flag)return;
    if(flag==-100)flag=0;
    int tmP=verifyUserBorrowedID(flag,B);///RETURNS BORROWED INDEX IF VALID
    while(tmP==-1)
    {
        setColor(10);
        printf("Wrong ID Or ISBN Re-Enter Your ISBN&ID or Enter \"cancel\" to Back\n");
        do
        {
            flag=VALIDATIONS_LOOP("Enter ISBN:",B);
            if(!flag)return;
        }
        while(check_isbn(B));///check if its valid ISBN
        flag=VALIDATIONS_LOOP_NUMBERS("Enter Your ID:",B2);
        if(!flag)return;
        if(flag==-100)flag=0;
        tmP=verifyUserBorrowedID(flag,B);///RETURNS BORROWED INDEX IF VALID
    }
    apply_return_changes(borrowed[tmP].bookISBN,borrowed[tmP].memberID);
    int month,day,year;
    get_date(&month,&day,&year);
    borrowed[tmP].returned.day=day;
    borrowed[tmP].returned.month=month;
    borrowed[tmP].returned.year=year;

}

void find_book()
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
        ///TO MAKE SURE TO PRINT ALL RESULTS BEFORE SEARCHING
        tmpo=search_book(search_key);
        setColor(14);
        gotoxy(0,1);
        for(i=0; i<k; i++)printf("%c",search_key[i]);
//TO ERASE PREVIOUS CHARS if BackSpace Was Clicked
        printf(" ");
        setColor(12);
        gotoxy(0,0);
        printf("Click Esc to Cancel -");
        switch(FLAG)
        {
        case TITLE:
            printf("(Click <-/-> toChange)Search: Title           ");
            break;
        case AUTHOR:
            printf("(Click <-/-> toChange)Search: Author           ");
            break;
        case PUBLISHER:
            printf("(Click <-/-> toChange)Search: Publisher           ");
            break;
        case CATEGORY:
            printf("(Click <-/-> toChange)Search: Category           ");///SPACES TO ELIMINATE LAST PRINT
            break;
        }

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
            ///UP
            if(tmp==(char)72)
            {
                if(CHOOSEN>0)CHOOSEN--;
                ///DOWN
            }
            else if(tmp==(char)80)
            {
                if(CHOOSEN<tmpo-1)CHOOSEN++;//lets make it like that for now
                ///LEFT
            }
            else if(tmp==(char)75)
            {
                if(FLAG>0)FLAG--;
                else FLAG=3;
                tmpo=search_book(search_key);
                ///RIGHT
            }
            else if(tmp==(char)77)
            {
                if(FLAG<3)FLAG++;
                else FLAG=0;
                tmpo=search_book(search_key);
            }
        }
        else if(tmp==(char)13)
        {

            view_book(&books[searched_books[CHOOSEN]]);
        }
        else
        {
            ///ALL POSSIBLE LETTERS
            if(k<40&&(tmp>=32&&tmp<=126))
            {
                search_key[k++]=tmp;
            }
        }
    }
}

int search_book(const char* str)
{
    int k=0;
    int notFound=1;
    int results=0;
    setColor(12);
    Erase(k+2);//to clear previous search table
    int Counter;
    for(Counter=0; Counter<nTmp; Counter++)
    {
        if(k==CHOOSEN) setColor(15);
        else setColor(8);
///TODO 5ly el elements tet7t fel awl 7asb el searching
        switch(FLAG)
        {
        case TITLE:
            if(smart_search(books[Counter].title,str))
            {
                notFound=0;
                gotoxy(0,k+2);
                k++;
                printf("%s\n",books[Counter].title);
                searched_books[results]=Counter;
                results++;
            }
            break;
        case AUTHOR:
            if(smart_search(books[Counter].author,str))
            {
                notFound=0;
                gotoxy(0,k+2);
                k++;

                printf("%s\n",books[Counter].title);
                searched_books[results]=Counter;
                results++;
            }
            break;
        case PUBLISHER:
            if(smart_search(books[Counter].publisher,str))
            {
                notFound=0;
                gotoxy(0,k+2);
                k++;

                printf("%s\n",books[Counter].title);
                searched_books[results]=Counter;
                results++;
            }
            break;
        case CATEGORY:
            if(smart_search(books[Counter].type,str))
            {
                notFound=0;
                gotoxy(0,k+2);
                k++;

                printf("%s\n",books[Counter].title);
                searched_books[results]=Counter;
                results++;
            }
            break;
        }
    }
    if(notFound)
    {
        setColor(12);
        printf("Sorry,but your search did not match any documents.!!\n");
    }
    return results;
}


int smart_search(const char* str1,const char* str2)
{
    char* p1=str1;
    char* p2=str2;
    int tempor=strlen(str2);
    int tempor2;//for strlen of the pointer cant do it under label
    int counter;
LABEL:
    counter=0;
    tempor2=strlen(p1);
    for(i=0; i<tempor; i++)
    {
        if(*p1=='\0'||tempor2<tempor)break;
        ///ABS FOR INSENSITIVE SEARCH AS REQUIRED
        if(p1[i]!=p2[i]&&abs((int)p1[i]-(int)p2[i])!=32)
        {
            p1++;
            goto LABEL;
        }
        else
        {
            counter++;
        }
    }
    if(counter==tempor)return 1;
    return 0;
///1 indicates true 0 indicates false
}

int search_book_isbn(const char* isbn)
{
    for(i=0; i<nTmp; i++)
    {
        if(strcmp(books[i].ISBN,isbn))
        {
            return i;
        }
    }
    return -1;

}
///                     VALIDATION STUFF
/*check if ISBN IS INCORRECT*/
int check_isbn(const char* str)
{
    ///BEFORE 2007 10 char 3 dashes after 2007 13 chars 4 dashes(VALID ISBN)
    /// 0-7432-6951-9     978-1-61213-028-6(EXAMPLES)
    if(strlen(str)!=13&&strlen(str)!=17)return 0;
    for(i=0; i<nTmp; i++)
    {
        if(!strcmp(books[i].ISBN,str))return 0;//indicates invalid
    }
    return 1;//indicates valid
}

int validateReturnDate(int d,int m,int y)
{
    ///1 indicates input date is after current date
    int month,day,year;
    get_date(&month,&day,&year);
    if(y>year)return 1;
    if(year>y)return 0;
    if(month>m&&year==y)return 0;
    if(day>d&&month==m&&year==y)return 0;
    return 1;
}
