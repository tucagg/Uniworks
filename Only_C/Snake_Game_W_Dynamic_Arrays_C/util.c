#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

Block** init_board() {
    Block** board = (Block**)malloc(BOARD_SIZE * sizeof(Block*));
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (Block*)malloc(BOARD_SIZE * sizeof(Block));
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j].type = 'e';
            board[i][j].value = 0;
        }
    }

    srand(time(NULL));

    // Randomly change the type of two blocks on the board
    int obstacleRow, obstacleCol;
    do {
        obstacleRow = rand() % BOARD_SIZE;
        obstacleCol = rand() % BOARD_SIZE;
    } while (obstacleRow == 0 && obstacleCol == 0); // Avoid placing obstacle on the top-left block
    board[obstacleRow][obstacleCol].type = 'o';
    board[obstacleRow][obstacleCol].value = 1;

    int baitRow, baitCol;
    do {
        baitRow = rand() % BOARD_SIZE;
        baitCol = rand() % BOARD_SIZE;
    } while (board[baitRow][baitCol].type != 'e');
    board[baitRow][baitCol].type = 'b';
    board[baitRow][baitCol].value = 0;

    return board;
}

void draw_board(Block** board, Snake* snake) {
    printf("+");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--");
    }
    printf("+\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (snake->snake[0].row == i && snake->snake[0].col == j) {
                printf(" O");
            } else {
                int isSnakeBody = 0;
                for (int k = 1; k < snake->length; k++) {
                    if (snake->snake[k].row == i && snake->snake[k].col == j) {
                        isSnakeBody = 1;
                        break;
                    }
                }
                if (isSnakeBody) {
                    printf(" X");
                } else if (board[i][j].type == 'b') {
                    printf(" .");
                } else if (board[i][j].type == 'o') {
                    printf("%2d", board[i][j].value);
                } else {
                    printf("  ");
                }
            }
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--");
    }
    printf("+\n");
}


void play() {
    Block** board = init_board();

    Snake snake;
    snake.snake = (Point*)malloc(sizeof(Point));
    snake.snake[0].row = 0;
    snake.snake[0].col = 0;
    snake.length = 1;
    snake.direction = 'd';

    int gameOver = 0;
    int moveCount = 0;

    while (!gameOver) {
        draw_board(board, &snake);
        move_snake(&snake);
        int other = update(board, &snake, &moveCount);
        gameOver = check_status(board, &snake);
        if (other) {
            break;
        }
    }

    printf("Game Over!\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        free(board[i]);
    }
    free(board);
    free(snake.snake);
}

void move_snake(Snake* snake) {
    char direction;
    printf("Enter next move (w/a/s/d): \n");
    scanf(" %c", &direction);

    // Check if the new direction is valid
    if ((direction == 'w' && snake->direction != 's') ||
        (direction == 'a' && snake->direction != 'd') ||
        (direction == 's' && snake->direction != 'w') ||
        (direction == 'd' && snake->direction != 'a')) {
        snake->direction = direction;
    }
}

int check_status(Block** board, Snake* snake) {
    int headRow = snake->snake[0].row;
    int headCol = snake->snake[0].col;

    // Check if the head of the snake hits its own body
    for (int i = 1; i < snake->length; i++) {
        if (snake->snake[i].row == headRow && snake->snake[i].col == headCol) {
            return 1;
        }
    }

    // Check if the snake collides with the wall
    if (headRow < 0 || headRow >= BOARD_SIZE || headCol < 0 || headCol >= BOARD_SIZE) {
        return 1;
    }

    // Check if the snake encounters an obstacle longer than itself
    if (board[headRow][headCol].type == 'o' && board[headRow][headCol].value > snake->length) {
        return 1;
    }

    return 0;
}

