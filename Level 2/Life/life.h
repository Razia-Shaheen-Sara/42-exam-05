#ifndef LIFE_H
#define LIFE_H

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct s_game
{
    int width;
    int height;
    int iter;
    char dead;
    char alive;
    int i;
    int j;
    int draw;
    char **board;
}t_game;


#endif

//atoi → <stdlib.h>
//read → <unistd.h>
//putchar → <stdio.h>
//malloc → <stdlib.h>
//calloc → <stdlib.h>
//realloc → <stdlib.h>
//free → <stdlib.h>

//iterations = how many times the board updates using these rules/number of rounds we play
//rules:
//For each cell, look at its 8 neighbors.
//Alive cell with <2 or >3 alive neighbors → dies
//Alive cell with 2 or 3 alive neighbors → lives
//Dead cell with exactly 3 alive neighbors → becomes alive

//pen movement: collected by key press w,a,s,d and x
//it has draw on/off button (x)
//begins at top left(0,0) - then receives which way to draw from input
//it basically draws the initial board of alive cells on which we will play


//EXAMPLE:
// so for x d d s x
//x → pen down/ draw
//d → move right, draw alive
//d → move right, draw alive
//s → move down, draw alive
//0 is alive
//x → pen up/ stop draw will make the following board--
//O O O _ _
//_ _ O _ _
//_ _ _ _ _
//_ _ _ _ _
//_ _ _ _ _


//iteration 1:
//O O O _ _      → becomes O O O _ _
//_ _ O _ _      → becomes O O O _ _
//_ _ _ _ _      → becomes _ O _ _ _
//_ _ _ _ _      → unchanged
//_ _ _ _ _      → unchanged

//iteration 2:
//O O O _ _      → O O O _ _
//O O O _ _      → O _ O _ _   //middle one dies because more than 3 neighbours are alive
//_ O _ _ _      → _ O _ _ _
//_ _ _ _ _      → unchanged
//_ _ _ _ _      → unchanged

