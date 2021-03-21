#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "commonHelpers.h"
#include "account.h"  
#include "accountTicketingUI.h"


//1. funtion with the basic information about te account 
void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}


//2.function that will display the summary record provide by user has as argument the struct account
void displayAccountSummaryRecord(const struct Account DataAcc, const struct Demographic Demo)
{
	int AgentResult = 0;
	if (DataAcc.AccountType == 'A')
	{
		AgentResult = 1;
	}
	printf("%05d %-9s %5d\n", DataAcc.NumCustomer, (AgentResult ? "AGENT" : "CUSTOMER"), Demo.BdayDate);
}

//3. Display the Account details  record with the password partially hidden with * 
void displayAccountDetailRecord(const struct Account account, const struct UserLogin login, const struct Demographic demo)
{
	int AgentResult = 0;
	char hidePassword[MAX_PASSWORD] = { '\0' };
	if (account.AccountType == 'A')
	{
		AgentResult = 1;
	}
	hidethePassword(&login, hidePassword);
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", account.NumCustomer, (AgentResult ? "AGENT" : "CUSTOMER"), demo.BdayDate, demo.HouseIncome, demo.CountryName, login.Name, login.LoginName);
	printf("%8s\n", hidePassword);

	//printf("\n");
}


//4. display the head of Accound detail
void displayAccountDetailRecordHead(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

//5. Funtion to hide the password with * where should have one letter and then on *
//get the original string and do a for only with odd numbers to change to *
void hidethePassword(const struct UserLogin* Password, char* hidePassword)
{
	int a;

	for (a = 0; a < MAX_PASSWORD - 1; a++)
	{
		if (a % 2 != 0)
			hidePassword[a] = 42;
		else
			hidePassword[a] = Password->Password[a];
	}
	//printf("print the pass %s \n", hidePassword);
}


//6. Application startup, Active the menu, if the logged is a Customer the app should display a specify message 
void applicationStartup(struct Account data[], int maxNumberofElements) {
	int index = -1;
	while (index == -1)
	{
		index = menuLogin(data, ACCOUNT_SIZE);
		if (index != -1) {
			if (data[index].AccountType == 'C') {
				printf("\n");
				printf("CUSTOMER: home menu currently unavailable\n\n");
				pauseExecution();
				//printf("\n");
				index = -1;
			}
			else
			{
				printf("\n");
				menuAgent(data, ACCOUNT_SIZE, &data[index]);
				index = -1;
			}
		}

	}

	//printf("index: %d", index);

}

//7. Menu login
//first show the option to login the number to login should be the same register as acc number
// loop to compare the int typed and the data in the array, must return the index of user
int menuLogin(const struct Account ArrayOfDATA[], int MAX_num_of_arguments) {
	int selection = 5, index = -1, flag = 0, cancel = 0;
	printChar('=', 55);
	printf("Account Ticketing System - Login\n");
	printChar('=', 55);
	
	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printChar('-', 46);
	putchar('\n');
	printf("Selection: ");
	selection = getIntFromRange(0, 1);
	while (flag == 0)
	{
		switch (selection)
		{
		case 1:
			printf("\n");
			index = findAccountIndexByAcctNum(0, ArrayOfDATA, ACCOUNT_SIZE, 0);
			flag = 1;
			break;
		case 0:
			printf("\n");

			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			cancel = getCharOption("yYnN");
			printf("\n");
			if (cancel == 'Y' || cancel == 'y')
			{
				printChar('=', 55);
				printf("Account Ticketing System - Terminated\n");
				printChar('=', 55);
				printf("\n");
				exit(0);
			}
			flag = 1;
			//printf("\n");
			break;
		}

	}
	//printf("index function menu: %d\n", index);

	return index;
}

//8.Display the agent main menu
//show the name and the number of the agent on the top
void menuAgent(struct Account Data[], int maxNumberofElements, const struct Account* DataofLoggedUSER) {
	int selection = -1, flag = 0, logged = 1;
	while (logged == 1)
	{
		int Freeindex = emptyIndex(Data, ACCOUNT_SIZE);
		int Changeindex = 0;
		flag = 0;
		printf("AGENT: %s  (%d)\n", DataofLoggedUSER->User.Name, DataofLoggedUSER->NumCustomer);
		printChar('=', 55);
		printf("Account Ticketing System - Login\n");
		printChar('=', 55);
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: summary view\n");
		printf("5) List accounts: detailed view\n");
		printChar('-', 46);
		printf("0) Logout\n");
		putchar('\n');
		printf("Selection: ");
		selection = getIntFromRange(0, 5);
	
		while (flag == 0)
		{
			switch (selection)
			{
			case 1:
				printf("\n");
				GetAccount(Data, Freeindex);
				flag = 1;
				break;
			case 2:
				printf("\n");
				Changeindex = findAccountIndexByAcctNum(0, Data, ACCOUNT_SIZE, 0);
				if (Changeindex != -1)
					menuUpdateOptions(Data, Changeindex);
				flag = 1;
				break;
			case 3:
				printf("\n");
				removeaccount(Data, DataofLoggedUSER->NumCustomer);
				flag = 1;
				break;
			case 4:
				printf("\n");
				displayAllAccountSummaryRecords(Data, ACCOUNT_SIZE);
				flag = 1;
				break;
			case 5:
				printf("\n");
				displayAllAccountDetailRecords(Data, ACCOUNT_SIZE);
				flag = 1;
				break;
			case 0:
				printf("\n### LOGGED OUT ###\n");
				putchar('\n');
				flag = 1;
				logged = 0;
				break;
			}

		}
	}

}

//9. return an integer representing the array index of Account
// search the arg1 in the array of arg2
//if the arg4 =0 will use the arg1 to looking for the user
//if arg4 != 0 will appear a scanf to add a number to looking for
// return -1 if do not found a user or the index of array if found
int findAccountIndexByAcctNum(int NumberTypetoLookingFor, const struct Account ArrayOfAcc[], int maxNumberofElements, int zeroORnot) {
	int accountNumber = 0, a, index = -1;
	if (NumberTypetoLookingFor == 0 && zeroORnot == 0) {
		printf("Enter your account#: ");
		accountNumber = getPositiveInteger();
		for (a = 0; a < maxNumberofElements; a++)
		{
			if (accountNumber == ArrayOfAcc[a].NumCustomer) {
				index = a;
				return index;
			}
		}
		if (index == -1) {
			printf("\n");
			printf("ERROR: Access Denied.\n\n");
			pauseExecution();
			return -1;
		}
	}
	else
	{
		for (a = 0; a < maxNumberofElements; a++)
		{
			if (zeroORnot == ArrayOfAcc[a].NumCustomer) {
				index = a;
				return index;
			}
		}
		if (index == -1) {
			printf("\n");
			printf("ERROR: Access Denied.\n\n");
			pauseExecution();
			return -1;
		}
	}
	return index;
}

//10.display the summary of all valids accounts(which is all than account number is greater than 0
void displayAllAccountSummaryRecords(const struct Account ArrayofAcc[], int maxNumberofElements) {
	int i = 0;
	displayAccountSummaryHeader();
	while (i < maxNumberofElements)
	{
		if (ArrayofAcc[i].NumCustomer != 0)
			displayAccountSummaryRecord(ArrayofAcc[i], ArrayofAcc[i].Demo);
		i++;
	}
	printf("\n");
	pauseExecution();
}

//11. display a detailed view of all valid account records(which is all than account number is greater than 0
void displayAllAccountDetailRecords(const struct Account ArrayofAcc[], int maxNumberofElements) {
	int i = 0;
	displayAccountDetailRecordHead();
	while (i < maxNumberofElements)
	{
		if (ArrayofAcc[i].NumCustomer != 0)
			displayAccountDetailRecord(ArrayofAcc[i], ArrayofAcc[i].User, ArrayofAcc[i].Demo);

		i++;
	}
	printf("\n");
	pauseExecution();
}


//12. Function provided for me
//pause the application
void pauseExecution(void) {
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

//13. loop to find an empyt acocunt to add info
int emptyIndex(const struct Account ArrayofAcc[], int maxNumberofElements) {
	int index = -1, i;
	for (i = 0; (i < maxNumberofElements && index == -1); i++) {
		if (ArrayofAcc[i].NumCustomer == 0) {
			index = i;
			return index;
			printf("index empty: %d ", i);
		}
	}
	if (index == -1)
	{
		printf("ERROR: Account listing is FULL, call ITS Support!\n");
	}
	return index;
}

//14. Menu To update Options
void menuUpdateOptions(struct Account Data[], int ChangeIndex) {
	int selection = 0, done = 1;
	while (done == 1) {
		int flag = 0;
		printf("\n");
		printf("Account: %05d - Update Options\n", Data[ChangeIndex].NumCustomer);
		printChar('-', 46);
		printf("1) Update account type (current value: %c)\n", Data[ChangeIndex].AccountType);
		printf("2) Login\n"
			"3) Demographics\n"
			"0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		while (flag == 0)
		{
			switch (selection)
			{
			case 1:
				printf("\n");
				updateAccount(Data, ChangeIndex);
				flag = 1;
				break;
			case 2:
				printf("\n");
				updateUserLogin(Data, ChangeIndex);
				flag = 1;
				break;
			case 3:
				printf("\n");
				updateDemographic(Data, ChangeIndex);
				flag = 1;
				break;
			case 0:
				done = 0;
				printf("\n");
				flag = 1;
				break;
			}
		}


	}
}

//15.remove account
void removeaccount(struct Account Data[], int currentLogin) {
	int delete = 0, current = 0;
	char final = 'x';
	printf("\n");
	current = findAccountIndexByAcctNum(0, Data, ACCOUNT_SIZE, currentLogin);
	delete = findAccountIndexByAcctNum(0, Data, ACCOUNT_SIZE, 0);
	if (delete == current) {
		printf("\n");
		printf("ERROR: You can't remove your own account!\n");
		printf("\n");
		pauseExecution();
	}
	else
	{
		displayAccountDetailRecordHead();
		displayAccountDetailRecord(Data[delete], Data[delete].User, Data[delete].Demo);
		printf("\n");
		printf("Are you sure you want to remove this record? ([Y]es|[N]o): \n");
		final = getCharOption("YN");
		printf("\n");
		if (final == 'Y' || final == 'y') {
			Data[delete].NumCustomer = 0;
			printf("\n*** Account Removed! ***\n\n");
			pauseExecution();
		}
		else {
			printf("\n*** No changes made! ***\n\n");
			pauseExecution();
		}
	}

}