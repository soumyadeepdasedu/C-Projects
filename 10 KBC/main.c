#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200809L
#define MAX_QUESTIONLEN 300
#define MAX_OPTIONLEN 100

volatile int timeout_happened = 0;

const char *PINK = "\033[1;35m";
const char *BLUE = "\033[1;34m";
const char *GREEN = "\033[1;32m";
const char *YELLOW = "\033[1;33m";
const char *AQUA = "\033[1;36m";
const char *RED = "\033[1;31m";
const char *COLOR_END = "\033[0m";

typedef struct
{
    char text[MAX_QUESTIONLEN];
    char options[4][MAX_OPTIONLEN];
    char correctOption;
    int timeout;
    int prize;
} Question;

// Function Prototype
int readQs(char *filename, Question **questions);
void printFormattedQs(Question questions);
void heading();
void timeout_handler(int sig);
void playGame(Question *questions, int numberOfQs);
int useLifeline(Question *question, int *lifeline);

// Function Definition
int readQs(char *filename, Question **questions)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open question bank\n");
        exit(0);
    }

    char str[MAX_QUESTIONLEN];
    int numberOfLines = 0;
    while (fgets(str, MAX_QUESTIONLEN, file))
    {
        numberOfLines++;
    }
    int numberOfQuestions = numberOfLines / 8;
    *questions = (Question *)malloc(numberOfQuestions * sizeof(Question));

    // Putting the cursor at start of file
    rewind(file);
    for (int i = 0; i < numberOfQuestions; i++)
    {
        // Read Question and store it in variable
        fgets((*questions)[i].text, MAX_QUESTIONLEN, file);
        for (int j = 0; j < 4; j++)
        {
            fgets((*questions)[i].options[j], MAX_OPTIONLEN, file);
        }

        // Read Options and store it in variable
        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correctOption = option[0];

        // Read Timeout number convert chracter to integer before storing in variable
        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        // Read the prize money convert character to integer before storing it in variable
        char prize[10];
        fgets(prize, 10, file);
        (*questions)[i].prize = atoi(prize);
    }
    fclose(file);
    return numberOfQuestions;
}

void printFormattedQs(Question questions)
{
    printf("\n\n%s%s%s", YELLOW, questions.text, COLOR_END);

    for (int i = 0; i < 4; i++)
    {
        if (questions.options[i][0] != '\0')
        {
            printf("%s%c. %s%s", AQUA, ('A' + i), questions.options[i], COLOR_END);
        }
    }
    printf("\n%sHurry!! You have only %d seconds to answer%s", YELLOW, questions.timeout, COLOR_END);
    printf("\n%sEnter your asnwer (A / B / C / D or L for Lifeline): %s", GREEN, COLOR_END);

    // printf("\n%s\n%s\n%s\n%s\n%s\n", questions.text, questions.options[0], questions.options[1], questions.options[2], questions.options[3]);
    // printf("\n%c\n%d\n%d\n", questions.correctOption, questions.timeout, questions.prize);
}

void heading()
{
    printf("\n\n%sKAUN BANEGA CROREPATI%s", PINK, COLOR_END);
    printf("\t%sKAUN BANEGA CROREPATI%s", BLUE, COLOR_END);
    printf("\t%sKAUN BANEGA CROREPATI%s", YELLOW, COLOR_END);
    printf("\t%sKAUN BANEGA CROREPATI%s", GREEN, COLOR_END);
    printf("\t%sKAUN BANEGA CROREPATI%s", AQUA, COLOR_END);
    printf("\t%sKAUN BANEGA CROREPATI%s", RED, COLOR_END);
}

void timeout_handler(int sig)
{
    (void)sig;
    timeout_happened = 1;
    printf("\n\n%sTime Out. Press any key%s\n", RED, COLOR_END);
    fflush(stdout);
}

void playGame(Question *questions, int numberOfQs)
{
    int money = 0;
    int lifeline[] = {1, 1};

    signal(SIGALRM, timeout_handler);

    for (int i = 0; i < numberOfQs; i++)
    {
        printFormattedQs(questions[i]);
        alarm(questions[i].timeout);
        char ch = getchar();
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        alarm(0);
        
        ch = toupper(ch);


        if (timeout_happened == 1)
        {
            break;
        }
        


        if (ch == 'L')
        {
            int value = useLifeline(&questions[i], lifeline);
            if (value != 2)
            {
                i--;
            }
            continue;
        }
        if (ch == questions[i].correctOption)
        {
            printf("%sCorrect Answer%s\n", GREEN, COLOR_END);
            money = questions[i].prize;
            printf("%sYou have won: %d%s\n", BLUE, money, COLOR_END);
        }
        else
        {
            printf("\n%sWrong! Correct Answer is %c%s\n", RED, questions[i].correctOption, COLOR_END);
            break;
        }
    }
    printf("\n\n%sGame Over! You total winnigs are Rs %d%s", BLUE, money, COLOR_END);
}

int useLifeline(Question *question, int *lifeline)
{
    printf("\n%sAvailble Lifelines: %s", PINK, COLOR_END);
    if (lifeline[0])
    {
        printf("\n%s1. Fifty-Fifty (50/50)%s", PINK, COLOR_END);
    }
    if (lifeline[1])
    {
        printf("\n%s2. Skip the Question%s", PINK, COLOR_END);
    }
    printf("\n%sChoose a lifeline or 0 to return: %s", PINK, COLOR_END);

    char ch1 = getchar();
    int c1;
    while ((c1 = getchar()) != '\n' && c1 != EOF)
        ;

    switch (ch1)
    {
    case '1':
        if (lifeline[0])
        {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2)
            {
                int num = rand() % 4;
                if ((num + 'A') != question->correctOption && question->options[num][0] != '\0')
                {
                    question->options[num][0] = '\0';
                    removed++;
                }
            }
            return 1;
        }
        break;
    case '2':
        if (lifeline[1])
        {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default:
        printf("\n%sReturning to the Question%s", PINK, COLOR_END);

        break;
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    heading();
    Question *questions;
    int numberOfQs = readQs("questions.txt", &questions);
    playGame(questions, numberOfQs);

    return 0;
}