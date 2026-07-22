#include <stdio.h>

// Making the sudoku grid with few numbers pre-filled
int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

void welcomeMessage();
void printPuzzle(int puzzle[9][9]);
int moveValidity(int puzzle[9][9], int row, int column, int value);
int solvePuzzle(int puzzle[9][9], int row, int column);

void welcomeMessage()
{
    // Welcome Message
    printf("\n<>--- Welcome to Sudoku Solver ---<>\n\n");
    printf("Rule: Fill numbers from 1 to 9 in the blank spaces\n");
    printf("No number should be repeated in same Row, Column or Box\n");
}

void printPuzzle(int puzzle[9][9])
{
    // First Separation
    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");

        for (int column = 0; column < 9; column++)
        {
            if (column % 3 == 0)
            {
                printf("| ");
            }

            // Prinintng the numbers (1 to 9)
            if (puzzle[row][column] != 0)
            {
                printf("%d ", puzzle[row][column]);
            }
            else
            {
                printf("  "); // Two spaces
            }
        }
        printf("|");
    }

    // End Separation
    printf("\n+-------+-------+-------+\n\n");
}

int moveValidity(int puzzle[9][9], int row, int column, int value)
{
    // This function checks whether in one row, column, or box there is no repetetion of numbers from 1 to 9
    // For a sudoku puzzle to be valid, each row, each column and each box must have all the numbers from 1 to 9 without repeatition

    // Checking the entered number in Row
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == value)
        {
            return 0;
        }
    }

    // Checking the entered number in Column
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[i][column] == value)
        {
            return 0;
        }
    }

    // Checking the entered number in Box
    int rowOfBox = row - (row % 3);
    int columnOfBox = column - (column % 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[rowOfBox + i][columnOfBox + j] == value)
            {
                return 0;
            }
        }
    }

    // If not the 3 above cases
    // return 1 denoted Valid Move and return 0 for Invalid Move
    return 1;
}

int solvePuzzle(int puzzle[9][9], int row, int column)
{
    // This Function will fill the empty spaces using Backtracking

    // If column number reaches 9 which is not available because columns are from 0 to 8 then reset column to 0 and go to next row
    if (column == 9)
    {
        if (row == 8)
        {
            // If function reaches the last element that is row 8 and column 9 and still the puzzle is valid that means puzzle is solved
            //  1 for puzzle solved
            return 1;
        }
        else
        {
            // Else move to the next row first column and restart the iteration
            column = 0;
            row += 1;
        }
    }

    // If the element is > 0 that is space is filled, then do nothing and call this function for the next element of the same row
    if (puzzle[row][column] > 0)
    {
        return solvePuzzle(puzzle, row, column + 1);
    }

    // Now try filling numbers 1 to 9 one by one in the spaces simultaneously checking if it a valid move or not
    for (int i = 1; i <= 9; i++)
    {
        // Fill the number for which the move becomes valid, but the filled element is not permanent
        if (moveValidity(puzzle, row, column, i))
        {
            puzzle[row][column] = i;

            // After one element is filled go to next position
            if (solvePuzzle(puzzle, row, column + 1))
            {
                // If the next one, next to next one all returns 1 and all spaces get filled then puzzle is solved
                return 1;
            }

            // If anyone return 0 that is invalid move then reset the previous filled number
            puzzle[row][column] = 0;
        }
    }

    // If there is not any correct combination is found that means the puzzle is not solved
    return 0;
}

int main()
{
    welcomeMessage();
    printf("\n\nOriginal Puzzle: \n");

    printPuzzle(puzzle);

    if (solvePuzzle(puzzle, 0, 0))
    {
        printf("The Puzzle is Solved\n");
        printPuzzle(puzzle);
    }
    else
    {
        printf("Puzzle is not Solvable\n");
    }
    return 0;
}