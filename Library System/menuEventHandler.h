#ifndef MENUEVENTHANDLER_H
#define MENUEVENTHANDLER_H
typedef unsigned int uint;//TYPEDEF FOR UNSIGNED INT FOR EASY USE
#include <math.h>//USED IN SMART SEARCH abs Func.
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "member.h"
#include "books.h"
#include "cmdNavigation.h"
/*                       SYSTEM ENUMS FOR GAME STATE AND OPTIONS                             */
enum gameState {MENU=0,BOOKS,MEMBERS,BORROW,ADMIN,SAVE,EXIT} SYSTEM;
enum searchOption {TITLE=0,AUTHOR,PUBLISHER,CATEGORY} FLAG;

/*                               VARIABLES                               */
//SYSTEM STUFF
int esc;// flag to check whether im still in the menu or i entered another one
int RUNNING;//FLAG FOR MAIN PROGRAM LOOP WON'T BE CHANGED UNLESS USER WANTS TO EXIT THE GAME
int i;//loops counter CAUSE IM LAZY I KNOW ITS NOT THAT GOOD
int CHOOSEN;//to scroll through main menu
char buffer; //Hold Key Presses to never lose clicked button on keyboard

/*                                FUNCTIONS                                                */
///SYSTEM INIT FUNCTIONS
extern void progStart();//INITIALIZE SYSTEM ENUMS -FLAGS AND LOADS THE DATA FROM FILES

///SYSYTEM DESIGN RELATED STUFF
extern void Erase(int startR);//CLEAR SCREEN FROM CERTAIN ROW USED IN SEARCH

///MENU STUFF AND LOGIC
extern void menuHandler();//RUNS MAIN MENU AND ITS LOGIC STUFF
extern void menuLogic();//CHECK WHAT THE USER CLICKED TO DETERMINE WHAT TO DO
extern void books_logic(int k);//AS ABOVE BUT FOR BOOKS SECTION
extern void members_logic(int k);//AS ABOVE BUT FOR MEMBERS SECTION
extern void borrow_logic(int k);//AS ABOVE BUT FOR BORROW SECTION
extern void admin_logic(int k);//AS ABOVE BUT FOR ADMIN SECTION
extern void overDue();//SHOWS OVERDUE BOOKS AND RUNS ITS LOGIC
extern void popularBooks();//SHOWS POPULAR BOOKS
extern void checkColor();//CHECK COLOR AND PUT IT DEPENDS ON USER CURRENT CURSOR POSITION

///SORTING STUFF
extern void bubbleSortBOOK(struct Book *arr,size_t s,char flag);
extern void bubbleSortMEMBER(struct Member *arr,size_t s);
extern void swapBOOK(struct Book *pr1,struct Book* pr2);
extern void swapMEMBER(struct Member *pr1,struct Member* pr2);

///VALIDATION STUFF
extern int VALIDATIONS_LOOP(const char* message,char *input);//RUNS DO WHILE LOOP TILL USER PUTS VALID STRING (NO NUMBERS NO SYMBOLS)
extern int VALIDATIONS_LOOP_NUMBERS(const char* message,char *input);//RUNS DO WHILE LOOP TILL USER PUTS VALID NUMBER (NO SYMBOLS NO STRING)
extern int VALIDATIONS_LOOP_NOTSYMBOLS(const char* message,char *input);//RUNS DO WHILE LOOP TILL USER PUTS VALID STRING(NO SYMBOLS)
extern int ValidateString(const char* str);//VALIDATE STRING AND RETURNS FLAG TO CHECK WHICH ERROR IS IT
extern int ValidatePhoneNumber(const char* str);//VALIDATE PHONE NUMBER AND RETURNS FLAG TO CHECK WHICH ERROR IS IT
extern int ValidateAge(const uint u);//VALIDATE AGE RANGE:7-110
extern int ValidateDate(const uint d,const uint m,const uint y);//VALIDATE DATE SO USER CAN'T PUT MONTH AS 13 for example
extern uint checkIfNumber(const char* str);//CHECK IF GIVEN STRING HAS ONLY NUMBERS IN IT

#endif // MENUVENTHANDLER_H
