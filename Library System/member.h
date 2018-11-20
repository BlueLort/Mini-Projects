#ifndef MEMBER_H
#define MEMBER_H
#include "menuEventHandler.h"
/*                                   STRUCTURES                     */
typedef struct Address
{
    char zone[40];
    char street[40];
    char city[40];
} Address;
typedef struct Member
{
    char fname[40];//first name
    char lname[40];//last name
    uint ID;//ID OF THE MEMBER RAND. Generated
    Address address;
    char phoneNumber[20];//phone number
    uint age;
    uint booksBorrowed;
    char email[40];//email of the member
} Member;
///MEMBER VARS.
//uint nMembers;//TOTAL MEMBERS ON THE SYSTEM SAVED
uint nMembersTmp;
Member members[100];
int searched_members[100];
/*                                FUNCTIONS                                                */
/* ALL OF THEM ARE EXTERN TO MAKE SURE THAT THEY ARE IMPLEMENTED IN SOURCE FILE (AVOIDING HUMAN ERROR) */
///SAVE to FILE
extern void saveMembers();

///LOADING from FILE
extern void loadMembers();

///SHOWING DETAILS
extern void show_members();//SHOWS ALL MEMBERS IN THE LIBRARY
extern void view_member(Member* MEMBER);//SHOW CERTAIN MEMBER INFO
extern void putBorrowed(const char* str);//PRINTS BOOK BASED ON str(if str == some ISBN)

///SOME LOGIC FUNCTIONS REGISTER REMOVING
extern void registerMember();//ADDS NEW MEMBER
extern void edit_member(Member* member);//EDIT MEMBER LOGIC
extern void remove_member(int k);//REMOVES MEMBER
extern uint generateID();//GENERATES RANDOM ID FOR USER

///SEARCHING FUNCTIONS
extern void find_member();//MAIN LOGIC AND IT STARTS SERIES OF FUNCTIONS
extern int search_member(const char* str);//MAIN LOGIC AND IT STARTS SERIES OF FUNCTIONS and then smart_search->books.h

///VALIDATION STUFF
extern int verifyUserID(uint ID);//CHECK IF USER ID EXISTS AND IF HE CAN BORROW BOOKS
extern int verifyUserBorrowedID(uint ID,const char* str);//VERIFY THAT USER ENTERED VALID ID AND ISBN EXISTING IN THE LIBRARY
extern int verifyEmail(const char* str);//VALIDATION FOR EMAIL INPUT

#endif
