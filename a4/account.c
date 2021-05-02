/*
	==================================================
	Assignment #2 Milestone #4:
	==================================================
	Name   : Yi-Tso Kuo
	ID     : 166577197
	Email  : ytkuo@myseneca.ca
	Section: NHH
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "commonHelpers.h"
#include "account.h"

//getAccount
void getAccount(struct Account *account)
{
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->accountType = getCharOption("AC");
    printf("\n");
    return;
}

//getUserLogin
void getUserLogin(struct UserLogin *login)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    userLoginCheck(login);
    printf("Enter the display name (%d chars max): ", LOGIN_DISPLAY_CHARS);
    getCString(login->displayName, 2, LOGIN_DISPLAY_CHARS);
    userPasswordCheck(login);
    printf("\n");
    return;
}

//getDemographic
void getDemographic(struct Demographic *demo)
{
    int oldestAge = currentYear() - 110;
    int youngestAge = currentYear() - 18;
    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter birth year (current age must be between 18 and 110): ");
    demo->birthYear = getIntFromRange(oldestAge, youngestAge);
    printf("Enter the household Income: $");
    demo->income = getPositiveDouble();
    demoCountryToUpper(demo);
    printf("\n");
    return;
}

//userLoginCheck
void userLoginCheck(struct UserLogin *login)
{
    int i, checkSpace = 0;
    char ch;
    while (checkSpace == 0)
    {
        printf("Enter user login (%d chars max): ", LOGIN_USER_CHARS);
        getCString(login->userName, 2, LOGIN_USER_CHARS);
        for (i = 0; i < LOGIN_USER_CHARS; i++)
        {
            ch = login->userName[i];
            if (isspace(ch))
            {
                checkSpace = 0;
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
                break;
            }
            else
            {
                checkSpace = 1;
            }
        }
    }
    return;
}

void userPasswordCheck(struct UserLogin *login)
{
    int i, checkPassword = 0;
    char ch;
    while (checkPassword == 0)
    {
        int countDigit = 0, countUppercase = 0, countLowercase = 0, countSymbol = 0;
        checkPassword = 0;
        printf("Enter the password (must be %d chars in length): ", LOGIN_PASSWORD);
        getCString(login->password, LOGIN_PASSWORD, LOGIN_PASSWORD);
        for (i = 0; i < LOGIN_PASSWORD; i++)
        {
            ch = login->password[i];
            if (islower(ch))
            {
                countLowercase += 1;
            }
            else if (isupper(ch))
            {
                countUppercase += 1;
            }
            else if (isdigit(ch))
            {
                countDigit += 1;
            }
            else if (ch == '!' || ch == '@' || ch == '#' || ch == '$' ||
                     ch == '%' || ch == '^' || ch == '&' || ch == '*')
            {
                countSymbol += 1;
            }
        }
        if (countDigit == 2 &&
            countLowercase == 2 &&
            countUppercase == 2 &&
            countSymbol == 2)
        {
            checkPassword = 1;
        }
        else
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character: !@#$%%^&*\n");
        }
    }
    return;
}

//demoCountryToUpper
void demoCountryToUpper(struct Demographic *demo)
{
    int i = 0;
    printf("Enter the country (%d chars max.): ", DEMO_COUNTRY_CHARS);
    getCString(demo->country, 1, DEMO_COUNTRY_CHARS);
    while (demo->country[i] != '\0')
    {
        demo->country[i] = toupper(demo->country[i]);
        i++;
    }
    return;
}

int loadAccounts(struct Account *account, int accountsSize)
{

    FILE *fp = fopen("accounts.txt", "r");
    int i, accountsLoaded = 0;

    if (fp != NULL)
    {
        for (i = 0; i < accountsSize; i++)
        {
            fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]",
                   &account[i].accountNumber,
                   &account[i].accountType,
                   account[i].login.displayName,
                   account[i].login.userName,
                   account[i].login.password,
                   &account[i].demo.birthYear,
                   &account[i].demo.income,
                   account[i].demo.country);

            if (account[i].accountNumber != 0)
            {
                accountsLoaded++;
            }
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: Can't open file!\n");
        //account problem return 1
        exit(1);
    }
    return accountsLoaded;
}

void removeAccount(struct Account *account, int index)
{
    FILE *fp = fopen("accounts_arc.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
                account[index].accountNumber,
                account[index].accountType,
                account[index].login.displayName,
                account[index].login.userName,
                account[index].login.password,
                account[index].demo.birthYear,
                account[index].demo.income,
                account[index].demo.country);

        fclose(fp);
        fp = NULL;
    }
    else
    {
        exit(1);
    }
    return;
}

int saveAccounts(struct Account *account, int accountsSize)
{
    FILE *fp = fopen("accounts.txt", "w");
    int i, accountsCount = 0;

    if (fp != NULL)
    {
        for (i = 0; i < accountsSize; i++)
        {
            if (account[i].accountNumber != 0)
            {

                fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s",
                        account[i].accountNumber,
                        account[i].accountType,
                        account[i].login.displayName,
                        account[i].login.userName,
                        account[i].login.password,
                        account[i].demo.birthYear,
                        account[i].demo.income,
                        account[i].demo.country);

                fprintf(fp, "\n");
                accountsCount++;
            }
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        exit(1);
    }
    return accountsCount;
}