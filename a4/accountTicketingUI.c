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
#include <string.h>
#include <stdlib.h>
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#define TICKET_SIZE 17

void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
    return;
}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
    return;
}

void displayAccountSummaryRecord(const struct Account *account)
{
    char *type;
    if (account->accountType == 'C')
    {
        type = "CUSTOMER";
    }
    else
    {
        type = "AGENT";
    }
    printf("%05d %-9s %5d", account->accountNumber, type, account->demo.birthYear);
    printf("\n");
    return;
}

void displayAccountDetailRecord(const struct Account *account)
{
    int i;
    char *type, password[LOGIN_PASSWORD + 1] = {0};
    if (account->accountType == 'C')
    {
        type = "CUSTOMER";
    }
    else
    {
        type = "AGENT";
    }

    for (i = 0; i < LOGIN_PASSWORD; i++)
    {
        if (i % 2 != 0)
        {
            password[i] = '*';
        }
        else
        {
            password[i] = account->login.password[i];
        }
    }

    printf("%05d %-9.9s %5d $%10.2lf %-10.10s %-15.15s %-10.10s %8.8s",
           account->accountNumber,
           type,
           account->demo.birthYear,
           account->demo.income,
           account->demo.country,
           account->login.displayName,
           account->login.userName,
           password);
    printf("\n");
    return;
}

void applicationStartup(struct AccountTicketingData *data)
{
    int check = -2;
    while (1)
    {
        check = menuLogin(data->accounts, data->ACCOUNT_MAX_SIZE);
        if (data->accounts[check].accountType == 'C')
        {
            menuCustomer(data, &data->accounts[check]);
        }
        else if (data->accounts[check].accountType == 'A')
        {
            menuAgent(data, &data->accounts[check]);
        }
        else if (check == -1)
        {
            printf("==============================================\n");
            printf("Account Ticketing System - Terminated\n");
            printf("==============================================\n");
            printf("\n");
            break;
        }
    }

    return;
}

int menuLogin(const struct Account *accountConst, int maxNum)
{
    int sectionNum, indexNum, attempts, accountNum = 0;
    char exit = 'y', accountEnter[31],
         passwordEnter[31];
    do
    {
        indexNum = 0;
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");
        sectionNum = getIntFromRange(0, 1);
        if (sectionNum)
        {
            exit = 'y';
            attempts = 3;
            while (1)
            {
                printf("\n");
                indexNum = findAccountIndexByAcctNum(accountNum, accountConst, maxNum, 1);
                printf("User Login    : ");
                scanf("%[^\n]", accountEnter);
                scanf("%*c");
                printf("Password      : ");
                scanf("%[^\n]", passwordEnter);
                scanf("%*c");
                if (indexNum >= 0 &&
                    strcmp(accountEnter, accountConst[indexNum].login.userName) == 0 &&
                    strcmp(passwordEnter, accountConst[indexNum].login.password) == 0)
                {
                    printf("\n");
                    break;
                }
                else
                {
                    attempts--;
                    printf("INVALID user login/password combination! [attempts remaining:%d]\n",
                           attempts);
                    if (attempts == 0)
                    {
                        printf("\nERROR:  Login failed!\n\n");
                        indexNum = -2;
                        pauseExecution();
                        break;
                    }
                }
            }
        }
        else if (sectionNum == 0)
        {
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            exit = getCharOption("yYnN");
            if (exit == 'y' || exit == 'Y')
            {
                indexNum = -1;
            }
            printf("\n");
        }
    } while (exit == 'n' || exit == 'N');
    return indexNum;
}

