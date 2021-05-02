/*
	==================================================
	Assignment #2 Milestone #4:
	==================================================
	Name   : Yi-Tso Kuo
	ID     : 166577197
	Email  : ytkuo@myseneca.ca
	Section: NHH
*/
#define MESSAGE_DISPLAY_CHARS 30
#define MESSAGE_DETAILS 150
#define TICKET_SUBJECT 30
#define MESSAGE_SIZE 20

#ifndef TICKET_H_
#define TICKET_H_
#include "accountTicketingUI.h"
// Header file contents goes here...

//Message
struct Message
{
    char accountType;
    char displayName[MESSAGE_DISPLAY_CHARS + 1];
    char details[MESSAGE_DETAILS + 1];
};

//Ticket
struct Ticket
{
    int ticketNum;
    int customerNum;
    int ticketStatus;
    char subject[TICKET_SUBJECT + 1];
    int messageCounter;
    struct Message message[MESSAGE_SIZE];
};

void displayTicketHeader(int);
void ticketStatus(const struct Ticket *, int);
void viewTicketMessage(const struct Ticket *);
void createNewTicket(struct AccountTicketingData *, const struct Account *);
void modifyTicket(struct AccountTicketingData *, const struct Account *);
void removeTickets(struct AccountTicketingData *, int);
void manageTicket(struct AccountTicketingData *, const struct Account *);
void closeTicketProcess(struct AccountTicketingData *, const struct Account *, int, int);
int loadTickets(struct Ticket *, int);
int archiveTickets(struct AccountTicketingData *);
int saveTickets(struct Ticket *, int);

#endif // !TICKET_H_