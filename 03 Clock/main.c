#include <stdio.h>
#include <time.h>   //For bringing Time and Date from system
#include <unistd.h> //For sleep function
#include <stdlib.h> //For Clearing the Screen after every loop

//Function Prorotype
void fillTime(char *buffer, int format);
void fillDate(char *buffer);
int inputFormat();
void clearScreen();

//Function Definitions
void fillTime(char *buffer, int format)
{
    time_t rawTime;
    struct tm *currentTime;

    time(&rawTime);
    currentTime = localtime(&rawTime); //Converting to Local Time Zone

    if (format == 1) //24 Hour Format
    {
        strftime(buffer, 100, "%H:%M:%S", currentTime);
    }
    else //12 Hour Format
    {
        strftime(buffer, 100, "%I:%M:%S %p", currentTime);
    }
}

void fillDate(char *buffer)
{
    time_t rawTime;
    struct tm *currentTime;

    time(&rawTime);
    currentTime = localtime(&rawTime);
    strftime(buffer, 100, "%A %d %B %Y", currentTime);
}

int inputFormat()
{
    int format;
    printf("Choose the Time Format: \n");
    printf("1. 24 Hour Format\n");
    printf("2. 12 Hour Format (default)\n");
    printf("Your Choice: ");
    scanf("%d", &format);
    return format;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls"); //For Windows
#else
    system("clear"); //For Other OS
#endif
}

int main()
{
    char time[100];
    char date[100];
    int format = inputFormat();

    while (1)
    {
        fillTime(time, format);
        fillDate(date);
        clearScreen();
        printf("<>----------CLOCK-------------<>\n");
        printf("Current Time: %s\n", time);
        printf("Today's Date: %s\n", date);
        printf("<>----------------------------<>\n");
        sleep(1); // Sleep for 1 sec after every loop or it will print let's say 1000 times per sec
    }

    return 0;
}