void menuAgent(struct AccountTicketingData *data,
               const struct Account *accountConst)
{
    int i, j, selectionNum, accountNum = 0, indexNum = -1, biggestAccountNum;
    int accountsArced, tickectsArced, messageArced;
    char remove;
    while (1)
    {
        i = 0;
        printf("AGENT: %s (%d)\n", accountConst->login.displayName,
               accountConst->accountNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf(" 1) Add a new account\n");
        printf(" 2) Modify an existing account\n");
        printf(" 3) Remove an account\n");
        printf(" 4) List accounts: summary view\n");
        printf(" 5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf(" 6) List new tickets\n");
        printf(" 7) List active tickets\n");
        printf(" 8) List closed tickets\n");
        printf(" 9) Manage a ticket\n");
        printf("10) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("11) View archived account statistics\n");
        printf("12) View archived tickets statistics\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");
        printf("Selection: ");
        selectionNum = getIntFromRange(0, 12);
        printf("\n");
        if (selectionNum == 1)
        {
            i = 0, biggestAccountNum = 0;
            for (j = 0; j < data->ACCOUNT_MAX_SIZE; j++)
            {
                if (data->accounts[j].accountNumber > biggestAccountNum)
                {
                    biggestAccountNum = data->accounts[j].accountNumber;
                }
            }

            while (data->accounts[i].accountNumber != 0)
            {
                if (data->accounts[i].accountNumber == 0)
                {
                    break;
                }
                i++;
            }
            if (i < data->ACCOUNT_MAX_SIZE)
            {
                printf("New Account Data (Account#:%d)\n", biggestAccountNum + 1);
                printf("----------------------------------------\n");
                data->accounts[i].accountNumber = biggestAccountNum + 1;
                getAccount(&data->accounts[i]);
                getUserLogin(&data->accounts[i].login);
                getDemographic(&data->accounts[i].demo);
                printf("*** New account added! ***\n");
                clearStandardInputBuffer();
            }
            else
            {
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
            }
            printf("\n");
            pauseExecution();
        }
        else if (selectionNum == 2)
        {
            updateAccount(data->accounts);
        }
        else if (selectionNum == 3)
        {
            while (1)
            {
                indexNum = findAccountIndexByAcctNum(accountNum, data->accounts,
                                                     data->ACCOUNT_MAX_SIZE, 1);
                if (data->accounts[indexNum].accountNumber ==
                    accountConst->accountNumber)
                {
                    printf("\nERROR: You can't remove your own account!\n");
                    break;
                }
                else if (indexNum != -1)
                {
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&data->accounts[indexNum]);
                    printf("\n");
                    printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                    remove = getCharOption("YN");
                    if (remove == 'Y')
                    {
                        removeAccount(data->accounts, indexNum);
                        removeTickets(data, data->accounts[indexNum].accountNumber);
                        data->accounts[indexNum]
                            .accountNumber = 0;
                        printf("\n*** Account Removed! ***\n");
                    }
                    else if (remove == 'N')
                    {
                        printf("\n*** No changes made! ***\n");
                    }

                    break;
                }
                else
                {
                    printf("Error input\n");
                }
            }
            printf("\n");
            pauseExecution();
        }
        else if (selectionNum == 4)
        {
            displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
        }
        else if (selectionNum == 5)
        {
            displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
        }
        else if (selectionNum == 6)
        {
            displayAllTicketDetailRecords(data, data->accounts, 1, 1, 1);
        }
        else if (selectionNum == 7)
        {
            displayAllTicketDetailRecords(data, data->accounts, 0, 1, 1);
        }
        else if (selectionNum == 8)
        {
            displayAllTicketDetailRecords(data, data->accounts, 0, 0, 1);
        }
        else if (selectionNum == 9)
        {
            manageTicket(data, accountConst);
        }
        else if (selectionNum == 10)
        {
            printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
            remove = getCharOption("YN");
            if (remove == 'Y')
            {
                printf("\n*** %d tickets archived ***\n\n", archiveTickets(data));
            }
            else if (remove == 'N')
            {
                printf("\n*** No changes made! ***\n");
            }
            pauseExecution();
        }
        else if (selectionNum == 11)
        {
            accountsArced = 0;
            accountsArced = viewArchivedStatistics("accounts_arc.txt");
            printf("There are %d account(s) currently archived.\n\n",
                   accountsArced);
            pauseExecution();
        }
        else if (selectionNum == 12)
        {
            tickectsArced = 0;
            messageArced = 0;
            tickectsArced = viewArchivedStatistics("tickets_arc.txt");
            messageArced = viewArchivedMessage(data->TICKET_MAX_SIZE);
            printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n",
                   tickectsArced, messageArced);
            pauseExecution();
        }
        else if (selectionNum == 0)
        {
            accountsArced = 0;
            tickectsArced = 0;
            accountsArced = saveAccounts(data->accounts, data->ACCOUNT_MAX_SIZE);
            tickectsArced = saveTickets(data->tickets, data->TICKET_MAX_SIZE);
            printf("Saving session modifications...\n");
            printf("   %d account saved.\n", accountsArced);
            printf("   %d tickets saved.\n", tickectsArced);
            printf("### LOGGED OUT ###\n\n");
            break;
        }
        i = 0;
    }
    return;
}

