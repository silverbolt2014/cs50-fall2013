//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle size and specs
#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 60
#define PADDLE_VERTICAL_LOCATION 500

#define BRICK_VERTICAL_OFFSET 15
#define BRICK_HORIZONTAL_OFFSET 40
#define BRICK_TOP_BORDER_MARGIN 20


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        // TODO
        
        // ** Handle paddle movement **
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we have one
        if (event != NULL)
        {
            // if the event was mouse movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                //d printf("mouse is at %0.f, %0.f\n", getX(event), getY(event));
                double mouse_x = getX(event);
                double paddle_x = 0;
                
                // Paddle on left edge
                if (mouse_x <= PADDLE_WIDTH / 2)
                {
                    paddle_x = 0;
                }
                // Paddle on right edge
                else if (mouse_x >= WIDTH - PADDLE_WIDTH / 2)
                {
                    paddle_x = WIDTH - PADDLE_WIDTH;
                
                }
                // Paddle in middle
                else
                {
                    paddle_x = mouse_x - PADDLE_WIDTH / 2;
                }
                
                setLocation(paddle, paddle_x, PADDLE_VERTICAL_LOCATION);
            }
        }        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(j * BRICK_HORIZONTAL_OFFSET + 2, i * BRICK_VERTICAL_OFFSET + 2 + BRICK_TOP_BORDER_MARGIN, 35, 10);
            add(window, brick);
        
        }
    }
    
    /*
    
    GRect brick0 = newGRect(0 * BRICK_HORIZONTAL_OFFSET, 0, 20, 10);
    add(window, brick0);
        
    GRect brick1 = newGRect(1 * BRICK_HORIZONTAL_OFFSET, 0, 20, 10);
    //GRect brick1 = newGRect(40, 0, 20, 10);
    add(window, brick1);
    
    
    */



}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(0, 0, PADDLE_WIDTH, PADDLE_HEIGHT);
    add(window, paddle);
    setColor(paddle, "GRAY");
    setFilled(paddle, true);
    
    // Center the paddle
    setLocation(paddle, (WIDTH / 2) - (PADDLE_WIDTH / 2), PADDLE_VERTICAL_LOCATION);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
