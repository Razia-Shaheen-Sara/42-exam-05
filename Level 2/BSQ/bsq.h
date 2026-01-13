#ifndef BSQ_H
#define BSQ_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_elements
{
    int num_lines;
    char empty;
    char obstacle;
    char full;

}t_elements;

typedef struct s_map
{
    char** grid;
    int width;
    int height;
}t_map;

typedef struct s_square
{
    int size;
    int i;
    int j;
}t_square;

int execute_bsq(FILE* file);
int convert_file_pointer(char* name);
//FILE *file is a stream handle to where the map is coming from.
//FILE is a library-defined "opaque" struct type(not a struct), used via pointer only
//It lets the same function work for: file input and standard input both
//It can point to: a file opened with fopen(), stdin, stdout / stderr
#endif