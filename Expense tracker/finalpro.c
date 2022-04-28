#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 80
#define MAX_MONTHS 12
#define CURRENT_YEAR 2020
#define YEAR_BACK 2019
#define INDEX 1
#define FILENAME "test.txt"
typedef struct {                      // structer for basic information
    int type_of_transaction;
    char description[MAX];
    float amount_of_money;
    char date[MAX];

}data;
int getinformation(data* initial, int Type_of_transaction, int index, char* months[MAX_MONTHS]);     //function used for getting and storeing information  
void print_record(data* initial, int INDEX1);       //function used for printing records 
int  save_records(data* initial);          //function used for saveing record in the file 
int read_records(data* initial);           //function used for reading from the file
void print_all(data* initial, int INDEX1);      //function used for printing final records 
int date(char* DATE, char* months[MAX_MONTHS]);     //function for date validation 
int compare(const void* s1, const void* s2);        // sort by date
int compare2(const void* s1, const void* s2);       // sort by Description
int main() {
    data initial[MAX];
    int expression = 0;          //variable for switch case
    int return1 = 0;            //return value used for save_records function 
    int return2 = 0;            //return value used for read_records function
    int return3 = 0;            //return value for removeing file
    int index = 0;
    const int width = 40;
    char ans;
    int Type_of_transaction;
    char* months[MAX_MONTHS] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December" };

    while (expression != 9) {
        printf("\n");
        printf("1. INITIAZLIE (CLEAR ALL RECORDS)\n");
        printf("2. SAVE FINANCIAL RECORDS TO FILE\n");
        printf("3. READ FINANCIAL RECORDS FROM FILE\n");
        printf("4. ADD MONEY \n");
        printf("5. SPEND MONEY \n");
        printf("6. PRINT REPORT\n");
        printf("7. PRINT REPORT BY DATE\n");
        printf("8. PRINT REPORT BY DESCRIPTION\n");
        printf("9. EXIT\n");
        printf("SELECT ONE OF THE OPTIONS GIVEN :");
        scanf("%d", &expression);
        printf("\n");
        switch (expression)
        {

        case 1:

            memset(initial, 0, 20); // clear all records array by setting 0 for all element 
            index = 0;
            printf("ALL RECORDS SET TO ZERO(0)\n");
            printf("DO YOU WANT TO DELETE THE FILE ?\nPRESS YESS(Y) OR NO(N) :");
            scanf(" %c", &ans);

            if ((toupper(ans) != 'Y' && toupper(ans) != 'N'))// read input & check answer is N or Y 
            {
                printf("INCORRECT ANSWER, TRY AGAIN\n");                // for Incorrect answer display message 
            }
            else if (toupper(ans) == 'Y')
            {
                return3 = remove(FILENAME);

                if (return3 == 0) {
                    printf("FILE DELETED SUCCESSFULLY");
                }
                else {
                    printf("ERROR: UNABLE TO DELTE FILE");
                }
            }
            else {
                printf("FILE NOT DELETED,ALL RECORDS SET TO ZERO(0)");
                printf("\n");
            }



            break;

        case 2:
            return1 = save_records(initial);         //return value is 1 or 0
            if (return1 == 0) {// if return1 =0 then the information stored success, else fails
                printf("THE INFORMATION WAS SUCCESSFULLY STORED IN THE FILE \n");
            }
            else {

                printf("ERROR: THE INFORMATION WAS NOT STORED IN THE FILE \n");

            }


            break;

        case 3:
            return2 = read_records(initial);   //return value is 1 or 0
            if (return2 == 0) // if return2 =0 then the information stored success, else fails
            {
                print_record(initial, index);   //  function to print all the information from file except net value
            }
            else
            {
                printf("UNABLE TO READ INFORMATION \n");
            }
            break;
        case 4:
            Type_of_transaction = 1;  // set value to for income 
            printf("RECORD %d\n", index + 1);
            printf("%*s : INCOME \n", -width, "TYPE OF TRANSACTION");
            index = getinformation(initial, Type_of_transaction, index, months); // store information and return index value
            break;
        case 5:
            Type_of_transaction = 0;  // set value to for expense
            printf("RECORD %d\n", index + 1);
            printf("%*s : EXPENSE \n", -width, "TYPE OF TRANSACTION");
            index = getinformation(initial, Type_of_transaction, index, months); // store information and return index value                     
            break;

        case 6:
            print_all(initial, index);  //function to print all the details from file
            break;

        case 7:
            qsort(initial, index, sizeof(data), compare); // sort by description of transaction
            print_all(initial, index);

            break;

        case 8:
            qsort(initial, index, sizeof(data), compare2); // sort by description of transaction
            print_all(initial, index); //function to print all the details from file

            break;
        case 9:
            printf("THE PROGRAM HAS ENDED ");       // To end the program
            break;

        default:

            printf("ERROR: YOU CANNOT SELECT OUT OF THE OPTIONS");// default statements
        }

    }


}
int date(char* DATE, char* months[MAX_MONTHS]) {
    int day, mon, year, is_leap = 0, is_valid = 1;


    sscanf(DATE, "%d/%d/%d", &day, &mon, &year);

    if (year >= YEAR_BACK && year <= CURRENT_YEAR)
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if (mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if (day > 28)
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months 
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if (day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    if (is_valid)
    {
        printf("DATE IS VALID .\n");
        return 0;
    }

    else
    {
        printf("DATE IS INVALID KINDLY ENTER BETWEEN YEAR 2019-2020.\n");
        return -1;
    }







}
int getinformation(data* initial, int Type_of_transaction, int index, char* months[MAX_MONTHS]) {
    int return1;
    int i = index;

    initial[i].type_of_transaction = Type_of_transaction;
    const int min_amount = 0;
    const int width = 40;


    do

    {
        printf("%*s : ", -width, "DESCRIPTION OF TRANSACTION");         //To store descripiton of transaction
        scanf(" %[^\n]", &initial[i].description);
        if (!(strlen(initial[i].description) < MAX)) {
            printf("INVALID ENTRY [MAX. 80 CHARACTERS]\n");
            initial[i].description[0] = NULL;
        }
    } while (initial[i].description[0] == NULL);
    int num = 0;
    do
    {
        printf("%*s : ", -width, "AMOUNT OF MONEY ");
        if (scanf("%f", &initial[i].amount_of_money) != 1)           //To store amount of money
        {
            char ch = getchar();
            while (ch != '\n')
                ch = getchar();
            num++;
            printf("INVALID ENTRY MINIMUM AMOUNT REQUIRED [%d]\n", num);
            initial[i].amount_of_money = 0;
        }
        else
        {
            if (initial[i].amount_of_money < min_amount)
            {
                num++;
                printf("INVALID ENTRY MINIMUM AMOUNT REQUIRED [%d]\n", num);
                initial[i].amount_of_money = 0;

            }
        }

    } while (initial[i].amount_of_money == 0);

    do
    {
        printf("%*s : ", -width, "DATE OF TRANSACTION [dd/mm/yyyy]");       //To store date of transaction

        scanf(" %[^\n]", &initial[i].date);
        return1 = date(initial[i].date, months); // return1 0 means correct, return1 -1 means incorrect

    } while (return1 != 0); // if ret is not 0 continue the loop

       //To display previous entered record 

    printf("\n");
    printf("ENTERED RECORD %d \n", i + 1);
    if (Type_of_transaction == 1)
    {
        printf("TYPE OF TRANSACTION :INCOME\n");
    }
    else {
        printf("TYPE OF TRANSACTION :EXPENSE\n");
    }
    printf("DESCRIPTION :%s\n", initial[i].description);
    printf("ENTERED AMOUNT :%.2f\n", initial[i].amount_of_money);
    printf("DATE :%s\n", initial[i].date);


    i++;

    return i;      // return value is index
}
void print_record(data* initial, int INDEX1) {

    printf("\n");
    printf("ENTERED RECORD \n");
    size_t n = sizeof(initial) / sizeof(initial);
    float tot_income = 0; // calculate total income
    float tot_expense = 0; // calculate total expense
    printf(" |%*s| |%*s| |%*s| |%*s|\n", -15, "DATE", -30, "DESCRIPTION OF TRANSACTION", -15, "INCOME", -15, "EXPENSE");
    if (INDEX1 > 0) {
        for (size_t i = 0; i < INDEX1; i++)
        {

            printf(" | %*s | ", -13, initial[i].date);
            printf("| %*s | ", -28, initial[i].description);
            if (initial[i].type_of_transaction == 1) {
                printf("| %*.2f | ", 13, initial[i].amount_of_money);
                tot_income += initial[i].amount_of_money;
            }
            else if (initial[i].type_of_transaction == 0)
            {
                printf("| %*.2f |", 31, initial[i].amount_of_money);
                tot_expense += initial[i].amount_of_money;
            }
            printf("\n");

        }
        printf("\n");
        printf(" | %*s ", -47, "Total ");
        printf(" |%*.2f | |%*.2f |", 14, tot_income, 14, tot_expense);

        printf("\n");
    }
    else {
        printf(" | %*s |\n", -82, "THERE IS NO DETAILS TO DISPLAY");
    }
}




int read_records(data* initial) {               //function for read from file 
    int count;
    FILE* my_file;
    data temp;
    if ((my_file = fopen(FILENAME, "rb")) == NULL) {
        printf("ERROR! OPENING FILE");
        return 1;                                   // return 0 means correct, return1 1 means incorrect
    }
    else
    {
        count = 0;
        while (fread(&temp, sizeof(temp), INDEX, my_file) == 1)
        {
            initial[count] = temp;
            count++;
        }

        fclose(my_file);
        return 0;
    }
}

int  save_records(data* initial) {                  //function for saveing to file
    int count;
    FILE* my_file;
    data temp;
    if ((my_file = fopen(FILENAME, "wb")) == NULL) {
        printf("ERROR! OPENING FIL");
        return 1;                                // return 0 means correct, return1 1 means incorrect
    }
    else
    {
        size_t n = sizeof(initial) / sizeof(initial);
        for (count = 0; count < n; count++)

        {
            temp = initial[count];
            fwrite(&temp, sizeof(temp), INDEX, my_file);
        }
        fclose(my_file);
        return 0;
    }


}
void print_all(data* initial, int INDEX1) {                //function to print all records plus net value

    printf("\n");

    size_t n = sizeof(initial) / sizeof(initial);
    float netamount = 0;// calculate net value
    float tot_income = 0; // calculate total income
    float tot_expense = 0; // calculate total expense
    printf(" |%*s| |%*s| |%*s| |%*s|\n", -15, "DATE", -30, "DESCRIPTION OF TRANSACTION", -15, "INCOME", -15, "EXPENSE");
    if (INDEX1 > 0) {
        for (size_t i = 0; i < INDEX1; i++)
        {
            printf("ENTERED RECORDS %d\n", INDEX1 + 1);
            printf(" | %*s | ", -13, initial[i].date);
            printf("| %*s | ", -28, initial[i].description);
            if (initial[i].type_of_transaction == 1) {
                printf("| %*.2f | ", 13, initial[i].amount_of_money);
                tot_income += initial[i].amount_of_money;
            }
            else if (initial[i].type_of_transaction == 0)
            {
                printf("| %*.2f |", 31, initial[i].amount_of_money);
                tot_expense += initial[i].amount_of_money;
            }
            printf("\n");
            netamount = tot_income - tot_expense;
        }
        printf("\n");
        printf(" | %*s ", -47, "Total ");
        printf(" |%*.2f | |%*.2f |", 14, tot_income, 14, tot_expense);
        printf("\n");
        printf("-------------------------------------\n");
        printf(" | NET AMOUNT: ");
        printf(" %*.2f  ", 13, netamount);
        printf("\n");
        if (netamount < 0) {
            printf(" YOU SPEND MORE THAN YOU EARN \n ");
        }
        else if (netamount == 0) {

            printf(" YOU SPENT ALL OF YOUR MONEY, YOU HAVE NO MONEY LEFT \n ");
        }
        else {
            printf(" YOU SPEND YOUR MONEY WISELY \n ");
        }
    }
    else {
        printf(" | %*s |\n", -82, "THERE IS NO DETAILS TO DISPLAY");
    }
}
int compare(const void* s1, const void* s2)
{
    data* e1 = (data*)s1;
    data* e2 = (data*)s2;
    int gendercompare = strcmp(e1->date, e2->date);

    return gendercompare;
}

int compare2(const void* s1, const void* s2)
{
    data* e1 = (data*)s1;
    data* e2 = (data*)s2;
    int gendercompare = strcmp(e1->description, e2->description);

    return gendercompare;
}
