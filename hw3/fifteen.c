/**
 * fifteen.c
 *
 * Refer to Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep`.
 */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

#ifndef INT_MAX
    #define INT_MAX 12345678
#endif // INT_MAX

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void greet(void);
void init(void);
void draw(void);
short move(int tile);
short won(void);
int get_int();

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (1)
    {
       
        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

         // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        printf("\n");

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(200000);
        }

        // sleep thread for animation's sake
        usleep(150000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Get an non-negative integer from user input
 * If the input is not non-negative integer, return INT_MAX
 */

 int get_int()
 {
    int theInput = 0;
    short ifInvalid = 0;

    char c = getchar();
    if (c == '\n')
        return INT_MAX;

    while (c != '\n') 
    {
        if ((c >= '0') && ( c <= '9'))
        {
            theInput = theInput * 10 + (c - '0');
        } else {
            ifInvalid = 1;
        }

        c = getchar();
    }

    if (ifInvalid){
        return INT_MAX;
    }
    else {
        return theInput;
    }
 }

/**
 * Greets player.
 */
void greet(void)
{    
    printf("WELCOME TO GAME OF FIFTEEN\n");
   usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO:initialize the board
    
   int c = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
        // fill the tiles in descending order
        board[i][j] = d * d - c;
        c++;
        }
    }
    board[d-1][d-1] = 80;
    if ((d * d)%2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}


/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        { 
            //the fuction will print the blank tile
            if (board[i][j] == 80){
            
                printf("    _");
            }
            else{
            
            //this makes it in descending order
                printf("%5i ", board[i][j]);
            }
        }
        printf("\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
short move(int tile)
{

// establish algorithm for checking bordering tiles
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                //check if the blank is to the right
                if (j+1 <= d-1 && board[i][j+1] == 80)
                {
                    board[i][j+1] = tile;
                    board[i][j] = 80;
                    return 1;
                }
                // check if the blank is to the left
                else if (j-1 >= 0 && board[i][j-1] == 80)
                {
                    board[i][j-1] = tile;
                    board[i][j] = 80;
                    return 1;
                }
                // check if the blank is above
                else if (i-1 >= 0 && board[i-1][j] == 80)
                {
                    board[i-1][j] = tile;
                    board[i][j] = 80;
                    return 1;
                }
                // check if the blank is below
                else if (i+1 <= d-1 && board[i+1][j] == 80)
                {
                    board[i+1][j] = tile;
                    board[i][j] = 80;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * Returns 1 if game is won (i.e., board is in winning configuration),
 * else 0.
 */
short won(void)
{
    int n = 1;
    //fuction checks last tile to see if blank if not return 0
    if (board[d-1][d-1] != 80){

        return 0;

    }

    for (int i = 0; i < d; i++){

    
        for (int j = 0; j < d; j++)
        {
             if (i == d - 1 && j == d - 1){
                return 1;
            } 
            // function checks for empty tiles then returns 0
            if (n != board[i][j]){

                return 0;
                n++;
            }                      
        }
    }
    return 0;
}
