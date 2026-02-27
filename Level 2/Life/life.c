#include "life.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void free_grid(char** grid, int height)
{
    if (grid)
    {
        for(int i = 0; i < height; i++)
        {
            if(grid[i])
                free(grid[i]);
        }
        free(grid);
        grid = NULL;
    }
}

int make_board(t_game *game, char** argv)
{
    game->i = 0;
    game->j = 0;
    game->draw = 0;
    game->width = atoi(argv[1]);
    game->height = atoi(argv[2]);
    game->iter = atoi(argv[3]);
    game->alive = '0';
    game->dead = ' ';
    game->board = (char**)malloc(game->height * sizeof(char*));
    if(!game->board)
        return (-1);
    for(int i = 0; i < game->height; i++)
    {
        game->board[i] = (char*)malloc((game->width + 1) * sizeof(char));
        if (!game->board[i])
        {
            free_grid(game->board, game->height);
            return(-1);
        }
        for(int j = 0; j < game->width; j++)
        {
            game->board[i][j] = ' ';//initialize whole board to dead
        }
    }
    return (0);
}

// //ssize_t read(int fd, void *buf, size_t count);
// //switch (c)
// //Checks which key was pressed: and decides whether to move depending on BOUNDS
// //THINK BOUNDS: i is up-down; j = left-right
// //'w' →  up (i--)
// //'s' → down (i++)
// //'a' → left (j--)
// //'d' → right (j++)
// //'x' → draw mode (on/off)

void handle_key(t_game *game)
{
    char c;
    int is_valid_cmd;
    while(read(STDIN_FILENO, &c, 1) == 1)
    {
        is_valid_cmd = 0;
        switch(c)
        {
            case 'w':
                if(game->i >= 1)
                    game->i--;
                break;
            case 's':
                if(game->i < game->height - 1)
                    game->i++;
                break;
            case 'a':
                if(game->j >= 1)
                    game->j--;
                break;
            case 'd':
                if(game->j < game->width - 1)
                    game->j++;
                break;
            case 'x':
                game-> draw = !game->draw;
                break;
            default:
                is_valid_cmd = 1;
                break;
        }
        if((game->draw) && (is_valid_cmd == 0))
        {
            if((game->i >= 0) && (game->i < game->height) && (game->j >= 0) && (game->j < game->width))
                game->board[game->i][game->j] = game->alive;
        } 
    }
}

int count_neig(t_game *game, int i, int j)
{
    int count = 0;
    for(int di = -1; di < 2; di++)
    {
        for(int dj = -1; dj < 2; dj++)
        {
            if (di == 0 && dj == 0)
                continue;
            int nei_row = i + di;
            int nei_col = j + dj;
            if (nei_row >= 0 && nei_row < game->height && nei_col >= 0 && nei_col < game->width)
            {
                if(game->board[nei_row][nei_col] == game-> alive)
                    count++;
            }
        }
    }
    return(count);
}

int play(t_game *game)
{   
    char**temp = (char**)malloc(game->height * sizeof(char*));
    if(!temp)
        return(-1);
    for(int i = 0; i < game->height; i++)
    {
        temp[i] = (char*)malloc(game->width * sizeof(char));
        if(!temp[i])
        {
            free_grid(temp, game->height);
            return(-1);
        }
    }
    for(int i = 0; i < game->height; i++)
    {
        for(int j = 0; j < game->width; j++)
        {
            int neighbr = count_neig(game, i, j);
            if(game->board[i][j] == game->alive)
            {
                if(neighbr == 3 || neighbr == 2)
                    temp[i][j] = game->alive;
                else
                    temp[i][j] = game->dead;
            } 
            else
            {
                if(neighbr == 3)
                    temp[i][j] = game->alive;
                else
                    temp[i][j] = game->dead;
            }
        } 
    }
    free_grid(game->board, game->height);
    game->board = temp;
    return(0);
}

void print_board(t_game *game)
{
    for(int i = 0; i < game->height; i++)
    {
        for(int j = 0; j < game->width; j++)
        {
            putchar(game->board[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char** argv)
{
    if(argc != 4)
        return(1);
    t_game game;
    if (make_board(&game, argv) == -1)
      return(-1);
    handle_key(&game);
    for(int i = 0; i < game.iter; i++)
    {
        if (play(&game) == -1)
        {
          free_grid(game.board, game.height);
          return(-1);
        }
    }
    print_board(&game);
    free_grid(game.board, game.height);
    return(0);
}
