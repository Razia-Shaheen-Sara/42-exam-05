#ifndef LIFE_H
#define LIFE_H

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct s_game
{
    int width;
    int height;
    int iterations;
    char dead;
    char alive;
    int i;
    int j;
    int draw;
    char **board;
}t_game;


#endif