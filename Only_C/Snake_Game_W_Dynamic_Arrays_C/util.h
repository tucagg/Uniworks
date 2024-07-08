#ifndef _UTIL_H_
#define _UTIL_H_

#define BOARD_SIZE 10

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    char type;
    int value;
} Block;

typedef struct {
    Point* snake;
    int length;
    char direction;
} Snake;

Block** init_board();
void draw_board(Block** board, Snake* snake);
void play();
void move_snake(Snake* snake);
int check_status(Block** board, Snake* snake);
int update(Block** board, Snake* snake, int* moveCount);
void update_bait(Block** board);
void update_obstacles(Block** board);
void cleanup_board(Block** board);
void cleanup_snake(Snake* snake);


#endif /* _UTIL_H_ */