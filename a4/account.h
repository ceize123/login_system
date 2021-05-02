/*
	==================================================
	Assignment #2 Milestone #4:
	==================================================
	Name   : Yi-Tso Kuo
	ID     : 166577197
	Email  : ytkuo@myseneca.ca
	Section: NHH
*/

#define LOGIN_USER_CHARS 10
#define LOGIN_DISPLAY_CHARS 30
#define LOGIN_PASSWORD 8
#define DEMO_COUNTRY_CHARS 30
//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
// Header file contents goes here...

struct Demographic
{
    int birthYear;
    double income;
    char country[DEMO_COUNTRY_CHARS + 1];
};

struct UserLogin
{
    char displayName[LOGIN_DISPLAY_CHARS + 1];
    char userName[LOGIN_USER_CHARS + 1];
    char password[LOGIN_PASSWORD + 1];
};

struct Account
{
    int accountNumber;
    char accountType;
    struct UserLogin login; //don't put pointer here
    struct Demographic demo;
};

void getAccount(struct Account *);
void getUserLogin(struct UserLogin *);
void getDemographic(struct Demographic *);
void userLoginCheck(struct UserLogin *);
void userPasswordCheck(struct UserLogin *);
void demoCountryToUpper(struct Demographic *);
int loadAccounts(struct Account *, int);
void removeAccount(struct Account *, int);
int saveAccounts(struct Account *, int);

#endif // !ACCOUNT_H_