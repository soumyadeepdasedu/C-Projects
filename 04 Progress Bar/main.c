#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Global Variable
const int BARLENGTH = 50;
const int MAXTASKS = 5;

typedef struct task
{
    int id;
    int progress;
    int step;
} Task;

// Function Prototype
void printBars(Task task);
void clearScreen();

// Function Definitions
void printBars(Task task)
{
    int bars = (task.progress * BARLENGTH) / 100;
    printf("Task %d: [", task.id);

    for (int i = 0; i < BARLENGTH; i++)
    {
        if (i < bars)
        {
            printf("-");
        }
        else
            printf(" ");
    }
    printf("] %d%%\n", task.progress);
}

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main()
{
    Task tasks[MAXTASKS];
    srand(time(NULL));
    // Seeding with time else everytime same random numbers will assigned

    for (int i = 0; i < MAXTASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    int tasksIncomplete = 1;
    while (tasksIncomplete)
    {
        tasksIncomplete = 0;
        clearScreen();
        printf("\t\t\tTASK PROGRESS BAR\n");

        for (int i = 0; i < MAXTASKS; i++)
        {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100)
            {
                tasks[i].progress = 100;
            }
            else if (tasks[i].progress < 100)
            {
                tasksIncomplete = 1;
            }
            printBars(tasks[i]);
        }

        sleep(1);
    }
    printf("All Tasks Completed!\n");

    return 0;
}