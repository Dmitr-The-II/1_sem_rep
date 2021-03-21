#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "commonHelpers.h"
#include "account.h"  
#include "accountTicketingUI.h"



int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}


void clearStandardInputBuffer(void)
{
	while (getchar() != '\n');
}



int getInteger(void)
{
	int Value;
	char new_line;
	scanf("%d%c", &Value, &new_line);
	while (new_line != '\n')
	{
		printf("ERROR: Value must be an integer: ");
		clearStandardInputBuffer();
		scanf("%d%c", &Value, &new_line);
	}
	return Value;
}



int getPositiveInteger(void)
{
	int a = 0;
	while (a <= 0)
	{
		a = getInteger();
		if (a < 0)
			printf("ERROR: Value must be a positive integer greater than zero: ");
	}
	return a;
}



double getDouble(void)
{
	double Value;
	char new_line;
	scanf("%lf%c", &Value, &new_line);
	while (new_line != '\n')
	{
		printf("ERROR: Value must be a double floating-point number: ");
		clearStandardInputBuffer();
		scanf("%lf%c", &Value, &new_line);
	}
	return Value;
}

double getPositiveDouble(void)
{
	double a = 0;
	while (a <= 0)
	{
		a = getDouble();
		if (a <= 0)
			printf("ERROR: Value must be a positive double floating-point number: ");
	}
	return a;
}


int getIntFromRange(int lower_bound, int upper_bound)
{
	int value, flag;
	flag = 1;

	while (flag == 1) {
		value = getInteger();
		if (value < lower_bound || value > upper_bound)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
		}
		else if (value >= lower_bound || value <= upper_bound) {

			flag = 0;
		}
	}
	return value;
}

 
char getCharOption(char* ArrayofvalidArgument)
{
	char letter[10], new_line;
	int a = 0, valid = 0, length = 0;
	while (valid == 0)
	{
		scanf("%[^'\n']s%1c", letter, &new_line);
		length = stringlength(letter);
		if (length == 1)
		{
			for (a = 0; ArrayofvalidArgument[a] != '\0'; a++)
			{
				if (letter[0] == ArrayofvalidArgument[a]) {
					valid = 1;
					return letter[0];
				}
			}
			printf("ERROR: Character must be one of [%s]: ", ArrayofvalidArgument);
		}
		else
			printf("ERROR: Character must be one of [%s]: ", ArrayofvalidArgument);
		clearStandardInputBuffer();
	}
	return letter[0];
}

void getCString(char* Cstring, int min_NumberChar, int max_NumberChar)
{
	int valid = 0, length = 0;
	char new_line = 'x';
	scanf("%[^\n]s%c", Cstring, &new_line);
	length = stringlength(Cstring);
	while (valid == 0)
	{
		if ((length < min_NumberChar || length > max_NumberChar) && length != 0)
		{
			if (min_NumberChar == max_NumberChar)
				printf("ERROR: String length must be exactly %d chars: ", max_NumberChar);
			else
			{
				if (length > max_NumberChar)
					printf("ERROR: String length must be no more than %d chars: ", max_NumberChar);
				if (length < min_NumberChar)
					printf("ERROR: String length must be between %d and %d chars: ", min_NumberChar, max_NumberChar);
			}
			clearStandardInputBuffer();
			scanf("%[^\n]s%c", Cstring, &new_line);
			length = stringlength(Cstring);
		}
		else
			valid = 1;
	}
	
}




int stringlength(char* string) {
	int length = 0, a;

	for (a = 0; string[a] != '\0'; a++)
		length = a + 1;

	return length;
}


void printChar(char simbol, int xTimes) {
	int a;
	for (a = 0; a < xTimes; a++)
		printf("%c", simbol);
	printf("\n");
}