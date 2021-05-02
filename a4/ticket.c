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
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

//Ticket
//displayTicketHeader
void displayTicketHeader(int agentOrCus)
{
	if (agentOrCus == 1)
	{
		puts("------ ----- --------------- ------ ------------------------------ --------");
		puts("Ticket Acct# Display Name    Status Subject                        Messages");
		puts("------ ----- --------------- ------ ------------------------------ --------");
	}
	else if (agentOrCus == 0)
	{
		puts("------ ------ ------------------------------ --------");
		puts("Ticket Status Subject                        Messages");
		puts("------ ------ ------------------------------ --------");
	}
	return;
}

//displayTicketRecord
void ticketStatus(const struct Ticket *ticket, int agentOrCus)
{
	char *status;
	if (ticket->ticketStatus == 1)
	{
		status = "ACTIVE";
	}
	else
	{
		status = "CLOSED";
	}

	if (agentOrCus == 1)
	{
		printf("%06d %5d %-15.15s %-6.6s %-30.30s    %2d\n",
			   ticket->ticketNum,
			   ticket->customerNum,
			   ticket->message->displayName,
			   status,
			   ticket->subject,
			   ticket->messageCounter);
	}
	else if (agentOrCus == 0)
	{
		printf("%06d %-6.6s %-30.30s    %2d\n",
			   ticket->ticketNum,
			   status,
			   ticket->subject,
			   ticket->messageCounter);
	}
	return;
}

//displayMessage
void viewTicketMessage(const struct Ticket *ticket)
{
	int i = 0;
	char *status, *type;
	if (ticket->ticketStatus == 1)
	{
		status = "ACTIVE";
	}
	else
	{
		status = "CLOSED";
	}
	puts("================================================================================");
	printf("%06d (%s) Re: %s\n", ticket->ticketNum, status, ticket->subject);
	puts("================================================================================");
	while (ticket->message[i].accountType != 0 &&
		   ticket->message[0].accountType == 'C' &&
		   i < MESSAGE_SIZE)
	{
		if (i % 5 == 0 && i != 0)
		{
			pauseExecution();
		}
		if (ticket->message[i].accountType == 'C')
		{
			type = "CUSTOMER";
		}
		else
		{
			type = "AGENT";
		}
		printf("%s (%s):\n", type, ticket->message[i].displayName);
		printf("   %s\n\n", ticket->message[i].details);
		i++;
	}
	return;
}

//createNewTicket
void createNewTicket(struct AccountTicketingData *data,
					 const struct Account *accountConst)
{
	int i, biggest = 0;
	char subjectEnter[TICKET_SUBJECT + 1] = {0};
	char messageEnter[MESSAGE_DETAILS + 1] = {0};
	for (i = 0; i < data->TICKET_MAX_SIZE; i++)
	{
		if (biggest < data->tickets[i].ticketNum)
		{
			biggest = data->tickets[i].ticketNum;
		}

		if (data->tickets[i].ticketNum == 0 && i <= data->TICKET_MAX_SIZE)
		{
			data->tickets[i].customerNum = accountConst->accountNumber;
			break;
		}
		else if (data->tickets[i].ticketNum != 0 && i == data->TICKET_MAX_SIZE - 1)
		{
			puts("ERROR: Ticket listing is FULL, call ITS Support!");
			printf("\n");
			pauseExecution();
			return;
		}
	}

	data->tickets[i].ticketNum = biggest + 1;
	printf("New Ticket (Ticket#:%06d)\n", data->tickets[i].ticketNum);
	puts("----------------------------------------");
	printf("Enter the ticket SUBJECT (%d chars. maximum): ",
		   TICKET_SUBJECT);
	getCString(subjectEnter, 2, TICKET_SUBJECT);
	strcpy(data->tickets[i].subject, subjectEnter);
	printf("\n");
	printf("Enter the ticket message details (%d chars. maximum). Press the ",
		   MESSAGE_DETAILS);
	printf("ENTER key to submit:\n");
	getCString(messageEnter, 2, MESSAGE_DETAILS);
	strcpy(data->tickets[i].message[0].details, messageEnter);
	puts("\n*** New ticket created! ***\n");
	data->tickets[i].messageCounter = 1;
	data->tickets[i].ticketStatus = 1;
	data->tickets[i].message->accountType = accountConst->accountType;
	strcpy(data->tickets[i].message->displayName, accountConst->login.displayName);
	clearStandardInputBuffer();
	pauseExecution();
	return;
}

