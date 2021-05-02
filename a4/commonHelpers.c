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
#include <time.h>
#include <string.h>
#include "commonHelpers.h"

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

// 1. getInteger
int getInteger(void)
{
	int number;
	char term;
	do
	{
		scanf("%d%c", &number, &term);
		if (term == '\n')
		{
			return number;
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (1);
}

// 2. getPositiveInteger
int getPositiveInteger(void)
{
	int positiveNum;
	char term;
	do
	{
		scanf("%d%c", &positiveNum, &term);
		if (term == '\n')
		{
			if (positiveNum > 0)
			{
				return positiveNum;
			}
			else
			{
				printf("ERROR: Value must be a positive integer greater than zero: ");
			}
		}
		else //for accidentally input a char
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (1);
}

// 3,4. getIntFromRange
int getIntFromRange(int minNum, int maxNum)
{
	int number;
	char term;
	do
	{
		term = '\0';
		scanf("%d%c", &number, &term);
		if (term == '\n')
		{
			if (number >= minNum && number <= maxNum)
			{
				return number;
			}
			else
			{
				printf("ERROR: Value must be between %d and %d inclusive: ",
					   minNum, maxNum);
			}
		}
		else
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
		}
	} while (1);
}

// 5. getDouble
double getDouble(void)
{
	double number;
	char term;
	do
	{
		scanf("%lf%c", &number, &term);
		if (term == '\n')
		{
			return number;
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (1);
}

// 6. getPositiveDouble
double getPositiveDouble(void)
{
	double positiveDouble;
	char term;
	do
	{
		scanf("%lf%c", &positiveDouble, &term);
		if (term == '\n')
		{
			if (positiveDouble > 0.0)
			{
				return positiveDouble;
			}
			else
			{
				printf("ERROR: Value must be a positive double floating-point number: ");
			}
		}
		else //for accidentally input a char
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (1);
}

// 7. getCharOption
char getCharOption(const char *validChars)
{
	int i;
	char inputChar, term;

	do
	{
		i = 0;
		scanf(" %c%c", &inputChar, &term); //without space, error output will print twice
		if (term == '\n')
		{
			while (validChars[i] != '\0')
			{
				if (inputChar == validChars[i])
				{
					return inputChar;
				}
				i++;
			}
			printf("ERROR: Character must be one of [%s]: ", validChars);
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", validChars);
		}

	} while (1);
}

// 8,9,10. getCString
void getCString(char cString[], int minNum, int maxNum)
{
	char stringEnter[100];
	int stringLen = 0;
	do
	{
		scanf(" %[^\n]", stringEnter);
		stringLen = strlen(stringEnter);
		if (minNum == maxNum)
		{
			if (stringLen == minNum)
			{
				strcpy(cString, stringEnter);
				break;
			}
			else
			{
				printf("ERROR: String length must be exactly %d chars: ",
					   minNum);
			}
		}
		else
		{
			if (stringLen > maxNum)
			{
				printf("ERROR: String length must be no more than %d chars: ",
					   maxNum);
			}
			else if (stringLen < minNum)
			{
				printf("ERROR: String length must be between %d and %d chars: ",
					   minNum, maxNum);
			}
			else
			{
				strcpy(cString, stringEnter);
				break;
			}
		}
	} while (1);
}