int update(Block** board, Snake* snake, int* moveCount) {
    int headRow = snake->snake[0].row;
    int headCol = snake->snake[0].col;

    int newRow, newCol;
    if (snake->direction == 'w') {
        if (headRow == 0) {
            return 1;
        } else {
            newRow = headRow - 1;
            newCol = headCol;
        }
    } else if (snake->direction == 'a') {
        if (headCol == 0) {
            return 1;
        } else {
            newRow = headRow;
            newCol = headCol - 1;
        }
    } else if (snake->direction == 's') {
        if (headRow == BOARD_SIZE - 1) {
            return 1;
        } else {
            newRow = headRow + 1;
            newCol = headCol;
        }
    } else if (snake->direction == 'd') {
        if (headCol == BOARD_SIZE - 1) {
            return 1;
        } else {
            newRow = headRow;
            newCol = headCol + 1;
        }
    }

    // Check if the snake has eaten the bait
    if (board[newRow][newCol].type == 'b') {
        snake->length++;
        Point* newSnake = (Point*)realloc(snake->snake, snake->length * sizeof(Point));
        if (newSnake != NULL) {
            snake->snake = newSnake;
            snake->snake[snake->length - 1].row = newRow;
            snake->snake[snake->length - 1].col = newCol;
        }
        board[newRow][newCol].type = 'e';
        board[newRow][newCol].value = 0;
    }
        // Shift the body of the snake
        for (int i = snake->length - 1; i > 0; i--) {
            snake->snake[i].row = snake->snake[i - 1].row;
            snake->snake[i].col = snake->snake[i - 1].col;
        }

        // Move the head of the snake
        snake->snake[0].row = newRow;
        snake->snake[0].col = newCol;
    

    // Update the bait and obstacles on the board
    int baitRow, baitCol;
    
    // Find the current bait position
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == 'b') {
                baitRow = i;
                baitCol = j;
                break;
            }
        }
    }

    // Check if the bait needs to be relocated
    if (board[baitRow][baitCol].type == 'e') {
        int newRow, newCol;
        do {
            newRow = rand() % BOARD_SIZE;
            newCol = rand() % BOARD_SIZE;
        } while (board[newRow][newCol].type != 'e');

        board[newRow][newCol].type = 'b';
        board[newRow][newCol].value = 0;
    }

    // Count the number of obstacles on the board
    int obstacleCount = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == 'o') {
                obstacleCount++;
            }
        }
    }
    // Add new obstacles every 5 moves
    if (*moveCount % 5 == 0 && obstacleCount < 3) {
        int obstacleRow, obstacleCol;
        do {
            obstacleRow = rand() % BOARD_SIZE;
            obstacleCol = rand() % BOARD_SIZE;
        } while (board[obstacleRow][obstacleCol].type != 'e');

        board[obstacleRow][obstacleCol].type = 'o';
        board[obstacleRow][obstacleCol].value = 1;
    }

    // Increase the height of existing obstacles randomly
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type == 'o') {
                if (rand() % 2 == 0) {
                    if(board[i][j].value < 9){
                    board[i][j].value++;}
                    else{
                        board[i][j].value = 1;
                    }

                }
            }
        }
    }

    // Update the obstacles every 5 moves
    if (*moveCount % 5 == 0 && obstacleCount > 2) {
        // Relocate the obstacles randomly
        Point obstacles[3];
        int obstacleCount = 0;

        // Find the current obstacles on the board and store their positions
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j].type == 'o') {
                    obstacles[obstacleCount].row = i;
                    obstacles[obstacleCount].col = j;
                    obstacleCount++;
                }
            }
        }

        // Relocate the obstacles randomly
        for (int i = 0; i < obstacleCount; i++) {
            int newRow, newCol;
            int isValidPosition = 0;

            while (!isValidPosition) {
                newRow = rand() % BOARD_SIZE;
                newCol = rand() % BOARD_SIZE;

                // Check if the new position is valid
                int isSnakeBody = 0;
                for (int k = 0; k < snake->length; k++) {
                    if (snake->snake[k].row == newRow && snake->snake[k].col == newCol) {
                        isSnakeBody = 1;
                        break;
                    }
                }

                // Check if the new position is the snake's head
                if (snake->snake[0].row == newRow && snake->snake[0].col == newCol) {
                    isSnakeBody = 1;
                }

                // Check if the new position is already an obstacle
                if (board[newRow][newCol].type == 'o') {
                    isSnakeBody = 1;
                }

                // If it's a valid position, relocate the obstacle
                if (!isSnakeBody) {
                    isValidPosition = 1;

                    // Copy the obstacle's value to the new position
                    board[newRow][newCol].type = 'o';
                     int height= board[obstacles[i].row][obstacles[i].col].value;
                     if(height<9){
                     board[newRow][newCol].value=height;
                     }
                     else{
                        board[newRow][newCol].value=9;
                     }
                    // Clear the old obstacle position
                    board[obstacles[i].row][obstacles[i].col].type = 'e';
                    board[obstacles[i].row][obstacles[i].col].value = 0;
                }
            }
        }
    }

    // Increase the move count
    (*moveCount)++;

    return 0;
}