//manage by customer side
void modifyTicket(struct AccountTicketingData *data,
				  const struct Account *accountConst)
{
	int i, j, ticketNumEnter, selectNum, done = 0;
	char *status;
	char subjectEnter[TICKET_SUBJECT + 1] = {0};
	char messageEnter[MESSAGE_DETAILS + 1] = {0};
	printf("Enter ticket number: ");
	scanf("%d%*c", &ticketNumEnter);
	printf("\n");
	for (i = 0; i < data->TICKET_MAX_SIZE; i++)
	{
		if (ticketNumEnter == data->tickets[i].ticketNum &&
			data->tickets[i].customerNum == accountConst->accountNumber)
		{
			break;
		}
	}

	if (i == data->TICKET_MAX_SIZE)
	{
		puts("ERROR: Invalid ticket number - you may only modify your own ticket.\n");
		pauseExecution();
		return;
	}

	if (data->tickets[i].ticketStatus == 1)
	{
		status = "ACTIVE";
		while (!done)
		{
			puts("----------------------------------------");
			printf("Ticket %06d - Update Options\n", data->tickets[i].ticketNum);
			puts("----------------------------------------");
			printf("Status  : %s\n", status);
			printf("Subject : %s\n", data->tickets[i].subject);
			puts("----------------------------------------");
			puts("1) Modify the subject");
			puts("2) Add a message");
			puts("3) Close ticket");
			puts("0) Done");
			printf("Selection: ");
			scanf("%d%*c", &selectNum);
			printf("\n");
			switch (selectNum)
			{
			case 1:
				printf("Enter the revised ticket SUBJECT (%d chars. maximum): ",
					   TICKET_SUBJECT);
				getCString(subjectEnter, 2, TICKET_SUBJECT);
				strcpy(data->tickets[i].subject, subjectEnter);
				printf("\n");
				break;
			case 2:
				if (data->tickets[i].messageCounter == MESSAGE_SIZE)
				{
					puts("ERROR: Message limit has been reached, call ITS Support!\n");
					break;
				}
				printf("Enter the ticket message details (%d chars. maximum). Press the ",
					   MESSAGE_DETAILS);
				printf("ENTER key to submit:\n");
				getCString(messageEnter, 2, MESSAGE_DETAILS);
				for (j = 1; j < MESSAGE_SIZE; j++)
				{
					if (data->tickets[i].message[j].accountType == 0 &&
						j <= data->tickets[i].messageCounter)
					{
						strcpy(data->tickets[i].message[j].displayName,
							   accountConst->login.displayName);
						data->tickets[i].message[j].accountType = accountConst->accountType;
						strcpy(data->tickets[i].message[j].details, messageEnter);
						break;
					}
				}
				data->tickets[i].messageCounter += 1;
				printf("\n");
				break;
			case 3:
				if (data->tickets[i].ticketStatus == 0)
				{
					puts("ERROR: Ticket is closed - changes are not permitted.\n");
					pauseExecution();
					break;
				}
				closeTicketProcess(data, accountConst, i, 0);
				done = 1;
				break;
			case 0:
				done = 1;
				pauseExecution();
				break;
			}
		}
	}
	else if (data->tickets[i].ticketStatus == 0)
	{
		printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
		pauseExecution();
	}
	return;
}

