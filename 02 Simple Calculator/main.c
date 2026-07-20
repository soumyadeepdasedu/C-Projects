#include <stdio.h>
#include <math.h> //For power calculation

// Global Variable
int choice;
double number1, number2;
double result;

// Function Prototype
void printMenu();
double division(double a, double b);
double modulus(int a, int b);

// Function Definition
void printMenu()
{
    printf("-------------------------------");
    printf("\nWelcome to Calculator\n\n");
    printf("Choose from the following options: \n\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");

    printf("Enter your Choice: ");
}

double division(double a, double b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid Argument for Division\n");
        return NAN; // NAN - Not A Number
    }
    return a / b;
}

double modulus(int a, int b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid Argument for Modulus.\n");
        return NAN;
    }
    return a % b;
}

int main()
{
    while (1)
    {
        printMenu();

        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer to prevent infinite loops
            continue;
        }

        if (choice == 7)
        {
            break;
        }
        if (choice < 1 || choice > 7)
        {
            fprintf(stderr, "Invalid Argument.\n");
            continue;
        }

        printf("Enter Number 1: ");
        scanf("%lf", &number1);
        printf("Enter Number 2: ");
        scanf("%lf", &number2);

        // Operations
        switch (choice)
        {
        case 1: // Add
            result = number1 + number2;
            break;
        case 2: // Sub
            result = number1 - number2;
            break;
        case 3: // Multiply
            result = number1 * number2;
            break;
        case 4: // Divide
            result = division(number1, number2);
            break;
        case 5: // Modulus
            result = modulus((int)number1, (int)number2);
            break;
        case 6: // Power
            result = pow(number1, number2);
            break;
        }

        if (!isnan(result))
        {
            printf("\nResult: %.2lf\n", result);
        }
    };

    printf("Goodbye!\n");

    return 0;
}