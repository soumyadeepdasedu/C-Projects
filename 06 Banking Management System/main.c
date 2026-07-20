#include <stdio.h>
#include <string.h>

const char *ACCOUNTFILENAME = "account.dat";

typedef struct Account
{
    char name[100];
    int accountnumber;
    float balance;
} Account;

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

void createAccount()
{
    printf("\n--- Create Account ---\n");

    Account acc;

    // We will store the information in a file (append binary mode)
    FILE *file = fopen(ACCOUNTFILENAME, "ab+");

    // Error handling
    if (file == NULL)
    {
        printf("Unable to open file!!\n");
        return;
    }

    // Clear the input buffer from scanf
    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("Enter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);

    // Replacing the tailing newline character
    int index = strcspn(acc.name, "\n");
    acc.name[index] = '\0';

    // Getting the account number from user
    printf("Enter your Account Number: ");
    scanf("%d", &acc.accountnumber);

    // Setting initial balance to 0
    acc.balance = 0;

    // Writing the customer info into the made file
    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);

    printf("Account Created Successfully\n\n");
}

void depositMoney()
{
    printf("\n--- Deposit Money --- \n");

    int userEnteredAccountNumber;
    float depositAmount;
    Account acc_to_read;

    // Open the file with customer info
    FILE *file = fopen(ACCOUNTFILENAME, "rb+");

    // Error handling
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    // Getting the account number of user
    printf("Enter your account number: ");
    scanf("%d", &userEnteredAccountNumber);

    // Getting amount to be deposited
    printf("Enter deposit amount: ");
    scanf("%f", &depositAmount);

    // Reading all the account number in the file and matching
    while (fread(&acc_to_read, sizeof(acc_to_read), 1, file))
    {
        if (acc_to_read.accountnumber == userEnteredAccountNumber)
        {
            acc_to_read.balance += depositAmount;

            // moving the cursor back to the start of matching account no.
            fseek(file, -sizeof(acc_to_read), SEEK_CUR);

            // now write the updated balance in the file
            fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);

            fclose(file);
            printf("Successfully deposited: Rs %.2f. New Balance: %.2f\n", depositAmount, acc_to_read.balance);
            return;
        }
    }
    // If whole file read and no account match
    fclose(file);
    printf("Deposit Unsuccessful. Account Number %d not found.\n", userEnteredAccountNumber);
}

void withdrawMoney()
{
    printf("\n--- Withdraw Money ---\n");
    // Opening the file
    FILE *file = fopen(ACCOUNTFILENAME, "rb+");

    // Error handling
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    int userEnteredAccountNumber;
    float withdrawAmount;
    Account acc_to_read;

    // Getting the account number and amount from user
    printf("Enter your account number: ");
    scanf("%d", &userEnteredAccountNumber);
    printf("Enter the amount to withdraw: ");
    scanf("%f", &withdrawAmount);

    while (fread(&acc_to_read, sizeof(acc_to_read), 1, file))
    {
        if (acc_to_read.accountnumber == userEnteredAccountNumber)
        {
            if (acc_to_read.balance >= withdrawAmount)
            {
                acc_to_read.balance -= withdrawAmount;
                fseek(file, -(long)sizeof(acc_to_read), SEEK_CUR);
                fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);
                printf("Successfully withdrawn Rs %.2f. Remaining balance is Rs %.2f\n", withdrawAmount, acc_to_read.balance);
            }
            else
            {
                printf("Insufficient Balance.\n");
            }
            fclose(file);
            return;
        }
    }
    // If whole file read and no account match
    fclose(file);
    printf("Withdrawl Unsuccessful. Account Number %d not found.\n", userEnteredAccountNumber);
}

void checkBalance()
{
    printf("\n--- Check Balance ---\n");
    int userEnteredAccountNumber;

    // Open the file with customer info
    FILE *file = fopen(ACCOUNTFILENAME, "rb");

    // Error handling
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    // Getting the account number for user
    printf("Enter your Account Number: ");
    scanf("%d", &userEnteredAccountNumber);

    Account accRead;
    while (fread(&accRead, sizeof(accRead), 1, file))
    {
        if (accRead.accountnumber == userEnteredAccountNumber)
        {
            printf("Your Account Balance is: Rs %.2f\n", accRead.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account Number %d not found.\n", userEnteredAccountNumber);
}

int main()
{
    while (1)
    {
        int choice;
        printf("\nBANK MANAGEMENT SYSTEM\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        // scanf("%d", &choice);

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");

            // Clear the malicious leftover characters from the buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue; // Skip the switch statement and restart the menu loop
        }

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            printf("Exitting Programme.\n");
            return 0;
            break;

        default:
            printf("Invalid Choice!\n");

            break;
        }
    }

    return 0;
}