void menuCustomer(struct AccountTicketingData *data,
                  const struct Account *accountConst)
{
    int selectionNum = 0, ticketsCount;
    while (1)
    {
        printf("CUSTOMER: %s (%d)\n",
               accountConst->login.displayName,
               accountConst->accountNumber);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) Create a new ticket\n");
        printf("3) Modify an active ticket\n");
        printf("4) List my tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");
        printf("Selection: ");
        selectionNum = getIntFromRange(0, 4);
        printf("\n");
        if (selectionNum == 1)
        {
            displayAllAccountDetailRecords(accountConst, 1);
            printf("\n");
            pauseExecution();
        }
        else if (selectionNum == 2)
        {
            createNewTicket(data, accountConst);
        }
        else if (selectionNum == 3)
        {
            modifyTicket(data, accountConst);
        }
        else if (selectionNum == 4)
        {
            displayAllTicketDetailRecords(data, accountConst, 0, 0, 0);
        }
        else if (selectionNum == 0)
        {
            ticketsCount = 0;
            ticketsCount = saveTickets(data->tickets, data->TICKET_MAX_SIZE);
            printf("Saving session modifications...\n");
            printf("   %d tickets saved.\n", ticketsCount);
            printf("### LOGGED OUT ###\n\n");
            break;
        }
    }
    return;
}

void displayAllAccountSummaryRecords(const struct Account *accountConst,
                                     int maxNum)
{
    int i;
    displayAccountSummaryHeader();
    for (i = 0; i < maxNum; i++)
    {
        if (accountConst[i].accountNumber != 0)
        {
            displayAccountSummaryRecord(&accountConst[i]);
        }
    }
    return;
}

void displayAllAccountDetailRecords(const struct Account *accountConst,
                                    int maxNum)
{
    int i;
    displayAccountDetailHeader();
    for (i = 0; i < maxNum; i++)
    {
        if (accountConst[i].accountNumber != 0)
        {
            displayAccountDetailRecord(&accountConst[i]);
        }
    }
    return;
}

void displayAllTicketDetailRecords(struct AccountTicketingData *data,
                                   const struct Account *accountConst,
                                   int newTickets, int activeTickets,
                                   int agentOrCus)
{
    int i, j, displayTicket[data->TICKET_MAX_SIZE], ticketEnter;
    char term;

    while (1)
    {
        i = 0, j = 0;
        if (agentOrCus == 1)
        {
            if (newTickets == 1 && activeTickets == 1)
            {
                displayTicketHeader(agentOrCus);

                for (i = 0; i < data->TICKET_MAX_SIZE; i++)
                {
                    if (data->tickets[i].ticketNum != 0 &&
                        data->tickets[i].ticketStatus != 0 &&
                        data->tickets[i].messageCounter == 1)
                    {
                        ticketStatus(&data->tickets[i], agentOrCus);
                        displayTicket[j] = data->tickets[i].ticketNum;
                        j++;
                    }
                }
            }
            else if (newTickets == 0 && activeTickets == 1)
            {
                displayTicketHeader(agentOrCus);
                for (i = 0; i < data->TICKET_MAX_SIZE; i++)
                {
                    if (data->tickets[i].ticketNum != 0 &&
                        data->tickets[i].ticketStatus != 0)
                    {
                        ticketStatus(&data->tickets[i], agentOrCus);
                        displayTicket[j] = data->tickets[i].ticketNum;
                        j++;
                    }
                }
            }
            else
            {
                displayTicketHeader(agentOrCus);
                for (i = 0; i < data->TICKET_MAX_SIZE; i++)
                {
                    if (data->tickets[i].ticketStatus == 0 &&
                        data->tickets[i].ticketNum != 0)
                    {
                        ticketStatus(&data->tickets[i], agentOrCus);
                        displayTicket[j] = data->tickets[i].ticketNum;
                        j++;
                    }
                }
            }
        }
        else
        {
            displayTicketHeader(agentOrCus);
            for (i = 0; i < data->TICKET_MAX_SIZE; i++)
            {
                if (data->tickets[i].customerNum == accountConst->accountNumber)
                {
                    ticketStatus(&data->tickets[i], agentOrCus);
                    displayTicket[j] = data->tickets[i].ticketNum;
                    j++;
                }
            }
        }

        if (agentOrCus == 1)
        {
            puts("------ ----- --------------- ------ ------------------------------ --------\n");
        }
        else
        {
            puts("------ ------ ------------------------------ --------\n");
        }
        puts("Enter the ticket number to view the messages or");
        printf("0 to return to previous menu: ");
        while (1)
        {
            term = '\0';
            scanf(" %d%c", &ticketEnter, &term);
            if (term == '\n')
            {
                if (ticketEnter >= 0)
                {
                    printf("\n");
                    break;
                }
                else
                {
                    printf("ERROR: Value must be positive or zero: ");
                }
            }
            else //for accidentally input a char
            {
                clearStandardInputBuffer();
                printf("ERROR: Value must be a positive integer greater than zero: ");
            }
        }
        if (ticketEnter == 0)
        {
            break;
        }
        else
        {
            //Double verify to get i for array
            i = 0, j = 0;
            while (displayTicket[j] != 0)
            {
                if (ticketEnter == displayTicket[j])
                {
                    while (1)
                    {
                        if (displayTicket[j] == data->tickets[i].ticketNum)
                        {
                            break;
                        }
                        i++;
                    }
                    break;
                }
                j++;
            }
            if (ticketEnter == data->tickets[i].ticketNum)
            {
                viewTicketMessage(&data->tickets[i]);
            }
            else
            {
                puts("ERROR: Invalid ticket number - you may only access your own tickets.\n");
            }
            pauseExecution();
        }
    }
    return;
}

