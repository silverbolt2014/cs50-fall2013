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
#define PADDLE_COLLISION_COLOR_TIMER 50

#define BRICK_VERTICAL_OFFSET 15
#define BRICK_HORIZONTAL_OFFSET 40
#define BRICK_TOP_BORDER_MARGIN 20

#define BALL_HEIGHT 20
#define BALL_WIDTH 20
#define BALL_VELOCITY 2


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
    double ball_speed_x = BALL_VELOCITY;
    double ball_speed_y = BALL_VELOCITY;

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    int paddle_color_timer = 0;

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = 10;//COLS * ROWS;

    // number of lives initially
    int lives = LIVES;
    bool restart_flag = false;

    // number of points initially
    int points = 0;
    
    // Wait a click before starting the game
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Restart the game if the user lost a life
        if (restart_flag)
        {
            // Remove previous paddle and ball
            removeGWindow(window, ball);
            //removeGWindow(window, paddle);            
            //freeGObject(paddle);
            freeGObject(ball);
            
            // Initialize a new paddle and ball
            //paddle = initPaddle(window);
            ball = initBall(window);
            ball_speed_x = BALL_VELOCITY;
            ball_speed_y = BALL_VELOCITY;            
            
            // Disable the restart flag
            restart_flag = false;
            waitForClick();
        }
        
        // ** Handle paddle movement **
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we have one
        if (event != NULL)
        {
            // if the event was mouse movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                //printf("mouse is at %0.f, %0.f\n", getX(event), getY(event));
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
                
                // Update paddle location
                setLocation(paddle, paddle_x, PADDLE_VERTICAL_LOCATION);
            }
        }

        // ** Handle ball movement **
        move(ball, ball_speed_x, ball_speed_y);

        // bounce off right edge of window
        if (getX(ball) + BALL_WIDTH >= WIDTH)
        {
            ball_speed_x *= -1;
        }
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            ball_speed_x *= -1;
        }

        // bounce off bottom of window
        if (getY(ball) + BALL_HEIGHT >= HEIGHT)
        {
            ball_speed_y *= -1;
            lives--;
            printf("Lost a life, lives remaining = %i\n", lives);
            restart_flag = true;
            continue;
        }
        // bounce off top of window
        else if (getY(ball) <= 0)
        {
            ball_speed_y *= -1;
        }


        // ** Handle collision with paddle when the ball is moving downwards
        GObject collision_object = detectCollision(window, ball);
        if ( collision_object != NULL)
        {
            if ( collision_object == paddle)
            {
                if (ball_speed_y > 0)
                {
                    ball_speed_y *= -1;
                }
                setColor(paddle, "RED");
                setFilled(paddle, true);
                paddle_color_timer = PADDLE_COLLISION_COLOR_TIMER;
            }
            else if ( strcmp(getType(collision_object), "GRect") == 0)
            {
                removeGWindow(window, collision_object);
                freeGObject(collision_object);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
                ball_speed_y *= -1;
            }
        }
        else
        {
            if (paddle_color_timer > 0 )
            {
                setColor(paddle, "RED");
                setFilled(paddle, true);
                paddle_color_timer--;
            }
            else
            {
                setColor(paddle, "GRAY");
                setFilled(paddle, true);
            }
        }
        pause(10);
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
    // Array of brick colors
    char* brick_color[] = {"CYAN", "GREEN", "MAGENTA", "ORANGE", "YELLOW"};
    
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(j * BRICK_HORIZONTAL_OFFSET + 2, i * BRICK_VERTICAL_OFFSET + 2 + BRICK_TOP_BORDER_MARGIN, 35, 10);
            setColor(brick, brick_color[i]);
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2 - BALL_WIDTH/2, HEIGHT/2- BALL_HEIGHT/2, BALL_WIDTH, BALL_HEIGHT);
    add(window, ball);
    setColor(ball, "BLUE");
    setFilled(ball, true);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
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
    GLabel score_label = newGLabel("0");
    setFont(score_label, "SansSerif-70");
    double x = WIDTH/2  - (getWidth(score_label)/2);
    double y = HEIGHT/2 - getHeight(score_label)/2;
    setLocation(score_label, x, y);
    add(window, score_label);
    return score_label;
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
