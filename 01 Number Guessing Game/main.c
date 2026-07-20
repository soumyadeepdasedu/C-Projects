#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int randomNumber;
    int guess;
    int numberOfGuess = 0;

    // Welcome Message
    printf("Welcome to Number Guessing Game\n\n");

    // Generating a random number, seeding is based on time, at different times different numbers will be generated
    srand(time(NULL));
    randomNumber = rand() % 100 + 1;

    do
    {
        printf("Guess a number (1 to 100): ");
        scanf("%d", &guess);
        numberOfGuess++;

        if (randomNumber < guess)
            printf("Enter a Smaller Number: \n");
        else if (randomNumber > guess)
            printf("Enter a Greater Number: \n");
        else
            printf("You have Guessed the Number in %d attempts\n", numberOfGuess);

    } while (randomNumber != guess);

    printf("\nThanks for Playing the Game\n");
    printf("\n\nDeveloped by: Soumyadeep Das\n");

    return 0;
}