void updateAccount(struct Account *accounts)
{
    int selectionNum = -1, accountNum = 0, indexNum, maxNum = 50;
    while (1)
    {
        indexNum = findAccountIndexByAcctNum(accountNum, accounts, maxNum, 1);
        printf("\n");
        if (indexNum == -1)
        {
            printf("Error input\n");
        }
        else
        {
            break;
        }
    }

    while (selectionNum != 0)
    {
        printf("Account: %d - Update Options\n", accounts[indexNum].accountNumber);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n",
               accounts[indexNum].accountType);
        printf("2) Login\n");
        printf("3) Demographics\n");
        printf("0) Done\n");
        printf("Selection: ");
        selectionNum = getIntFromRange(0, 3);
        if (selectionNum == 1)
        {
            printf("\n");
            printf("Enter the account type (A=Agent | C=Customer): ");
            accounts[indexNum].accountType = getCharOption("AC");
        }
        else if (selectionNum == 2)
        {
            printf("\n");
            updateUserLogin(&accounts[indexNum].login);
        }
        else if (selectionNum == 3)
        {
            printf("\n");
            updateDemographic(&accounts[indexNum].demo);
        }
        else if (selectionNum == 0)
        {
            printf("\n");
        }
    }
    return;
}

void updateUserLogin(struct UserLogin *login)
{
    int selectionNum = -1;
    while (selectionNum != 0)
    {
        printf("User Login: %s - Update Options\n", login->userName);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", login->displayName);
        printf("2) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        selectionNum = getIntFromRange(0, 2);
        if (selectionNum == 1)
        {
            printf("\n");
            printf("Enter the display name (%d chars max): ",
                   LOGIN_DISPLAY_CHARS);
            getCString(login->displayName, 2, LOGIN_DISPLAY_CHARS);
        }
        else if (selectionNum == 2)
        {
            printf("\n");
            userPasswordCheck(login);
        }
        printf("\n");
    }

    return;
}

void updateDemographic(struct Demographic *demo)
{
    int selectionNum = -1;
    while (selectionNum != 0)
    {
        printf("Demographic Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Household Income (current value: $%.2lf)\n", demo->income);
        printf("2) Country (current value: %s)\n", demo->country);
        printf("0) Done\n");
        printf("Selection: ");
        selectionNum = getIntFromRange(0, 2);
        if (selectionNum == 1)
        {
            printf("\n");
            printf("Enter the household Income: $");
            demo->income = getPositiveDouble();
        }
        else if (selectionNum == 2)
        {
            printf("\n");
            demoCountryToUpper(demo);
        }
        printf("\n");
    }

    return;
}

int findAccountIndexByAcctNum(int accountNum, const struct Account *accountConst,
                              int maxNum, int check)
{
    int i, result = -1, accountEnter;
    if (check == 0)
    {
        i = 0;
        while (i < maxNum)
        {
            if (accountNum == accountConst[i].accountNumber)
            {
                result = i;
                break;
            }
            i++;
        }
    }
    else if (check == 1)
    {
        i = 0;
        printf("Enter the account#: ");
        accountEnter = getPositiveInteger();
        for (i = 0; i < maxNum; i++)
        {
            if (accountEnter == accountConst[i].accountNumber)
            {
                result = i;
                break;
            }
        }
    }
    return result;
}

void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
    return;
}

int viewArchivedStatistics(const char *str)
{
    FILE *fp = fopen(str, "r");
    int charsRead, lines = 0;

    if (fp != NULL)
    {
        while ((charsRead = fgetc(fp)) != EOF)
        {
            if (charsRead == '\n')
                lines++;
        }
        fclose(fp);
        fp = NULL;
    }
    return lines;
}

int viewArchivedMessage(int size)
{
    FILE *fp;
    int i = 0, messageCounter[TICKET_SIZE] = {0}, msgCount = 0;
    fp = fopen("tickets_arc.txt", "r");
    if (fp != NULL)
    {
        while (i < size)
        {
            //store ticket messageCounter into messageCounter array
            fscanf(fp, "%*d|%*d|%*d|%*[^|]|%d|%*[^\n]", &messageCounter[i]);
            if (messageCounter[i] != 0)
            {
                msgCount += messageCounter[i];
            }
            i++;
        }
        fclose(fp);
        fp = NULL;
    }
    return msgCount;
}