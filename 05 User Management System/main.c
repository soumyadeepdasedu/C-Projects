#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <windows.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int userCount = 0;

void userRegistration();
int userLogin(); // Returns the User Index
void fgetsInputFix(char *ptr);
void inputCredentials(char *username, char *password);

void userRegistration()
{
    if (userCount == MAX_USERS)
    {
        printf("Maximum %d Users are Supported. No more Registrations allowed\n\n", MAX_USERS);
        return;
    }

    int newIndex = userCount;
    printf("Registering a New User\n");

    inputCredentials(users[newIndex].username, users[newIndex].password);
    userCount++;
    printf("Registration Successful!\n\n");
}

int userLogin()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    inputCredentials(username, password);
    printf("\n");

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void fgetsInputFix(char *ptr)
{
    int index = strcspn(ptr, "\n");
    ptr[index] = '\0';
}

void inputCredentials(char *username, char *password)
{
    // Entering Username
    printf("Enter Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fgetsInputFix(username);
    printf("Enter Password (masking enabled): ");
    fflush(stdout);

    // Entering Password - Changing terminal properties for pass masking
    struct termios oldProps, newProps;
    tcgetattr(STDIN_FILENO, &oldProps);
    newProps = oldProps;
    newProps.c_lflag = ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newProps);

    // printf("Enter Password: ");
    // fgets(password, CREDENTIAL_LENGTH, stdin);
    // fgetsInputFix(password);

    char ch;
    int i = 0;
    while (ch = getchar() != '\n' && ch != EOF)
    {
        if (ch == '\b' || ch == 127)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldProps);

    printf("\n");
}

int main()
{
    int option;
    int userIndex;
    while (1)
    {
        printf("Welcome to User Management\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Select an Option: ");
        scanf("%d", &option);
        getchar(); // Consumes extra enter
        printf("\n");

        switch (option)
        {
        case 1: // Register
            userRegistration();
            break;
        case 2: // Login
            userIndex = userLogin();
            if (userIndex >= 0)
            {
                printf("Login Successful! Welcome %s!\n", users[userIndex].username);
            }
            else
            {
                printf("Login Failed! Incorrect Username or Passoword\n");
            }

            break;
        case 3: // Exit
            printf("Exitting Programme\n");
            return 0;
            break;

        default:
            fprintf(stderr, "Invalid Option. Please Try Again\n");
            break;
        }
    }

    return 0;
}