#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"





struct Account GetAccount(struct Account account[], int FreeIndex)
{
	printf("Account Data: New Record\n");
	printChar('-', 40);
	printf("Enter the account number: ");
	account[FreeIndex].NumCustomer = getInteger();
	printf("\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account[FreeIndex].AccountType = getCharOption("AC");
	printf("\n");
	GetUserLogin(account, FreeIndex);
	GetDemographic(account, FreeIndex);
	printf("*** New account added! ***\n");

	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	char new_Line = 'x';
	scanf("%c", &new_Line);
	printf("\n");
	return account[FreeIndex];
}




struct UserLogin GetUserLogin(struct Account account[], int FreeIndex)
{
	printf("User Login Data Input\n");
	printChar('-', 40);
	printf("Enter user login (%d chars max): ", (MAX_LOGIN_NAME - 1));
	clearStandardInputBuffer();
	getCString(account[FreeIndex].User.LoginName, 1, (MAX_LOGIN_NAME - 1));
	printf("Enter the display name (%d chars max): ", (MAX_DISPLAY_NAME - 1));
	clearStandardInputBuffer();
	getCString(account[FreeIndex].User.Name, 1, (MAX_DISPLAY_NAME - 1));
	printf("Enter the password (must be %d chars in length): ", (MAX_PASSWORD - 1));
	clearStandardInputBuffer();
	getCString(account[FreeIndex].User.Password, (MAX_PASSWORD - 1), (MAX_PASSWORD - 1));
	printf("\n");
	return account[FreeIndex].User;

}


struct Demographic GetDemographic(struct Account account[], int FreeIndex)
{
	printf("Demographic Data Input\n");
	printChar('-', 40);
	clearStandardInputBuffer();
	int MinAge = currentYear() - MAX_AGE, MaxAge = currentYear() - MIN_AGE;
	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	account[FreeIndex].Demo.BdayDate = getIntFromRange(MinAge, MaxAge);
	printf("Enter the household Income: $");
	account[FreeIndex].Demo.HouseIncome = getPositiveDouble();
	printf("Enter the country (%d chars max.): ", (MAX_DISPLAY_COUNTRY - 1));
	getCString(account[FreeIndex].Demo.CountryName, 1, MAX_DISPLAY_COUNTRY);
	printf("\n");
	return account[FreeIndex].Demo;
}



void updateAccount(struct Account ArrayofData[], int changeIndex)
{
	printf("Enter the account type (A=Agent | C=Customer): ");
	ArrayofData[changeIndex].AccountType = getCharOption("AC");
	
}


void updateUserLogin(struct Account ArrayofData[], int changeIndex)
{
	int selection = 0, done = 1;
	while (done == 1)
	{
		int flag = 0;
		printf("\n");
		printf("User Login: %s - Update Options\n", ArrayofData[changeIndex].User.LoginName);
		printChar('-', 46);
		printf("1) Display name (current value: %s)\n", ArrayofData[changeIndex].User.Name);
		printf("2) Password\n"
			"0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);
		printf("\n");
		while (flag == 0)
		{
			switch (selection)
			{
			case 1:
				printf("Enter the display name (%d chars max): ", (MAX_DISPLAY_NAME - 1));
				getCString(ArrayofData[changeIndex].User.Name, 1, (MAX_DISPLAY_NAME - 1));
				flag = 1;
				break;
			case 2:
				printf("Enter the password (must be %d chars in length): ", (MAX_PASSWORD - 1));
				getCString(ArrayofData[changeIndex].User.Password, (MAX_PASSWORD - 1), (MAX_PASSWORD - 1));
				flag = 1;
				break;
			case 0:
				done = 0;
				flag = 1;
				break;
			}

		}
		
	}
}


void updateDemographic(struct Account ArrayofData[], int changeIndex)
{
	int selection = 0, done = 1;
	while (done == 1)
	{
		int flag = 0;
		printf("\n");
		printf("Demographic Update Options\n");
		printChar('-', 46);
		printf("1) Household Income (current value: %.2lf)\n", ArrayofData[changeIndex].Demo.HouseIncome);
		printf("2) Country (current value: %s)\n"
			"0) Done\n", ArrayofData[changeIndex].Demo.CountryName);
		printf("Selection: ");
		selection = getIntFromRange(0, 2);
		printf("\n");
		while (flag == 0)
		{
			switch (selection)
			{
			case 1:
				
				printf("Enter the household Income: $");
				ArrayofData[changeIndex].Demo.HouseIncome = getPositiveDouble();
				flag = 1;
				break;
			case 2:
				
				printf("Enter the country (%d chars max.): ", (MAX_DISPLAY_COUNTRY - 1));
				getCString(ArrayofData[changeIndex].Demo.CountryName, 1, MAX_DISPLAY_COUNTRY);
				flag = 1;
				break;
			case 0:
				
				done = 0;
				flag = 1;
				break;
			}

		}

	}
}
