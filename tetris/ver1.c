// includes
#include <stdio.h>
#include <time.h>

// --- defines
// macro
#define clearScreen() printf("\033[2J")
#define setPosition(x, y) printf("\033[%d;%dH", (y)+1, (x)*2+1)
#define cursorOn() printf("\033[?25h")
#define cursorOff() printf("\033[?25l")
#define setCharColor(n) printf("\033[3%dm", (n))
#define setBackColor(n) printf("\033[%4dm", (n))
#define setAttribute(n) printf("\033[%dm", (n))
// field
#define WIDTH 10
#define HEIGHT 20
// color
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7
#define DEFAULT 9
// brightness
#define NORMAL 0
#define BRIGHT 1
#define DIM 2
// style
#define UNDERBAR 4
#define BLINK 5
#define REVERSE 7
#define HIDE 8
#define STRIKE 9

// prototypes
void init(void);
void reset(void);
int wait(int msec);

/*
 * initialize
 */
void init(void)
{
	setBackColor(BLACK);
	setCharColor(WHITE);
	setAttribute(NORMAL);
	clearScreen();
	cursorOff();
}

/*
 * reset
 */
void reset(void)
{
	setBackColor(BLACK);
	setCharColor(WHITE);
	setAttribute(NORMAL);
	clearScreen();
	cursorOn();
}

/*
 * main func
 */
int main(int argc, char *argv[])
{
	int y;
	// 
	init();
	// 
	for (y = 1; y < 23; y++)
	{
		// show cells
		setPosition(5, y);
		setCharColor(WHITE);
		setBackColor(BLACK);
		setAttribute(REVERSE);
		printf("  ");
		fflush(stdout);

		wait(500);

		// destroy cells
		setPosition(5, y);
		setCharColor(WHITE);
		setBackColor(BLACK);
		setAttribute(NORMAL);
		printf("  ");
		fflush(stdout);
	}
	reset();
	
}

/*
 * wait func
 */
int wait(int msec)
{
	struct timespec r = {0, msec * 1000L * 1000L};
	return nanosleep(&r, NULL);
}






