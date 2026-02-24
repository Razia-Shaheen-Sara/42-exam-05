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
        game->board[i] = (char*)malloc(game->width * sizeof(char));
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

// #include "life.h"
// void free_board(t_game* game)//getting the whole game because i also need height
// {
//     if (game->board)
//     {
//         for(int i = 0; i < game->height; i++)
//         {
//             if(game->board[i])
//                 free(game->board[i]);
//         }
//         free(game->board);
//         game->board = NULL;
//     }
// }

// int make_board(t_game* game, char**argv) //kill all in the beginnning
// {
//     game->width = atoi(argv[1]);
//     game->height = atoi(argv[2]);
//     game->iterations = atoi(argv[3]);
//     game->alive = 'O';
//     game->dead = ' ';
//     game->i = 0;
//     game->j = 0;
//     game->draw = 0;
//     game->board = (char**)malloc(game->height * sizeof(char*));
//     if (!game->board)
//         return (-1);
//     for (int i = 0; i < game->height; i++)// 2 purpose
//     {
//         game->board[i] = (char*)malloc(game->width * sizeof(char));
//         if(!game->board[i])
//         {
//             free_board(game);
//             return(-1);
//         }
//         for (int j = 0; j < game->width; j++)
//         {
//             game->board[i][j]= ' ';
//         }
//     }
//     return (0);

// }

// void handle_key(t_game* game) //only alive if is_valid_cmd is 0(valid) and draw mode on
// {
//     char c;
//     int is_valid_cmd;
//     //the whole keyboard activity will be inside while
//     while (read(STDIN_FILENO, &c, 1) == 1)//Reads one character from stdin into  buffer c.
//     {
//         is_valid_cmd = 0;//valid 
//         switch (c)//checks which key was pressed
//         {
//             case 'w':
//                 if(game->i > 0)
//                     game->i--;//matrix starts at i=0(top row, so decrease ONLY when not top row i.e. i > 0)
//                 break;
//             case 's':
//                 if(game->i < (game->height - 1))
//                     game->i++;
//                 break;
//             case 'd':
//                 if(game->j < (game->width - 1))
//                     game->j++;
//                 break;
//             case 'a':
//                 if(game->j > 0)
//                     game->j--;
//                 break;
//             case 'x':
//                 game->draw = !game->draw; //just flip, it will go both ways-- now it is a toggle
//                 break;
//             default:
//                 is_valid_cmd = 1;//invalid
//                 break;
//         }
//         //out of switch but inside while
//         //Valid row indexes: 0 to height - 1
//         //Valid column indexes: 0 to width - 1
//         //if draw mode on and is_valid_cmd is 0 (valid)--- if game->i and game->j within bounds-- then game->alive
//         if(game->draw && (is_valid_cmd == 0))
//         {
//             if((game->i >= 0) && (game->i < game-> height) && (game->j >= 0) && (game->j < game->width))
//                 game->board[game->i][game->j] = game->alive;
//         }
//     }
// }

// //Explanation:
// //int neighbor_row = i + di;
// //int neighbour_col = j + dj;
// // moving:
// //di = -1 → one row up
// //di = 0 → same row
// //di = 1 → one row down
// //dj = -1 → one column left
// //dj = 0 → same column
// //dj = 1 → one column right

// int count_neighbours(t_game* game, int i, int j)
// {
//     int count = 0; //alive neighbour count = 0
//     for (int di = -1; di < 2; di++)//nested(2)
//     {
//         for (int dj = -1; dj < 2; dj++)
//         {
//             // Skip the cell itself; we only want neighbors
//             if (di == 0 && dj == 0)
//                 continue;
//             // Calculate the neighbor's coordinates
//             int neighbor_row = i + di; //row index of neighbour
//             int neighbour_col = j + dj; //column index for neighbour

//             // Check that neighbor is inside the board boundaries
//             if(neighbor_row >= 0 && neighbour_col >= 0 &&
//                 neighbor_row < game->height && neighbour_col < game->width)
//             {
//                 // If the neighbor is alive, increment the count
//                 if (game->board[neighbor_row][neighbour_col] == game->alive)
//                     count++;
//             }
//         }
//     }
//     return(count);
// }

// int play(t_game* game)
// {
//     char** temp = (char**)malloc(game->height * sizeof(char*));//cause board changes in every round/iteration
//     if (!temp)
//         return(-1);
//     for(int i = 0; i < game->height; i++)
//     {
//         temp[i] = (char*)malloc(game->width * sizeof(char));
//         if (!temp[i])
//         {
//             // Free all previously allocated rows of temp
//             for(int k = 0; k < i; k++)
//                 free(temp[k]);
//             free(temp);
//             return(-1);  
//         }
//     }
//     // Loop over each cell of the board
//     for (int i = 0; i < game->height; i++)//nested(1)
//     {
//         for (int j = 0; j < game->width; j++)//count_neib
//         {
//              // Count the number of alive neighbors for the current cell
//             int neighbours = count_neighbours(game, i, j);
//             if (game->board[i][j] == game->alive)// If current cell is alive
//             {
//                 if (neighbours == 2 || neighbours == 3)// Survives if 2 or 3 neighbors
//                     temp[i][j] = game->alive; // stays alive
//                 else
//                     temp[i][j] = game->dead;
//             }
//             else //cureent cell is dead
//             {
//                 if(neighbours == 3)
//                     temp[i][j] = game->alive;//born
//                 else
//                     temp[i][j] = game->dead;//stay dead
                
//             }
//         }
//     }
//     free_board(game); //free old board
//     game->board = temp;
//     return (0);
// }

// //Alive cell stays alive → 2 or 3 neighbors
// //Dead cell becomes alive → exactly 3 neighbors

// void print_board(t_game* game)
// {
//     for(int i = 0; i < game->height; i++)//nested(3)
//     {
//         for(int j = 0; j < game->width; j++)
//         {
//             putchar(game->board[i][j]);
//         }
//         putchar('\n');
//     }
// }

// int main(int argc, char**argv)
// {
//     if(argc != 4)
//         return (1);
//     t_game game;//just make a game, no poiter to anything
//     if(make_board(&game, argv)== -1)//send game ref and argv
//         return(1);
//     handle_key(&game);
//     for (int i = 0; i < game.iterations; i++)
//     {
//         if(play(&game) == -1)
//         {
//             free_board(&game);
//             return (1);
//         }
//     }
//     print_board(&game);
//     free_board(&game);
//     return (0);
// }