#include "bsq.h"

//int fscanf(FILE *stream, const char *format, ...);return value = number of items written/line_len; 
// return on error: negative value (usually EOF); ... = variable arguments (like printf)
//SEQUENCE
// 1. line_
// 2. check if parsed fields == 4
// 3. check if num_ ine is <=0
// 4. chars are not same
// 5,6,7. make sure char are printable (between 32 and 126)
//test with a input using tab


int load_elements(FILE* input,t_elements* elements)//Parse header
{
    int parsed_fields = fscanf(input, "%d %c %c %c", &(elements->num_lines), &(elements->empty), &(elements->obstacle), &(elements->full));
    if (parsed_fields != 4)
        return (-1);
    if (elements->num_lines <= 0)
        return (-1);
    if (elements->obstacle == elements->empty || elements->obstacle == elements->full || elements->full == elements->empty)
        return (-1);
    if (elements->obstacle < 32 || elements->obstacle > 126)
        return (-1);
    if (elements->empty < 32 || elements->empty > 126)
        return (-1);
    if (elements->full < 32 || elements->full > 126)
        return (-1);
    return (0);
}


void free_map(char** array)
{  
    int i = 0;
    if (array)
    {
        while(array[i] != NULL)
        {
            if (array[i])
                free(array[i]);
            i++;
        }
        free(array);
    }

}

//1.malloc and protect 2. while loop ....
char* ft_substr(char* given_str, int start, int len)
{
    char* str = (char*) malloc(len + 1);
    if (!str)
        return (NULL);
    int i = 0;
    int j = 0;
    while (given_str[i])
    {
        if (i >= start && j < len)
        {
            str[j] = given_str[i];
            j++;
        }
        i++;
    }
    str[j]= '\0';
    return (str);
}

int validate_map_chars(char** map, char c1, char c2)
{
    int i = 0;
    while (map[i])//my nested (1)
    {
        int j = 0;
        while(map[i][j] != '\0')
        {
            if ((map[i][j] != c1) && (map[i][j] != c2))
                return(-1); 
            j++;
        }
        i++;
    }
    return (0);
}
//map->grid= a pointer to an array of char*
//map->grid[i]= points to each row of the map
//map->grid[0] → first row
//map->grid[height - 1] → last row


//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
//IMPORTANT: getline returns the number of characters including the newline if it exists.
//   lineptr → address of buffer (allocated/expanded by getline)
//   n       → address of buffer size
//   stream  → FILE* to read from
// return:
//   >= 0    → number of chars read (including '\n')
//   -1      → error or EOF


//SEQUENCE:
// 1. set num_lines as map height
// 2. malloc for grid and protect
//3. mark the end as null
//4. initialize a string to store lines from getline
//5. setup len for getline
//6. use getline to // Skip the newline leftover from fscanf
//7. make a for loop to iterate through all rows(meaning map->height)
////7.1. use getline to line_len into line_len and free line and map in case of failure
//9. remove trailing newline- why?Because getline includes \n. so:width comparison is correct map rows don’t contain \n
//10. If a row is empty (after removing '\n') and it's NOT the last row,the map is invalid (empty lines in the middle- not allowed)
//11. put the line in map->grid[i] using ft_substr and PROTECT substr
//12. Store the length of first row (i = 0) (line_len) and set map->width.
//13. for the nexts (else), if width does not match, ditch
//14. validate map chars by sending grid, empty and obstacles

int load_map(FILE* input, t_map* map, t_elements* elements)
{
    map->height = elements->num_lines;
    map->grid = (char**)malloc((map->height + 1) * sizeof(char*));//****height+1 must needed for NULL****
    if (!map->grid)
        return(-1);
    map->grid[map->height] = NULL; //***mark the end of the array (so you can loop until NULL)***
    char* line = NULL;
    size_t len = 0;
    if (getline(&line, &len, input) == -1)// Skip the leftover newline from the header line
    {
        free_map(map->grid);
        return (-1);
    }
    for (int i = 0; i <map->height; i++)//1.getline-2.remove his'\n'-3.check if middle empty-4.copy line in grid-5.set width 6.check width
    {
        ssize_t line_len = getline(&line, &len, input);
        if (line_len == -1)
        {
            free(line);//free it cause getline allocated it for me
            free_map(map->grid);
            return (-1);
        }
        if (line_len > 0 && line[line_len - 1] == '\n') //remove \n so width is correct
            line_len--;
        if (line_len <= 0 && i != map->height - 1)//forbid empty line in the middle row but tolerate at last index
        {
            free(line);
            free_map(map->grid);
            return(-1);
        }
        map->grid[i] = ft_substr(line, 0, line_len);
        if (!map->grid[i])
        {
            free(line);
            free_map(map->grid);
            return(-1);
        }
        if (i == 0) //in the first iteration
            map->width = line_len; //set the width
        else //for all other rows in the next iterations
        {
            if (map->width != line_len)//invalidate other line_len 
            {
                free(line);
                free_map(map->grid);
                return (-1);
            }
        }
    }
    if(validate_map_chars(map->grid, elements->empty, elements->obstacle)== -1)
    {
        free(line);
        free_map(map->grid);
        return(-1);
    }
    free(line);//use of line ended 
    return (0);
}

