/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Hyunjin Shin
Student ID#: 168043214
Email      : hshin41@myseneca.ca
Section    : NAA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

// 1. inputInt
int inputInt(void)
{
    int nread = -1;
    int result = 0;
    int done = 1;
    do {
        nread = scanf("%d", &result);
        if (getchar() != '\n')
        {
            printf("Error! Input a whole number: "); // when user inputs a float number
            clearInputBuffer();
        }

        else if (nread != 1)
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }

        else
        {
            done = 0;
        }
    } while (done);

    return result;
}

// 2. inputIntPositive
int inputIntPositive(void)
{
    int result = 0;
    int done = 1;
    do {
        result = inputInt();
        if (result < 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            done = 0;
        }

    } while (done);
    return result;
}

// 3. inputIntRange
int inputIntRange(int min, int max)
{
    int result = 0;
    int done = 1;
    do {
        result = inputInt();

        if (result < min || result > max)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }

        else
        {
            done = 0;
        }
    } while (done);
    return result;
}

// 4. inputCharOption
char inputCharOption(char* string)
{
    char result;
    int found = 1;
    int i = 0;
    int posn = 0; // position of null terminator

    // finding the position of a null terminator
    while (string[i] != '\0')
    {
        i++;
        posn = i;
    }

    // getting input from user and check if it matches the give string
    do {
        scanf("%c", &result);
        clearInputBuffer();
        for (i = 0; i < posn + 1; i++)
        {
            if (result == string[i])
            {
                posn = i;
                found = 0; // found the character maching that of the string
            }
        }

        if (found != 0)
        {
            printf("ERROR: Character must be one of [%s]:", string);
        }
    } while (found);

    // copy the matched character into a variable to return it
    result = string[posn];

    return result;
}

// 5. inputCString
void inputCString(char* string, int min, int max)
{
    int done = 1;
    char ch = 'X';
    int i = 0;
    int posn = 0; //position of '\0'

    char temp[MAX_STRING] = "\0";

    while (done)
    {
        // getting input string and store it into temp string
        i = 0;
        do {
            ch = getchar();
            temp[i] = ch;
            posn = i;// to find the position of null terminator;
            i++;
        } while (ch != '\n');
        temp[posn] = '\0'; // to insert null terminator at the end of the string.


        //test to see if it is properly stored
        /*printf("i = %d, posn = %d", i, posn);
        for (i = 0; i <= posn; i++)
        {
            printf("%c", temp[i]);
        }*/


        // filtering invaild input when min == max
        if (min == max)
        {
            if (posn > max || posn < min)
            {
                printf("ERROR: String length must be exactly %d chars: ", max);
            }

            else
            {
                for (i = 0; i < posn + 1; i++)
                {
                    string[i] = temp[i];
                }
                done = 0;
            }
        }
        // filtering invaild input when min != max
        else
        {
            if (posn > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }

            else if (posn < min)
            {
                printf("ERROR: String length must be between %d and %d: ", min, max);
            }

            else
            {
                for (i = 0; i < posn + 1; i++)
                {
                    string[i] = temp[i];
                }
                done = 0;
            }
        }
    }
    return;
}

// 6. displayFormattedPhone
void displayFormattedPhone(const char phoneNumber[])
{
    int i = 0;
    int bad = 0;
    int posn = 0;

    // figuring out the size of phone number
    while (phoneNumber != NULL && phoneNumber[i] != '\0')
    {
        i++;
        posn = i; // index of null terminator
    }

    // check if it has the valid size and is not NULL pointer
    if (posn != 10 || phoneNumber == NULL)
    {
        printf("(___)___-____");
    }

    else
    {
        for (i = 0; i < 10; i++)
        {
            if (phoneNumber[i] > 57 || phoneNumber[i] < 48) // checking if they are 0~9 with ASKII CODE 
            {
                printf("(___)___-____");
                i = 100; // escape the for loop
                bad = 1;
            }
        }

        if (bad == 0)
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3],
                phoneNumber[4], phoneNumber[5], phoneNumber[6], phoneNumber[7], phoneNumber[8], phoneNumber[9]);
        }
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// 7. inputOneChar -- getting only one char.
char inputOneChar(char* string)
{
    char result;
    int ch;
    int found = 1;
    int i = 0;
    int posn = 0; // position of null terminator

    // finding the position of a null terminator
    while (string[i] != '\0')
    {
        i++;
        posn = i;
    }

    // getting input from user and check if it matches the give string
    do {
        scanf("%c", &result);
        while((ch = getchar()) != '\n') // to check if the input is more than one character
        {
            printf("ERROR: Character must be one of [%s]: ", string);
            clearInputBuffer();
            scanf("%c", &result);
        }

        for (i = 0; i < posn + 1; i++)
        {
            if (result == string[i])
            {
                posn = i;
                found = 0; // found the character maching that of the string
            }
        }

        if (found != 0)
        {
            printf("ERROR: Character must be one of [%s]:", string);
        }
    } while (found);

    // copy the matched character into a variable to return it
    result = string[posn];

    return result;
}


// 8. inputPhoneString
void inputPhoneString(char* string, int min, int max)
{
    int done = 1;
    char ch = 'X';
    int i = 0;
    int posn = 0; //position of '\0'

    char temp[MAX_STRING] = "\0";

    while (done)
    {
        // getting input string and store it into temp string
        i = 0;
        do {
            ch = getchar();
            temp[i] = ch;
            posn = i;// to find the position of null terminator;
            i++;
        } while (ch != '\n');
        temp[posn] = '\0'; // to insert null terminator at the end of the string.

        // filtering invaild input when min == max
        if (min == max)
        {
            if (posn > max || posn < min)
            {
                printf("Invalid %d-digit number! Number: ", max);
            }

            else
            {
                for (i = 0; i < posn + 1; i++)
                {
                    string[i] = temp[i];
                }
                done = 0;
            }
        }
        // filtering invaild input when min != max
        else
        {
            if (posn > max)
            {
                printf("Invalid %d-digit number! Number: ", max);
            }

            else if (posn < min)
            {
                printf("Invalid %d-digit number! Number: ", max);
            }

            else
            {
                for (i = 0; i < posn + 1; i++)
                {
                    string[i] = temp[i];
                }
                done = 0;
            }
        }
    }
    return;
}

