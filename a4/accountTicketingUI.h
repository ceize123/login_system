/*
	==================================================
	Assignment #2 Milestone #4:
	==================================================
	Name   : Yi-Tso Kuo
	ID     : 166577197
	Email  : ytkuo@myseneca.ca
	Section: NHH
*/
#include "account.h"
#include "ticket.h"

//
// Your identification information commented header goes here...
//
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
// Header file contents goes here...

//AccountTicketingData
struct AccountTicketingData
{
	struct Account *accounts;
	const int ACCOUNT_MAX_SIZE;

	struct Ticket *tickets;
	const int TICKET_MAX_SIZE;
};

void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account *);
void displayAccountDetailRecord(const struct Account *);
void applicationStartup(struct AccountTicketingData *);
int menuLogin(const struct Account *, int);
void menuAgent(struct AccountTicketingData *, const struct Account *);
void menuCustomer(struct AccountTicketingData *, const struct Account *);
void displayAllAccountSummaryRecords(const struct Account *, int);
void displayAllAccountDetailRecords(const struct Account *, int);
//newTickets and activeTickets for determining how I grab data
void displayAllTicketDetailRecords(struct AccountTicketingData *,
								   const struct Account *,
								   int, int, int);
void updateAccount(struct Account *);
void updateUserLogin(struct UserLogin *);
void updateDemographic(struct Demographic *);
int findAccountIndexByAcctNum(int, const struct Account *, int, int);
void pauseExecution(void);
int viewArchivedStatistics(const char *);
int viewArchivedMessage(int);

#endif // !ACCOUNT_TICKETING_UI_H_