int find_min(int n1, int n2, int n3)
{
    int min = n1;
    if (n2 < min)
        min = n2;
    if (n3 < min)
        min = n3;
    return (min);
}

void find_biggst_sq(t_map* map, t_square* square, t_elements* elements)//THE DP ALGORITHM!!
{
    // Create a DP matrix/shadow map with same dimensions as map and set ALL to 0
    int matrix[map->height][map->width];
    for(int i = 0; i < map->height; i++)//nested loop(2)
    {
        for(int j = 0; j < map->width; j++)//set all to zero
            matrix[i][j] = 0;
    }
    for(int i = 0; i < map->height; i++)//iterate again //nested loop(3)
    {
        for(int j = 0; j < map->width; j++)//1.make obstacle 0. 2.make first row and col==1 3.find min 4.increase min+1 5.update sq
        {
            if(map->grid[i][j] == elements->obstacle)
                matrix[i][j] = 0; //obs cannot be part of square
            else if(i == 0 || j == 0) //cells in the first row or column can only form a square of size 1
                matrix[i][j] = 1; 
            else
            {
                int min = find_min(matrix[i - 1][j], matrix[i - 1][j - 1], matrix[i][j - 1]);//top, left and top-left
                matrix[i][j] = min + 1;
            }
            if (matrix[i][j] > square-> size) //if current cell is bigger than 
            {
                //update square
                square->size = matrix[i][j];
                square->i = i - matrix[i][j] + 1;
                square->j = j - matrix[i][j] + 1;
                //square->i and square->j point to the top-left corner of the largest square found.
            }
        }
    }
}

//Grow the smallest sq

void print_filled_square(t_map* map, t_square* square, t_elements* element)
{
    for (int i = square->i; i < square->i + square->size; i++)//my mested loop(4)
    {
        for(int j = square->j; j < square->j + square->size; j++)
        {
            if ((i < map->height) && (j < map->width)) 
                map->grid[i][j] = element->full;///fill
        }
    }
    for (int i = 0; i < map->height; i++)// print each line by fputs
    {
        fputs(map->grid[i], stdout);
        fputc('\n', stdout);
    }
}


//SEQUENCE:
//1. load_elements
//2.load_map
//3. find_biggst_square
//4. print_filled_sq
//5.free_map

int execute_bsq(FILE* input)
{
    t_elements elements;
    t_map map;
    t_square square;
    if (load_elements(input, &elements) == -1)//parse header
        return (-1);
    if (load_map(input, &map, &elements) == -1)
        return (-1);
    square.size = 0; square.i = 0; square.j = 0;
    find_biggst_sq(&map, &square, &elements);
    print_filled_square(&map, &square, &elements);
    free_map(map.grid);
    return(0);
}

int convert_file_pointer(char* given_file)
{
    // Open the given_file (read-only mode) in FILE* input
    FILE* input = fopen(given_file, "r");
    if (!input) 
        return(-1);
    int ret = 0;
    ret = execute_bsq(input);
    fclose(input);
    return (ret);
}

//FILE* is a stream handle to where the map is coming from.
//FILE is a library-defined "opaque" struct type(not a struct), used via pointer only
//It lets the same function work for: input input and standard input both
//It can point to: a input opened with fopen(), stdin, stdout / stderr


// FILE* fopen(const char *pathname, const char *mode);
// pathname → input given_file
// mode → "r", "w", "a", etc.
// returns FILE * on success
// returns NULL on failure