void removeTickets(struct AccountTicketingData *data, int accountNum)
{
	FILE *fp = fopen("tickets_arc.txt", "a");
	int i, j = 0;

	if (fp != NULL)
	{
		for (i = 0; i < data->TICKET_MAX_SIZE; i++)
		{
			if (data->tickets[i].customerNum == accountNum)
			{
				if (data->tickets[i].ticketNum != 0 &&
					data->tickets[i].ticketStatus == 0)
				{
					fprintf(fp, "%d|%d|%d|%s|%d|",
							data->tickets[i].ticketNum,
							data->tickets[i].customerNum,
							data->tickets[i].ticketStatus,
							data->tickets[i].subject,
							data->tickets[i].messageCounter);

					while (j < data->tickets[i].messageCounter)
					{
						fprintf(fp, "%c|%s|%s|",
								data->tickets[i].message[j].accountType,
								data->tickets[i].message[j].displayName,
								data->tickets[i].message[j].details);
						j++;
					}
					fprintf(fp, "\n");
				}
				data->tickets[i].ticketNum = 0;
			}
			j = 0;
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		exit(2);
	}
	return;
}

//manage by agent side
void manageTicket(struct AccountTicketingData *data, const struct Account *accountConst)
{
	int i, j, ticketNumEnter, selectNum, done = 0;
	char *status, reOpenTicket;
	char messageEnter[MESSAGE_DETAILS + 1] = {0};
	printf("Enter ticket number: ");
	scanf("%d%*c", &ticketNumEnter);
	printf("\n");
	for (i = 0; i < data->TICKET_MAX_SIZE; i++)
	{
		if (ticketNumEnter == data->tickets[i].ticketNum)
		{
			break;
		}
	}
	if (i == data->TICKET_MAX_SIZE)
	{
		puts("ERROR: Invalid ticket number\n");
		return;
	}

	while (!done)
	{
		if (data->tickets[i].ticketStatus == 1)
		{
			status = "ACTIVE";
		}
		else
		{
			status = "CLOSED";
		}
		puts("----------------------------------------");
		printf("Ticket %06d - Update Options\n", data->tickets[i].ticketNum);
		puts("----------------------------------------");
		printf("Status  : %s\n", status);
		printf("Subject : %s\n", data->tickets[i].subject);
		printf("Acct#   : %d\n", data->tickets[i].customerNum);
		printf("Customer: %s\n", data->tickets[i].message->displayName);
		puts("----------------------------------------");
		puts("1) Add a message");
		puts("2) Close ticket");
		puts("3) Re-open ticket");
		puts("0) Done");
		printf("Selection: ");
		scanf("%d%*c", &selectNum);
		printf("\n");
		switch (selectNum)
		{
		case 1:
			if (data->tickets[i].ticketStatus == 0)
			{
				puts("ERROR: Ticket is closed - new messages are not permitted.\n");
				break;
			}
			for (j = 1; j < data->TICKET_MAX_SIZE; j++)
			{
				if (data->tickets[i].message[j].accountType == 0 &&
					j <= data->tickets[i].messageCounter)
				{
					data->tickets[i].message[j].accountType = accountConst->accountType;
					strcpy(data->tickets[i].message[j].displayName,
						   accountConst->login.displayName);
					break;
				}
			}
			if (j == data->TICKET_MAX_SIZE)
			{
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
				break;
			}
			printf("Enter the ticket message details (%d chars. maximum). Press the ",
				   MESSAGE_DETAILS);
			printf("ENTER key to submit:\n");
			getCString(messageEnter, 2, MESSAGE_DETAILS);
			printf("\n");
			strcpy(data->tickets[i].message[j].details, messageEnter);
			data->tickets[i].messageCounter += 1;
			break;
		case 2:
			if (data->tickets[i].ticketStatus == 0)
			{
				puts("ERROR: Ticket is already closed!\n");
				break;
			}
			else
			{
				closeTicketProcess(data, accountConst, i, 1);
			}
			break;
		case 3:
			if (data->tickets[i].ticketStatus == 1)
			{
				printf("ERROR: Ticket is already active!\n\n");
				break;
			}
			printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
			reOpenTicket = getCharOption("YN");
			printf("\n");
			if (reOpenTicket == 'Y')
			{
				data->tickets[i].ticketStatus = 1;
				printf("*** Ticket re-opened! ***\n\n");
			}
			break;
		case 0:
			done = 1;
			break;
		}
	}
	return;
}

void closeTicketProcess(struct AccountTicketingData *data,
						const struct Account *accountConst,
						int index, int agentOrCus)
{
	int j;
	char closeTicket, leaveMsg;
	char messageEnter[MESSAGE_DETAILS + 1] = {0};
	printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
	closeTicket = getCharOption("YN");
	if (closeTicket == 'Y')
	{
		if (data->tickets[index].messageCounter != MESSAGE_SIZE)
		{
			printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
			leaveMsg = getCharOption("YN");
			printf("\n");
			if (leaveMsg == 'Y')
			{
				printf("Enter the ticket message details (%d chars. maximum). Press the ",
					   MESSAGE_DETAILS);
				printf("ENTER key to submit:\n");
				getCString(messageEnter, 2, MESSAGE_DETAILS);
				for (j = 1; j < data->TICKET_MAX_SIZE; j++)
				{
					if (data->tickets[index].message[j].accountType == 0 &&
						j <= data->tickets[index].messageCounter)
					{
						data->tickets[index].message[j].accountType =
							accountConst->accountType;
						strcpy(data->tickets[index].message[j].displayName,
							   accountConst->login.displayName);
						strcpy(data->tickets[index].message[j].details,
							   messageEnter);
						break;
					}
				}
				data->tickets[index].messageCounter += 1;
				printf("\n");
				clearStandardInputBuffer();
			}
		}
		else if (data->tickets[index].messageCounter == MESSAGE_SIZE)
		{
			printf("\n");
		}
		puts("*** Ticket closed! ***\n");
		data->tickets[index].ticketStatus = 0;
		if (agentOrCus == 0)
		{
			pauseExecution();
		}
	}
	return;
}

int loadTickets(struct Ticket *tickets, int ticketsSize)
{
	FILE *fp = fopen("tickets.txt", "r");
	int i, j = 0, ticketsLoaded = 0;

	if (fp != NULL)
	{
		for (i = 0; i < ticketsSize; i++)
		{
			fscanf(fp, "%d|%d|%d|%[^|]|%d|",
				   &tickets[i].ticketNum,
				   &tickets[i].customerNum,
				   &tickets[i].ticketStatus,
				   tickets[i].subject,
				   &tickets[i].messageCounter);

			//store message
			while (j < tickets[i].messageCounter)
			{
				fscanf(fp, "%c|%[^|]|%[^|]|",
					   &tickets[i].message[j].accountType,
					   tickets[i].message[j].displayName,
					   tickets[i].message[j].details);
				j++;
			}

			j = 0;
			if (tickets[i].ticketNum != 0)
			{
				ticketsLoaded++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR: Can't open file!\n");
		//ticket problem return 2
		exit(2);
	}
	return ticketsLoaded;
}

int archiveTickets(struct AccountTicketingData *data)
{
	FILE *fp = fopen("tickets_arc.txt", "a");
	int i, j = 0, ticketsArced = 0;

	if (fp != NULL)
	{
		for (i = 0; i < data->TICKET_MAX_SIZE; i++)
		{
			if (data->tickets[i].ticketNum != 0 &&
				data->tickets[i].ticketStatus == 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|",
						data->tickets[i].ticketNum,
						data->tickets[i].customerNum,
						data->tickets[i].ticketStatus,
						data->tickets[i].subject,
						data->tickets[i].messageCounter);

				while (j < data->tickets[i].messageCounter)
				{
					fprintf(fp, "%c|%s|%s|",
							data->tickets[i].message[j].accountType,
							data->tickets[i].message[j].displayName,
							data->tickets[i].message[j].details);
					j++;
				}
				data->tickets[i].ticketNum = 0;
				ticketsArced++;
				fprintf(fp, "\n");
			}
			j = 0;
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		exit(2);
	}
	return ticketsArced;
}

int saveTickets(struct Ticket *tickets, int ticketsSize)
{
	FILE *fp = fopen("tickets.txt", "w");
	int i, j = 0, ticketsCount = 0;

	if (fp != NULL)
	{
		for (i = 0; i < ticketsSize; i++)
		{
			if (tickets[i].ticketNum != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|",
						tickets[i].ticketNum,
						tickets[i].customerNum,
						tickets[i].ticketStatus,
						tickets[i].subject,
						tickets[i].messageCounter);

				while (j < tickets[i].messageCounter)
				{
					fprintf(fp, "%c|%s|%s|",
							tickets[i].message[j].accountType,
							tickets[i].message[j].displayName,
							tickets[i].message[j].details);
					j++;
				}
				fprintf(fp, "\n");
				ticketsCount++;
			}
			j = 0;
		}

		fclose(fp);
		fp = NULL;
	}
	else
	{
		exit(2);
	}
	return ticketsCount;
}