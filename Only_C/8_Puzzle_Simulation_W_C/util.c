#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

void autofinish(int puzzle[3][3], int sayi, int movement_x, int movement_y, int score) {
    if (checkisittrue(puzzle) == 1) {
        printf("Congratulations!\n");
        return;
    }
    
    int movements[4] = {UP, DOWN, LEFT, RIGHT};
    
    for (int i = 0; i < 4; i++) {
        int random_index = rand() % 4;
        char yon = movements[random_index];
        
        int bosluk_x, bosluk_y;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (puzzle[j][k] == '_') {
                    bosluk_x = j;
                    bosluk_y = k;
                }
            }
        }
        
        int temp;
        switch (yon) {
            case UP:
                if (bosluk_y == movement_y && (bosluk_x - movement_x) == -1) {
                    temp = puzzle[movement_x][movement_y];
                    puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                    puzzle[bosluk_x][bosluk_y] = temp;
                    score++;
                    show_puzzle(puzzle, score);
                    autofinish(puzzle, sayi, movement_x, movement_y, score);
                }
                break;
            case DOWN:
                if (bosluk_y == movement_y && (bosluk_x - movement_x) == 1) {
                    temp = puzzle[movement_x][movement_y];
                    puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                    puzzle[bosluk_x][bosluk_y] = temp;
                    score++;
                    show_puzzle(puzzle, score);
                    autofinish(puzzle, sayi, movement_x, movement_y, score);
                }
                break;
            case LEFT:
                if (bosluk_x == movement_x && (bosluk_y - movement_y) == -1) {
                    temp = puzzle[movement_x][movement_y];
                    puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                    puzzle[bosluk_x][bosluk_y] = temp;
                    score++;
                    show_puzzle(puzzle, score);
                    autofinish(puzzle, sayi, movement_x, movement_y, score);
                }
                break;
            case RIGHT:
                if (bosluk_x == movement_x && (bosluk_y - movement_y) == 1) {
                    temp = puzzle[movement_x][movement_y];
                    puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                    puzzle[bosluk_x][bosluk_y] = temp;
                    score++;
                    show_puzzle(puzzle, score);
                    autofinish(puzzle, sayi, movement_x, movement_y, score);
                }
                break;
            default:
                break;
        }
    }
}


int write_best_score(int score)
{
    FILE *fp2 = fopen("best_score.txt", "r");
    if (fp2 == NULL)
    {
        printf("Dosya bulunamadi.\n");
        return 1;
    }
    int best_score=0;
    fscanf(fp2, " %d", &best_score);
    fclose(fp2);
    score= 1000-(10*score);
    if (score > best_score)
    {
        FILE *fp3=fopen("best_score.txt","w");
        best_score = score;
        fprintf(fp2, "%d\n", best_score);
        fclose(fp3);
    }
    
    return best_score;
}

int checkisitrandom(int puzzle[3][3], int sayi)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == sayi)
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkisittrue(int puzzle[3][3])
{
    int i, j;
    int ilksayi;
    int sayac = 0;
    ilksayi = puzzle[0][0];
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (puzzle[i][j]!= '_' && puzzle[i][j] >= ilksayi)
            {
                ilksayi = puzzle[i][j];
                sayac++;
            }
        }
    }
    if (sayac == 8)
    {
        return 1;
    }
    return 0;
}

void create_puzzle(int puzzle[3][3])
{
    srand(time(NULL));
    int i, j;
    int sayi;
    int bosluk_random_dikey, bosluk_random_yatay;
    bosluk_random_dikey = rand() % 3;
    bosluk_random_yatay = rand() % 3;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (i == bosluk_random_dikey && j == bosluk_random_yatay)
            {
                puzzle[i][j] = '_';
            }
            else
            {
                sayi = rand() % 8 + 1;
                while (checkisitrandom(puzzle, sayi) == 1)
                {
                    sayi = rand() % 8 + 1;
                }
                puzzle[i][j] = sayi;
            }
        }
    }
}

int show_puzzle(int puzzle[3][3], int score)
{
    FILE *fp = fopen("board.txt", "a");
    if (fp == NULL)
    {
        printf("Dosya bulunamadi.\n");
        return 1;
    }
    
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == '_')
            {
                printf("_ ");
                fprintf(fp, "_ ");
            }
            else
            {
                printf("%d ", puzzle[i][j]);
                fprintf(fp, "%d ", puzzle[i][j]);
            }
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    fprintf(fp, "-----------------\n");
    score++;
    fclose(fp);
    return score;
}

int checkfun(int puzzle[3][3], int sayi, int score)
{
    if (checkisittrue(puzzle) == 1)
    {
        printf("Congratulations!\n");
        return 0;
    }
    else
    {
        int eslesme;
        char yon;
        printf("Enter your move(number-direction, e.g., 2-R): ");
        scanf("%d - %c", &eslesme, &yon);
        while (eslesme < 1 || eslesme > 8)
        {
            printf("Enter your move(number-direction, e.g., 2-R): ");
            scanf("%d - %c", &eslesme, &yon);
        }

        int movement_x = -1;
        int movement_y = -1;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (puzzle[i][j] == eslesme)
                {
                    movement_x = i;
                    movement_y = j;
                }
            }
        }

        if (movement_x != -1 && movement_y != -1)
        {
            gamefunc(puzzle, sayi, movement_x, movement_y, yon);
            show_puzzle(puzzle, score);
        }
        else
        {
            printf("Number not found in the puzzle.\n");
        }
    }
    return 1;
}

