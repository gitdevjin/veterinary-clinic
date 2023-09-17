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
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    int good = 0;
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(patient + i, fmt);
            good += 1;
        }
    }

    if (good == 0)
    {
        printf("*** No records found ***");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        printf("\n");
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i;
    int good = 0;
    int posn = 0;

    //checking if there is an empty index in the patient array
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            good = 1;
            posn = i; // index where to store the new patient data
            i = 100; // exit the for loop
        }
    }

    if (good)
    {
        patient[posn].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[posn]);
    }
    else
        printf("ERROR: Patient listing is FULL!\n");
    printf("\n");
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int index = -1;
    int inputNumber;
    printf("Enter the patient number: ");
    inputNumber = inputIntPositive();
    printf("\n");
    index = findPatientIndexByPatientNum(inputNumber, patient, max);

    if (index != -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
        printf("ERROR: Patient reocrd not found!\n");
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int inputNumber;
    int index = -1;
    char selection = ' ';
    printf("Enter the patient number: ");
    inputNumber = inputIntPositive();
    printf("\n");
    index = findPatientIndexByPatientNum(inputNumber, patient, max);
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputOneChar("yn");
        if (selection == 'y')
        {
            patient[index].patientNumber = 0;
            strcpy(patient[index].name, "\0");
            strcpy(patient[index].phone.description, "\0");
            strcpy(patient[index].phone.number, "\0");
            printf("Patient record has been removed!\n");
        }

        else if (selection == 'n')
        {
            printf("Operation aborted.\n");
        }

        else
        {
            printf("Invalid intput\n");
        }

    }

    else
    {
        printf("ERROR: Patient record not found!\n");
    }

    printf("\n");
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    struct ClinicData timeOrder = { 0 }; 
    int temp = 0;
    long long int min = 0;
    int posn = 0;
    struct Appointment minData = {0};

    struct Patient appointmentPatient[MAX_APPOINTMENTS] = { {0} };

    timeOrder = *data;
  
    long long int timeIntConversion[MAX_APPOINTMENTS] = { 0 };
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if (timeOrder.appointments[i].date.year != 0)
        {
            timeIntConversion[i] = 10000000 * (timeOrder.appointments[i].date.year - 2000)
                + 100000 * timeOrder.appointments[i].date.month + 1000 * timeOrder.appointments[i].date.day
                + 10 * (timeOrder.appointments[i].time.hour) + (timeOrder.appointments[i].time.min) / 10;
        }
        else
            timeOrder.appointments[i].date.year = 0;
            
    }

    for (posn = 0; posn < MAX_APPOINTMENTS; posn++)
    {
        min = timeIntConversion[posn];
        minData = timeOrder.appointments[posn];
        temp = posn;
        for (i = posn; i < MAX_APPOINTMENTS; i++)
        {
            if (timeIntConversion[i] < min)
            {
                min = timeIntConversion[i];
                temp = i;
                minData = timeOrder.appointments[i];
            }
        }
    
        timeIntConversion[temp] = timeIntConversion[posn];
        timeIntConversion[posn] = min;
       
        timeOrder.appointments[temp] = timeOrder.appointments[posn];
        timeOrder.appointments[posn] = minData;

    }

    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if (timeOrder.appointments[i].patientNumber != 0)
        {
            posn = findPatientIndexByPatientNum(timeOrder.appointments[i].patientNumber, timeOrder.patients, timeOrder.maxPatient);
            appointmentPatient[i] = timeOrder.patients[posn];
        }
    }


    displayScheduleTableHeader(&data->appointments->date, ALL_INCLUDE); 
    
    for (i = 0; i < MAX_APPOINTMENTS; i++) 
    {
        if (timeOrder.appointments[i].patientNumber != 0)
        {
            displayScheduleData(&appointmentPatient[i], &timeOrder.appointments[i], ALL_INCLUDE);
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i;
    struct Date searchDate = { 0 };
  
    inputDate(&searchDate);
    printf("\n");

    struct ClinicData timeOrder = { 0 };
    int temp = 0;
    long long int min = 0;
    int posn = 0;
    struct Appointment minData = { 0 };

    struct Patient appointmentPatient[MAX_APPOINTMENTS] = { {0} };

    timeOrder = *data;

    long long int timeIntConversion[MAX_APPOINTMENTS] = { 0 };
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if (timeOrder.appointments[i].date.year != 0)
        {
            timeIntConversion[i] = 10000000 * (timeOrder.appointments[i].date.year - 2000)
                + 100000 * timeOrder.appointments[i].date.month + 1000 * timeOrder.appointments[i].date.day
                + 10 * (timeOrder.appointments[i].time.hour) + (timeOrder.appointments[i].time.min) / 10;
        }
        else
            timeOrder.appointments[i].date.year = 0;

    }

    for (posn = 0; posn < MAX_APPOINTMENTS; posn++)
    {
        min = timeIntConversion[posn];
        minData = timeOrder.appointments[posn];
        temp = posn;
        for (i = posn; i < MAX_APPOINTMENTS; i++)
        {
            if (timeIntConversion[i] < min)
            {
                min = timeIntConversion[i];
                temp = i;
                minData = timeOrder.appointments[i];
            }
        }

        timeIntConversion[temp] = timeIntConversion[posn];
        timeIntConversion[posn] = min;

        timeOrder.appointments[temp] = timeOrder.appointments[posn];
        timeOrder.appointments[posn] = minData;

    }

    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if (timeOrder.appointments[i].patientNumber != 0)
        {
            posn = findPatientIndexByPatientNum(timeOrder.appointments[i].patientNumber, timeOrder.patients, timeOrder.maxPatient);
            appointmentPatient[i] = timeOrder.patients[posn];
        }

    }

    displayScheduleTableHeader(&searchDate, DATA_SPECIFIC);

    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if ( (timeOrder.appointments[i].patientNumber != 0)
            && (searchDate.year == data->appointments[i].date.year)
            && (searchDate.month == data->appointments[i].date.month)
            && (searchDate.day == data->appointments[i].date.day))
        {
            displayScheduleData(&appointmentPatient[i], &timeOrder.appointments[i], DATA_SPECIFIC);
        }
    }
    printf("\n");

}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointment, struct Patient* patients, int maxPatient)
{
    
    int i;
    int good = 0;
    int booked = 0;
    int posn = 0;
    int timeConversion;
    struct Appointment new = { 0 };
   
    printf("Patient Number: ");
    new.patientNumber = inputIntPositive();
    
    for (i = 0; i < maxPatient; i++)
    {
        if (new.patientNumber == patients[i].patientNumber)
        {
                good = 1;
        }
    }

    if (good == 0)
    {
        printf("ERROR : Patient record not found!\n");
        return;
    }

    inputDate(&new.date);

    printf("Hour (0-23)  : ");
    new.time.hour = inputIntRange(0, 23);
    printf("Minute (0-59): ");
    new.time.min = inputIntRange(0, 59);
    printf("\n");
    
    while (good == 1)
    {
        timeConversion = (new.time.hour * 100) + (new.time.min);
        
        if ( (timeConversion >= OPERATION_START) && (timeConversion <= OPERATION_END) && (new.time.min % APPOINTMENT_INTERVAL == 0) )
        {
            booked = 0;
            for (i = 0; i < MAX_APPOINTMENTS; i++)
            {
                if ( (new.time.hour == appointments[i].time.hour)
                    && (new.time.min == appointments[i].time.min) 
                    && (new.date.year == appointments[i].date.year)
                    && (new.date.month == appointments[i].date.month)
                    && (new.date.day == appointments[i].date.day) )
                {
                    booked = 1;
                    i = MAX_APPOINTMENTS;
                }
            }

            if (booked == 0)
            {
                for (i = 0; appointments[i].date.year != 0 && i < maxAppointment; i++)
                {
                    if (appointments[i].patientNumber == 0);
                    posn = i;
                    i = maxAppointment;
                }

                appointments[posn].patientNumber = new.patientNumber;
                appointments[posn].date.year = new.date.year;
                appointments[posn].date.month = new.date.month;
                appointments[posn].date.day = new.date.day;
                appointments[posn].time.hour = new.time.hour;
                appointments[posn].time.min = new.time.min;
                printf("\n");
                printf("*** Appointment scheduled! ***\n");
                good = 0;
            }

            else
            {
                printf("ERROR: Appointment timeslot is not available!\n");
                printf("\n");
                inputDate(&new.date);
                printf("Hour (0-23)  : ");
                new.time.hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                new.time.min = inputIntRange(0, 59);
            } 
        }
        else
        { 
                printf("ERROR: Time must be between %d:%02d and %d:%02d in %d minute intervals.\n",
                    OPERATION_START / 100, OPERATION_START % 100, OPERATION_END / 100, OPERATION_END % 100, APPOINTMENT_INTERVAL);
                printf("\n");
                printf("Hour (0-23)  : ");
                new.time.hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                new.time.min = inputIntRange(0, 59);
        }
    }
    printf("\n");
}



// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointment, struct Patient* patients, int maxPatient)
{
    int i = 0;
    int good = 0;
    int found = 0;
    int posn = 0;
    int posn2 = 0;
    char selection;
    struct Appointment input = { 0 };

    printf("Patient Number: ");
    input.patientNumber = inputIntPositive();
    for (i = 0; i < maxPatient; i++)
    {
        if (input.patientNumber == patients[i].patientNumber)
        {
            good = 1;
            posn = i;
        }
    }

    if (good == 0)
    {
        printf("ERROR: Patient record not found!\n");
        printf("\n");
        return;
    }

    inputDate(&input.date);
    printf("\n");
    while (good)
    {
        for (i = 0; i < maxAppointment; i++)
        {
            if (input.patientNumber == appointments[i].patientNumber && input.date.year == appointments[i].date.year
                && input.date.month == appointments[i].date.month && input.date.day == appointments[i].date.day)
            {
                found = 1;
                posn2 = i;
            }
        }

        if (found)
        {
            displayPatientData(&patients[posn], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            scanf("%c%*c", &selection);
            printf("\n");
            if (selection == 'y')
            {
                appointments[posn2].patientNumber = 0;
                appointments[posn2].date.year = 0;
                appointments[posn2].date.month = 0;
                appointments[posn2].date.day = 0;
                good = 0;
                printf("Appointment record has been removed!\n");
            }
            else
                return;
        }
    }
    printf("\n");
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int index = -1;
    int inputNumber;
    printf("Search by patient number: ");
    inputNumber = inputIntPositive();
    printf("\n");
    index = findPatientIndexByPatientNum(inputNumber, patient, max);
    if (index != -1)
        displayPatientData(&patient[index], FMT_FORM);
    else
    {
        printf("*** No records found ***\n");
    }

    printf("\n");
    suspend();
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i = 0;
    int good = 0;
    char inputNumber[PHONE_LEN + 1];


    printf("Search by phone number: ");
    inputPhoneString(inputNumber, PHONE_LEN, PHONE_LEN);
    printf("\n");

    printf("Pat.# Name            Phone#\n");
    printf("----- --------------- --------------------\n");

    //test
    //displayFormattedPhone(inputNumber);
    //printf("\n");
    //printf("%s\n", patient[i].phone.number);

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, inputNumber) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            good += 1;
        }
    }

    if (good == 0)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }

    printf("\n");
    suspend();
}
// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int high = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > high)
        {
            high = patient[i].patientNumber;
        }
    }
    return high + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;
    int posn = -1;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            posn = i;
        }
    }
    return posn;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
    printf("*** New patient record added ***\n");

}


// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int selection;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    printf("\n");

    if (selection == 1)
    {
        strcpy(phone->description, "CELL");
        printf("Contact: CELL\n");
        printf("Number : ");
        inputPhoneString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }

    else if (selection == 2)
    {
        strcpy(phone->description, "HOME");
        printf("Contact: HOME\n");
        printf("Number : ");
        inputPhoneString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }
    else if (selection == 3)
    {
        strcpy(phone->description, "WORK");
        printf("Contact: WORK\n");
        printf("Number : ");
        inputPhoneString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }
    else
    {
        strcpy(phone->description, "TBD");
        strcpy(phone->number, " ");
    }

}
// MS3 inputDate
void inputDate(struct Date* date)
{

    printf("Year        : ");
    date->year = inputIntPositive();
    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);
    
    if ((date->year % 4) == 0)
    {
        if ((date->month) == 2)
        {
            printf("Day (1-29)  : ");
            date->day = inputIntRange(1, 29);
        }
        else if ((date->month) == 1 || (date->month) == 3 || (date->month) == 5 || (date->month) == 7 || (date->month) == 8 ||
            (date->month) == 10 || (date->month) == 12)
        {
            printf("Day (1-31)  : ");
            date->day = inputIntRange(1, 31);
        }
        else
        {
            printf("Day (1-30)  : ");
            date->day = inputIntRange(1, 30);
        }
    }

    else
        if ((date->month) == 2)
        {
            printf("Day (1-28)  : ");
            date->day = inputIntRange(1, 28);
        }
        else if ((date->month) == 1 || (date->month) == 3 || (date->month) == 5 || (date->month) == 7 || (date->month) == 8 ||
            (date->month) == 10 || (date->month) == 12)
        {
            printf("Day (1-31)  : ");
            date->day = inputIntRange(1, 31);
        }
        else
        {
            printf("Day (1-30)  : ");
            date->day = inputIntRange(1, 30);
        }
    
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) 
{
    int i;
    int count = 0;
    int good = 1;
    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        for (i = 0; i < max && good != EOF; i++)
        {
            good = fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]",
                &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
            //printf("Read: %d, %s, %s, %s,\n", patients[i].patientNumber,
               // patients[i].name, patients[i].phone.description, patients[i].phone.number);
            count++;
        }
        fclose(fp);
    }
    return count;
}

// "%d|%s[^|]|%s[^|]|%s[^\n]"
//"%d|%15[^|]|%5[^|]|%11[^\n]"

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i;
    int count = 0;
    int good = 1;
    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        for (i = 0; i < max && good != EOF; i++)
        {
            good = fscanf(fp, "%d,%d,%d,%d,%d,%d%*c",
                &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day,
                &appoints[i].time.hour, &appoints[i].time.min);
            count++;
        }
        fclose(fp);
    }
    
    return count - 1;
}