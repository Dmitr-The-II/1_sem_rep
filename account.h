#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#define _CRT_SECURE_NO_WARNINGS

#define MAX_PASSWORD 9
#define MAX_LOGIN_NAME 11
#define MAX_DISPLAY_NAME 31
#define MAX_DISPLAY_COUNTRY 31
#define MAX_AGE 110
#define MIN_AGE 18
#define ACCOUNT_SIZE 50
#define INIT_DATA_SIZE 5

struct Demographic
{
	int BdayDate;
	double HouseIncome;
	char CountryName[MAX_DISPLAY_COUNTRY];
};

struct UserLogin
{
	char Name[MAX_DISPLAY_NAME];
	char LoginName[MAX_LOGIN_NAME];
	char Password[MAX_PASSWORD];
};

struct Account
{
	int NumCustomer;
	char AccountType;
	struct UserLogin User;
	struct Demographic Demo;
};



struct Account GetAccount(struct Account account[], int FreeIndex);


struct UserLogin GetUserLogin(struct Account account[], int FreeIndex);


struct Demographic GetDemographic(struct Account account[], int FreeIndex);



void updateAccount(struct Account ArrayofData[], int changeIndex);


void updateUserLogin(struct Account ArrayofData[], int changeIndex);

void updateDemographic(struct Account ArrayofData[], int changeIndex);








#endif
