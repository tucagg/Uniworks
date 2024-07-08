#ifndef _UTIL_H_
#define _UTIL_H_

#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
#define RIGHT 'r'
#define UP1 'U'
#define DOWN1 'D'
#define LEFT1 'L'
#define RIGHT1 'R'

int checkisitrandom(int puzzle[3][3], int sayi);
int checkisittrue(int puzzle[3][3]);
void create_puzzle(int puzzle[3][3]);
int checkfun(int puzzle[3][3], int sayi, int score);
int gamefunc(int puzzle[3][3], int sayi, int movement_x, int movement_y, char yon);
int show_puzzle(int puzzle[3][3],int score);
void menu();
int case1(int movement_x, int movement_y, int puzzle[3][3], int sayi,int score);
int write_best_score(int score);
void autofinish(int puzzle[3][3], int sayi, int movement_x, int movement_y, int score);


#endif /* _UTIL_H_ */