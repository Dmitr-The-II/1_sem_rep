#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

//functions provide for me

//1.Get the current 4 digit year from the system
int currentYear(void);

//2. Empty the standard input buffer
void clearStandardInputBuffer(void);

//3. get a valid integer from the keyboard, and display an error if an invalid value is entered

int getInteger(void);

//4.get a valid integer and validate if the number if more then 0, and display an erro if an invalid value is entered
int getPositiveInteger(void);

//5.get a valid double and return in the funtion, if an invalid number was typed an erro will be displayed
double getDouble(void);

//6.get a valid double from the  and return in the funtion, if an invalid number was typed an erro will be displayed
double getPositiveDouble(void);

//7. Get the argument 1 and set as a min value to a integer and argument 2 max value to a integer return the number if the input is correct, else show a error messenge
//int getIntFromRange(int lowerNumber, int highestNumber);
int getIntFromRange(int lower_bound, int upper_bound);

//8.Return a single valid char value and receives one argument which is the strig with the valid options to type 
char getCharOption(char* ArrayofvalidArguments);

//9. obtain the user input for a String with the number max and min of chars allowed
void getCString(char* Cstring, int min_NumberChar, int max_NumberChar);



//10. string length
int stringlength(char* string);



void printChar(char simbol, int xTimes);

#endif