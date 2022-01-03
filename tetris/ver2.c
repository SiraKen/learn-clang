// --- includes
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
// block
#define BLOCK_SIZE 4
#define BLOCK_NUM 7

// --- typedef
typedef struct cell
{
	char c;
	int charcolor;
	int backcolor;
	int attribute;
} Cell;

// block
Cell block_type[BLOCK_NUM][BLOCK_SIZE][BLOCK_SIZE] = {
	'\0', RED, BLACK, NORMAL,
	'\0', RED, BLACK, NORMAL,
	' ', RED, BLACK, REVERSE,
	'\0', RED, BLACK, NORMAL
};


// --- prototypes
void init(void);
void reset(void);
int wait(int msec);
int checkRange(Cell a, int x, int y);
int printCell(Cell c, int x, int y);
int clearCell(Cell c, int x, int y);
void copyBlock(Cell src[BLOCK_SIZE][BLOCK_SIZE], Cell dst[BLOCK_SIZE][BLOCK_SIZE]);
void printBlock(Cell block[BLOCK_SIZE][BLOCK_SIZE], int x, int y);
void clearBlock(Cell block[BLOCK_SIZE][BLOCK_SIZE], int x, int y);

/*
 * main func
 */
int main(int argc, char *argv[])
{
	int i;
	Cell block[BLOCK_SIZE][BLOCK_SIZE];
	copyBlock(block_type[1], block);
	// 
	init();
	// 
	for (i = 1; i < HEIGHT; i++)
	{
		printBlock(block, 5, i);
		wait(500);
		clearBlock(block, 5, i);
	}
	reset();
	
}

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
 * wait func
 */
int wait(int msec)
{
	struct timespec r = {0, msec * 1000L * 1000L};
	return nanosleep(&r, NULL);
}

/*
 * check range func
 */
int checkRange(Cell a, int x, int y)
{
	if (a.c == '\0' || x < 0 || y < 0 || WIDTH <= x || HEIGHT <= y)
		return -1;
	else
		return 0;
}

/*
 * print cell func
 */
int printCell(Cell c, int x, int y)
{
	if (checkRange(c, x, y) == -1)
		return -1;
	setPosition(x, y);
	setAttribute(c.attribute);
	setBackColor(c.backcolor);
	setCharColor(c.charcolor);
	printf("%c%c", c.c, c.c);
	fflush(stdout);
	return 0;
}

/*
 * clear cell func
 */
int clearCell(Cell c, int x, int y)
{
	if (checkRange(c, x, y) == -1)
		return -1;
	setPosition(x, y);
	setAttribute(NORMAL);
	setBackColor(BLACK);
	setCharColor(BLACK);
	printf("  ");
	fflush(stdout);
	return 0;
}

/*
 * copy block func
 */
void copyBlock(Cell src[BLOCK_SIZE][BLOCK_SIZE], Cell dst[BLOCK_SIZE][BLOCK_SIZE])
{
	int i, j;
	for (j = 0; j < BLOCK_SIZE; j++)
		for (i = 0; i < BLOCK_SIZE; i++)
			dst[j][i] = src[j][i];
}

/*
 * print block func
 */
int printBlock(Cell block[BLOCK_SIZE][BLOCK_SIZE], int x, int y)
{
	int i, j;
	for (j = 0; j < BLOCK_SIZE; j++)
		for (i = 0; i < BLOCK_SIZE; i++)
			printCell(block[j][i], i + x, j + y);
	return 0;
}

/*
 * clear block func
 */
int clearBlock(Cell block[BLOCK_SIZE][BLOCK_SIZE], int x, int y)
{
	int i, j;
	for (j = 0; j < BLOCK_SIZE; j++)
		for (i = 0; i < BLOCK_SIZE; i++)
			clearCell(block[j][i],i + x, j + y);
	return 0;
}

