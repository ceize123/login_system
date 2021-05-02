/*
	==================================================
	Assignment #2 Milestone #4:
	==================================================
	Name   : Yi-Tso Kuo
	ID     : 166577197
	Email  : ytkuo@myseneca.ca
	Section: NHH
*/

//
// Your identification information commented header goes here...
//
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
// Header file contents goes here...

int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
int getIntFromRange(int, int);
double getDouble(void);
double getPositiveDouble(void);
char getCharOption(const char *);
void getCString(char *, int, int);

#endif // !COMMON_HELPERS_H_