#ifndef BOOKS_H
#define BOOKS_H
#include "menuEventHandler.h"
/*                                   STRUCTURES                     */
typedef struct
{
    uint day;
    uint month;
    uint year;
} date;

typedef struct Book
{
    char title[60];//Title of the book
    char author[40];//Author name
    char publisher[40];//publisher name
    char ISBN[40];//ISBN OF THE BOOK
    char type[20];//category of the book
    uint nCopies;
    uint available;
    uint nBorrowed;
    date publicationDate;
} Book;

typedef struct Borrowed
{
    uint memberID;
    char bookISBN[40];
    date issued;
    date dueToReturn;
    date returned;
} Borrowed;
/*                               VARIABLES                               */
//uint n;//TOTAL BOOKS ON THE SYSTEM SAVED
///BOOKS VARS.
uint nTmp;///TO HANDLE RUNNING TIME
int SEARCHING;///FLAG TO KNOW IF IM SEARCHING OR I'M NOT
Book books[100];
///BORROWING VARS.
Borrowed borrowed[500];///MEMBERS SIZE x3 WORST CASE and relatively large array to hold returned and unreturned books
uint nBorrowed;/// BORROWED SIZE
int searched_books[100];///indicies of searched books
///OVER DUE VARS.
int overdueLength;///UNLIKE MEMBERS BOOKS IN SEARCH IT DOESNT HAVE A FUNCTION TO KNOW ITS SIZE
int overdue_books[500];///indicies of overdue books
/*                                FUNCTIONS                                                */
/* ALL OF THEM ARE EXTERN TO MAKE SURE THAT THEY ARE IMPLEMENTED IN SOURCE FILE (AVOIDING HUMAN ERROR) */
///SAVE to FILE
extern void save_books();
extern void save_borrowed();

///LOADING from FILE
extern void load_books();
extern void load_borrowed();

///SHOWING DETAILS
extern void show_books();//SHOWS ALL THE BOOKS
extern void show_borrowed();//SHOWS ALL THE BORROWED BOOKS
extern void show_borrowed_overDue();//SHOWS ALL THE OVERDUE BOOKS
extern void view_book(Book* book);//SHOWS book DETAILS
extern void view_borrow(Borrowed* borrow);//SHOWS borrow DETAILS

///SOME LOGIC FUNCTIONS ADDING REMOVING GETTING DATE
extern void add_new_book();//ADDS NEW BOOK IN THE LIBRARY
extern void edit_book(Book* book);//EDITS EXISTING BOOK
extern void delete_book(int k);//REMOVES BOOK FROM LIBRARY
extern void apply_return_changes(const char *str,uint ID);//INCREASE NUMBER OF AVAILABLE FOR BOOKS AND APPLY SOME OTHER CHANGES
extern void get_date(  int * month,int * day, int * year );//PUT CURRENT DATE VALUES FOR DAY MONTH YEAR
extern void borrow_book(Book* book);//RUNS BORROW BOOK AND ASKS USER FOR HIS INFO
extern void return_book();//ASKS USER FOR INFO AND RETURNS THE BOOK

///SEARCHING FUNCTIONS
extern void find_book();//MAIN LOGIC AND IT STARTS SERIES OF FUNCTIONS
extern int search_book(const char* str);//it start operation on the string given from find_book
extern int smart_search(const char* str1,const char* str2);//The main LOGIC Of Comparing and coming up with a result
extern int search_book_isbn(const char* isbn);//CHECK IF CERTAIN ISBN IS IN OUR LIBRARY OR NOT FOR BORROWING

///VALIDATION STUFF
extern int check_isbn(const char* str);//CHECK IF ITS VALID ISBN LENGTH &EXISTS IN OUR LIBRARY OR NOT
extern int validateReturnDate(int d,int m,int y);//CHECK IF GIVEN DATE HAVE PASSED CURRENT DATE OR NOT

#endif // BOOKS_H
