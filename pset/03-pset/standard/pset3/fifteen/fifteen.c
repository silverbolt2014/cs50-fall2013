/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500
#define BLANK_VALUE 0

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];
int blank_row = -1;
int blank_col = -1;

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // Initialize the board, starting with the largest number and moving down
    int count = d*d - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = count;
            count--;
        }
    }
    
    // If the board is even by even switch tiles 1 and 2
    if (d % 2 == 0)
    {
        board[ d - 1][d - 2] = 2;
        board[ d - 1] [d - 3] = 1;
    }
    
    // Save location of blank tile
    blank_row = d - 1;
    blank_col = d - 1;
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // printf("function: %s\n", __func__);
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%2i ", board[i][j]);
        }
        printf("\n");
    }

    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Validate user entered a valid tile value
    if (tile > d*d - 1 || tile < 1)
    {
        return false;
    }
    
    int tile_row = -1;
    int tile_col = -1;
    
    // Find coordinates for the tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if ( tile == board[i][j] )
            {
                tile_row = i;
                tile_col = j;
            }
            
        }
    }
    
    //- printf("tile = %d, [%i, %i]\n", tile, tile_row, tile_col);
    //- printf("blank tile [%i, %i]\n", blank_row, blank_col);
    
    // Up and Down - Same column
    if (blank_col == tile_col)
    {
        //- printf("Same column\n");
        // tile is above blank tile
        if ( blank_row - 1 == tile_row )
        {
            //- printf("The tile can move down\n");
            // new tile coordinates
            board[blank_row][tile_col] = tile;

            // new blank coordinates
            board[blank_row - 1][tile_col] = BLANK_VALUE;
            
            // Update blank coordinates
            blank_row = blank_row - 1;
            return true;
        }
        
        // title is below blank tile
        if ( blank_row + 1 == tile_row )
        {
            //- printf("The tile can move up\n");
            // new tile coordinates
            board[blank_row][tile_col] = tile;

            // new blank coordinates
            board[blank_row + 1][tile_col] = BLANK_VALUE;
            
            // Update blank coordinates
            blank_row = blank_row + 1;
            return true;
        }
    }
    
    
    // Left and Right - Same Row
    if (blank_row == tile_row)
    {
        //- printf("Same row\n");
        // tile is to the left of the blank tile
        if ( blank_col - 1 == tile_col )
        {
            //- printf("The tile can move right\n");
            // new tile coordinates
            board[blank_row][blank_col] = tile;

            // new blank coordinates
            board[blank_row][blank_col - 1] = BLANK_VALUE;
            
            // Update blank coordinates
            blank_col = blank_col - 1;
            return true;
        }
        // title is to the right of the blank tile
        if ( blank_col + 1 == tile_col )
        {
            //- printf("The tile can move left\n");
            // new tile coordinates
            board[blank_row][blank_col] = tile;

            // new blank coordinates
            board[blank_row][blank_col + 1] = BLANK_VALUE;
            
            // Update blank coordinates
            blank_col = blank_col + 1;

            return true;
        }
    }
    
    usleep(3000000);

    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int current_value = 1;
    
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (r == d-1 && c == d-1)
            {
                if ( board[r][c] == BLANK_VALUE )
                {
                    return true;
                }
            }
            else if ( board[r][c] != current_value )
            {
                return false;
            }
            current_value++;            
        }
    }
    printf("Error: Should never get here, line:%d\n", __LINE__);
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
