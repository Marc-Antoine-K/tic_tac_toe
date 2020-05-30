#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void print_board(int board[9], char human_start);
void human_move(int board[9]);
void dummy_computer_move(int board[9]);
void smart_computer_move(int board[9]);
bool is_move_valid(int move, int board[9]);
int winner(const int board[9]);
int minimax (int *board, int player);
int end(int board[9]);
void draw(int board[9]);


int main (void)
{

srand(time(NULL));   // Initialization, should only be called once.
int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.

int board[9] = {0};

//begins the game
printf("You just started a new game of Tic Tac Toe. \n");
printf(" 1 | 2 | 3 \n");
printf(" 4 | 5 | 6 \n");
printf(" 7 | 8 | 9 \n");

printf("X starts.\n Do you want to start? answer y or n\n");
char human_start = 'a';
while (human_start != 'y' && human_start != 'n')
{
    scanf("%c", &human_start);
}

//plays until there is a winner or no more move available
int turn = (human_start == 'y');
if (turn == 1)
    printf("YOU PLAY WITH 'X' \n");
else
    printf("YOU PLAY WITH '0' \n");

int score = winner(board);
int over = end(board);
while (score!= 3 && score !=-3 && over !=1)   
{
    if (turn == 1)
    {
        print_board(board, human_start);
        human_move(board);
        score = winner(board);
        over = end(board);
        turn = 0;
    }
    else 
    {
        //dummy_computer_move(board);
        smart_computer_move(board);
        score = winner(board);
        over = end(board);
        turn = 1;
    }
}

//declare the winner
print_board(board, human_start);
switch (score)
{
case 3:
    printf("The computer won, you lost!\n");
    break;
case -3:
    printf("Congratulations, you won!\n");
    break;

default:
    printf("It's a draw! \n");
    break;
}

return (0);
}

//return 3 if computer wins, -3 if human wins, else 0 
int winner(const int board[9])
{
    int sum = 0;
    //check row win
    for (int i = 0; i < 3; i++)
    {
        sum = board[3*i] + board[3*i+1] + board[3*i+2];
        if (sum == 3 || sum == -3)
        {
            return sum;
        }
    }

    //check colomun win
    for (int i = 0; i < 3; i++)
    {
        sum = board[i] + board[i+3] + board[i+6];
        if (sum == 3 || sum == -3)
        {
            return sum;
        }       
    }

    //check diagonal win
    for (int i = 0; i < 2; i++)
    {
        sum = board[3*i] + board[4] + board[8-2*i];   
        if (sum == 3 || sum == -3)
        {
            return sum;
        }              
    }
    return 0;
}

void human_move(int board[9])
{
    printf("Enter a valid number to play (between 1 and 9)\n");
    int move;
    scanf("%i", &move);
    if(is_move_valid(move, board))
    {
        board[move-1] = -1;
    }
    else
    {
        printf("The move you entered is not valid \n");
        human_move(board);
    }
}

void print_board(int board[9], char human_start)
{
    char char_board[9] = {' '};
    char human = 'X';
    char computer = 'O';
    if (human_start=='n')
    {
        human = 'O';
        computer = 'X';
    }
    for(int i = 0; i < 9; i++)
    {
        switch (board[i])
        {
        case -1:
            char_board[i] = human;
            break;
        case 1:
            char_board[i] = computer;
            break;
        
        default:
            char_board[i] = ' ';
            break;
        }
    }

    printf(" %c | %c | %c \n", char_board[0], char_board[1], char_board[2]);
    printf(" %c | %c | %c \n", char_board[3], char_board[4], char_board[5]);
    printf(" %c | %c | %c \n", char_board[6], char_board[7], char_board[8]);
}

bool is_move_valid(int move, int board[9])
{
    return (move > 0 && move < 10 && board[move-1] == 0);
}

void dummy_computer_move(int board[9])
{
    int move = (rand() % 9) + 1;
    if (is_move_valid(move, board))
    {
        board[move-1] = 1;
        printf("\n The computer plays %i\n", move);
    }
    else
    {
        dummy_computer_move(board);
    }
}

void smart_computer_move(int board[9])
{
    int move;
    int score;
    int bestscore = -100;//infinity
    //test all possinle moves
    for (int i = 0; i < 9; i++)
    {
        if (is_move_valid(i + 1, board))
        {
            board[i] = 1;
            score = minimax(board, -1);
            if (bestscore < score)
            {
                bestscore = score;
                move = i + 1;
            }
            board[i] = 0;
        }
    }
    //select the best play
    board[move-1] = 1;
    printf("\n The computer played %i\n", move);
}

//return the score of the board
int minimax(int *board, int player)
{
    int score = winner(board);
    //if we are at a leaf
    if (score == 3 || score == -3 || (score == 0 && end(board)))
    {
        return score;
    }
    else //we explore the tree
    {
        int bestscore = -100*player;
        if (player == 1)
        {
            for (int i = 0; i < 9; i++)
            {
                if (is_move_valid(i+1, board)) 
                {
                    board[i] = player;
                    score = minimax(board, player*(-1));//go down one layer and simulates the next player play
                    if (score > bestscore)//max
                        bestscore = score;
                    board[i] = 0;
                }
            }
            return (bestscore);
        }
        else if (player == -1 )
        {
            for (int i = 0; i < 9; i++)
            {
                if (is_move_valid(i+1, board)) 
                {
                    board[i] = player;
                    score = minimax(board, player*(-1));//go down one layer and simulates the next player play
                    if (score < bestscore)//min
                        bestscore = score;
                    board[i] = 0;
                }
            }
            return(bestscore);
        }
    }
}

//if no winner, check that there is still room for a move, if not returns 0
int end(int board[9])
{
    int board_full = 1;
    int end = 0;
    for (int i = 0; i < 9; i++)
    {
        board_full *= board[i];
    }
    if (board_full != 0)
    {
        //game is over
        end = 1;
    }
    return end;
}

void draw(int board[9])
{
    printf("\n");
    for(int i = 0; i < 9; i++)
    {
        printf("%i", board[i]);
        printf(" | ");
    }
    printf("\n");
}