int gamefunc(int puzzle[3][3], int sayi, int movement_x, int movement_y, char yon)
{
    int bosluk_x, bosluk_y;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == '_')
            {
                bosluk_x = i;
                bosluk_y = j;
            }
        }
    }

    if ((bosluk_x == movement_x && abs(bosluk_y - movement_y) == 1) ||
        (bosluk_y == movement_y && abs(bosluk_x - movement_x) == 1))
    {
        // BOSLUKX FALAN ONLARI YANLIŞLIKLA TAM TERSİ YAPTIM Xİ Y YYİ X GİBİ DÜŞÜN Bİ DE +-LERE DE DİKKAT ET
        int temp;
        switch (yon)
        {
        case UP1:
        case UP:
            if ((bosluk_y == movement_y && (bosluk_x - movement_x) == -1))
            {
                temp = puzzle[movement_x][movement_y];
                puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                puzzle[bosluk_x][bosluk_y] = temp;
            }
            else
            {
                printf("Invalid move.\n");
            }
            break;
        case DOWN1:
        case DOWN:
            if ((bosluk_y == movement_y && (bosluk_x - movement_x) == 1))
            {
                temp = puzzle[movement_x][movement_y];
                puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                puzzle[bosluk_x][bosluk_y] = temp;
            }
            else
            {
                printf("Invalid move.\n");
            }
            break;
        case LEFT1:
        case LEFT:
            if ((bosluk_x == movement_x && (bosluk_y - movement_y) == -1))
            {
                temp = puzzle[movement_x][movement_y];
                puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                puzzle[bosluk_x][bosluk_y] = temp;
            }
            else
            {
                printf("Invalid move.\n");
            }
            break;
        case RIGHT1:
        case RIGHT:
            if ((bosluk_x == movement_x && (bosluk_y - movement_y) == 1))
            {
                temp = puzzle[movement_x][movement_y];
                puzzle[movement_x][movement_y] = puzzle[bosluk_x][bosluk_y];
                puzzle[bosluk_x][bosluk_y] = temp;
            }
            else
            {
                printf("Invalid move.\n");
            }
            break;
        default:
            printf("Invalid move!\n");
            break;
        }
    }
    else
    {
        printf("Invalid move!\n");
    }
    return 0;
}

int case1(int movement_x, int movement_y, int puzzle[3][3], int sayi,int score)
{
    printf("Play game as a user\n");
    create_puzzle(puzzle);
    show_puzzle(puzzle,score);
    int baksana;
    do
    {
        baksana = checkfun(puzzle, sayi,score);
    } while (baksana == 1);
    int write_best_score(int score);
    return 0;
}

int case2(int movement_x, int movement_y, int puzzle[3][3], int sayi, int score)
{
    printf("Finish the game with PC\n");
    create_puzzle(puzzle);
    show_puzzle(puzzle, score);
    
    while (!checkisittrue(puzzle))
    {
        int empty_x, empty_y;
        // Find the coordinates of the empty slot ('_')
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (puzzle[i][j] == '_')
                {
                    empty_x = i;
                    empty_y = j;
                    break;
                }
            }
        }
        
        // Generate a random move
        char move;
        do {
            move = (char)('u' + rand() % 4); // 'u', 'd', 'l', 'r'
        } while (!((move == 'u' && empty_x > 0) || (move == 'd' && empty_x < 2) ||
                   (move == 'l' && empty_y > 0) || (move == 'r' && empty_y < 2)));
        
        // Perform the move
        switch (move)
        {
            case 'u':
                puzzle[empty_x][empty_y] = puzzle[empty_x - 1][empty_y];
                puzzle[empty_x - 1][empty_y] = '_';
                break;
            case 'd':
                puzzle[empty_x][empty_y] = puzzle[empty_x + 1][empty_y];
                puzzle[empty_x + 1][empty_y] = '_';
                break;
            case 'l':
                puzzle[empty_x][empty_y] = puzzle[empty_x][empty_y - 1];
                puzzle[empty_x][empty_y - 1] = '_';
                break;
            case 'r':
                puzzle[empty_x][empty_y] = puzzle[empty_x][empty_y + 1];
                puzzle[empty_x][empty_y + 1] = '_';
                break;
        }
        
        score = show_puzzle(puzzle, score);
    }
    
    printf("Congratulations!\n");
    score = write_best_score(score);
    
    return 0;
}


void menu()
{   
    int score=100;
    int movement_x;
    int movement_y;
    int puzzle[3][3];
    int sayi;
    int choice;
    int numara;
    printf("\nWelcome to the 8-Puzzle Game\n");
    printf("1. Play game as a user\n");
    printf("2. Finish the game with PC\n");
    printf("3. Show the best score\n");
    printf("4. Exit\n");

    printf("\nEnter your choice: \n");
    do
    {
        scanf("%d", &choice);
        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice, re-enter again: ");
        }
    } while (choice < 1 || choice > 4);

    switch (choice)
    {
    case 1:
    //burada kullanıcıdan alınan inputlarla bulmacayı çözmeli
        case1(movement_x, movement_y, puzzle, sayi,score);
        menu();
        break;
    case 2:
    //burada bilgisayar random hareketler yaparak bulmacayı çözmeli
        case2(movement_x, movement_y, puzzle, sayi,score);
        menu();
        break;
    case 3:
    //burada en iyi skoru göstermeli
        printf("Show the best score\n");
        int show;
        show = write_best_score(score);
        printf("Best score is %d\n", show);
        menu();
        break;
    case 4:
    //burada programdan çıkmalı
        printf("Exit\n");
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}
