#ifndef ACCOUNT_TICKETING_H_
#define ACCOUNT_TICKETING_H_


void displayAccountSummaryHeader(void);


void displayAccountSummaryRecord(const struct Account DataAcc, const struct Demographic Demo);


void displayAccountDetailRecord(const struct Account account, const struct UserLogin login, const struct Demographic demo);


void displayAccountDetailRecordHead(void);


void hidethePassword(const struct UserLogin* Password, char* hidePassword);


void applicationStartup(struct Account data[], int maxNumberofElements);


int menuLogin(const struct Account ArrayOfDATA[], int MAX_num_of_arguments);


void menuAgent(struct Account Data[], int maxNumberofElements, const struct Account* DataofLoggedUSER);


int findAccountIndexByAcctNum(int NumberTypetoLookingFor, const struct Account ArrayOfAcc[], int maxNumberofElements, int zeroORnot);


void displayAllAccountSummaryRecords(const struct Account ArrayofAcc[], int maxNumberofElements);


void displayAllAccountDetailRecords(const struct Account ArrayofAcc[], int maxNumberofElements);


void pauseExecution(void);


int emptyIndex(const struct Account ArrayofAcc[], int maxNumberofElements);


void menuUpdateOptions(struct Account Data[], int ChangeIndex);

void removeaccount(struct Account Data[], int currentLogin);

#endif