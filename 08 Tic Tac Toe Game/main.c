#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARDSIZE 3
#define X 'X'
#define O 'O'

typedef struct Score
{
    int player;
    int computer;
    int draw;

} Score;

// Global Variable
int difficultyLevel;
Score score = {.player = 0, .computer = 0, .draw = 0};

// Function Prototype
void welcomeMessage();
void chooseDifficulty();
void clearScreen();
void printBoard(char board[BOARDSIZE][BOARDSIZE]);
int checkWin(char board[BOARDSIZE][BOARDSIZE], char player);
int checkDraw(char board[BOARDSIZE][BOARDSIZE]);
void playGame();
void playerMove(char board[BOARDSIZE][BOARDSIZE]);
void computerMove(char board[BOARDSIZE][BOARDSIZE]);
int validMove(char board[BOARDSIZE][BOARDSIZE], int row, int column);
int minimax(char board[BOARDSIZE][BOARDSIZE], int depth, int is_maximizing);

// Function Definition
void welcomeMessage()
{
    printf("\n--- Tic Tac Toe ---\n");
}

void chooseDifficulty()
{
    while (1)
    {
        printf("\nSelect Difficulty Level: \n");
        printf("1. Human (Standard)\n");
        printf("2. God Mode (Impossible to Win)\n");
        printf("Enter your choice: ");
        scanf("%d", &difficultyLevel);

        // If user enters something other 1 or 2 re-run loop
        if (difficultyLevel != 1 && difficultyLevel != 2)
        {
            printf("\nIncorrect Choice. Enter 1/2\n");
        }
        else
        {
            break;
        }
    };
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear")
#endif
}

void printBoard(char board[BOARDSIZE][BOARDSIZE])
{
    clearScreen();
    welcomeMessage();
    printf("\n SCORE: Player X: %d | Computer: %d | Draw: %d\n", score.player, score.computer, score.draw);

    // Board - A 2D character array of 3x3
    for (int i = 0; i < BOARDSIZE; i++)
    {
        printf("\n");

        for (int j = 0; j < BOARDSIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < BOARDSIZE - 1)
            {
                printf("|");
            }
        }
        if (i < BOARDSIZE - 1)
        {
            printf("\n---+---+---");
        }
    }
    printf("\n\n");
}

int checkWin(char board[BOARDSIZE][BOARDSIZE], char player)
{
    // Winning Logic
    for (int i = 0; i < BOARDSIZE; i++)
    {
        // Check if same symbol in the Row. Row fix column changes
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            // 1 for win
            return 1;
        }
        // Check if same symbol in the Column. Column fix row changes
        else if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            // 1 for win
            return 1;
        }
        // Check if same symbol in both the Diagonal
        else if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[2][0] == player && board[1][1] == player && board[0][2] == player))
        {
            // 1 for win
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int checkDraw(char board[BOARDSIZE][BOARDSIZE])
{
    // Just check if anyone won and if the board is full or not
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                // 0 for not draw
                return 0;
            }
        }
    }
    // 1 for draw
    return 1;
}

void playGame()
{
    // It will make the board first for every instance
    char board[BOARDSIZE][BOARDSIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };

    // if random number is 0 then X if any number other than 0 then O
    char currentPlayer = rand() % 2 == 0 ? X : O;

    printBoard(board);
    while (1)
    {
        // Player has made a move check if he won with that move or not
        if (currentPlayer == X)
        {
            playerMove(board);
            printBoard(board);
            if (checkWin(board, X))
            {
                score.player++;
                printBoard(board);
                printf("Congratulations! You have Won\n");
                break;
            }
            currentPlayer = O;
        }
        // Computer has made a move check if computer has won with that move or not
        else
        {
            computerMove(board);
            printBoard(board);
            if (checkWin(board, O))
            {
                score.computer++;
                printBoard(board);
                printf("Computer Won! Well Played\n");
                break;
            }
            currentPlayer = X;
        }

        // Check if the game is Draw
        if (checkDraw(board))
        {
            score.draw++;
            printBoard(board);
            printf("\nIt's a Draw\n");
            break;
        }
    };
}

void playerMove(char board[BOARDSIZE][BOARDSIZE])
{
    int count = 0, x, y;
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1)
    {
        board[x][y] = X;
        return;
    }

    int row;
    int column;
    do
    {
        printf("\n Player X's turn");
        printf("\nEnter row and column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &column);

        // converting to zero based
        row--;
        column--;

    } while (!validMove(board, row, column));

    // Move is registered on the board
    board[row][column] = X;
}

int minimax(char board[BOARDSIZE][BOARDSIZE], int depth, int is_maximizing)
{
    // Minimax for God mode: O is the maximizing computer, X is the player.
    // Returns a score relative to O: +10 - depth for an O win (prefer faster wins),
    // depth - 10 for an X win (prefer slower losses), 0 for a draw.
    if (checkWin(board, O))
    {
        return 10 - depth;
    }
    if (checkWin(board, X))
    {
        return depth - 10;
    }
    if (checkDraw(board))
    {
        return 0;
    }

    if (is_maximizing)
    {
        int best = -1000;
        for (int i = 0; i < BOARDSIZE; i++)
        {
            for (int j = 0; j < BOARDSIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = O;
                    int sc = minimax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (sc > best)
                    {
                        best = sc;
                    }
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < BOARDSIZE; i++)
        {
            for (int j = 0; j < BOARDSIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = X;
                    int sc = minimax(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (sc < best)
                    {
                        best = sc;
                    }
                }
            }
        }
        return best;
    }
}

void computerMove(char board[BOARDSIZE][BOARDSIZE])
{
    // GOD Mode: play the optimal move via minimax (unbeatable).
    if (difficultyLevel == 2)
    {
        int best_score = -1000, best_row = -1, best_col = -1;
        for (int i = 0; i < BOARDSIZE; i++)
        {
            for (int j = 0; j < BOARDSIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = O;
                    int sc = minimax(board, 0, 0);
                    board[i][j] = ' ';
                    if (sc > best_score)
                    {
                        best_score = sc;
                        best_row = i;
                        best_col = j;
                    }
                }
            }
        }
        if (best_row != -1)
        {
            board[best_row][best_col] = O;
            return;
        }
    }

    // 1. Play for Immediate win
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (checkWin(board, O))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 2. Play for Immediate Block
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (checkWin(board, X))
                {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 3. Play first available move
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                return;
            }
        }
    }
}

int validMove(char board[BOARDSIZE][BOARDSIZE], int row, int column)
{
    return !(row < 0 || column < 0 ||
             row > 2 || column > 2 ||
             board[row][column] != ' ');
}

int main()
{
    // For choosing which symbol to assign player
    srand(time(NULL));

    int choice;
    welcomeMessage();
    chooseDifficulty();

    do
    {
        playGame();
        printf("\nPlay again? (Yes-1 No-0): ");
        scanf("%d", &choice);

    } while (choice == 1);

    printf("\nThanks for Playing");

    return 0;
}