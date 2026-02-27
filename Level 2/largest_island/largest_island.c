/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   largest_island.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 15:05:33 by rshaheen      #+#    #+#                 */
/*   Updated: 2026/02/25 15:16:57 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h> //for open
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


//struct stat info; is a structure that holds metadata about a file
//when used in fstat(), the info struct gets filled with details about the file referred to by the file descriptor fd. 
//This metadata is not the file’s contents, just information about the file itself. Some useful fields in struct stat are:
//info.st_size → size of the file in bytes. You use this to know how much memory to allocate before reading the file.


int count_height(char *str)
{
    if(!str || str[0]== '\0')
        return (0);
    int count = 0;
    int i = 0;
    while(str[i])
    {
        if(str[i]== '\n')
            count++;
        i++;
    }
    if((i > 0) && (str[i - 1]!= '\n'))//if no newline in the last lline
        count++;
    return(count);
}

int count_wid(char* str)
{
    int i = 0;
    while(str[i] && str[i] != '\n')
    {
        i++;
    }
    return(i);
}

char *read_file(int fd)
{
    struct stat info;
    if(fstat(fd, &info) < 0)
        return(NULL);
    char *str = malloc(info.st_size + 1);//because read needs malloc
    if(!str)
        return(NULL);
    ssize_t bytes_read = read(fd, str, info.st_size);
    if (bytes_read < 0)
    {
        free(str);
        return(NULL);
    }
    str[bytes_read] = '\0';
    return(str);
}

int validate_map(char *str, int height, int width)
{
    if (!str || height <= 0 || width <= 0)
        return -1;
    int k = 0;
    //1. validate chars
    for(int i = 0; i < height; i++)// 1. validate chars(by nested); 2. all line's(minus the last) \n, 3. last line's n
    {
        for(int j = 0; j < width; j++)
        {
            if(str[k] != 'X' && str[k] != '.')//validate chars within one line
                return(-1);
            k++;
        }
        if(i < height - 1)//all rows except last one
        {
            if(str[k] != '\n')//must end with newline
                return(-1);
            k++;//newline found, skip it
        }
        else//last line
        {
            if(str[k] == '\n')
            {
                k++;//only one \n allowed
                if(str[k] != '\0')
                    return(-1);// now must end
            }
            else if(str[k] != '\0')//no newline, must end here
                return(-1);
        }
    }   
    return (0);
}

void free_grid(char **grid, int height)
{
    if(grid)
    {
        for(int i = 0; i < height; i++)
        {
            if(grid[i])
                free(grid[i]);
        }
        free(grid);
    }
}

char **make_grid(char *str, int height, int width)
{
    char **grid = (char**)malloc(height * sizeof(char*));
    if(!grid)
        return(NULL);
    for(int i = 0; i < height; i++)
    {
        grid[i] = (char*)malloc(width * sizeof(char));
        if(!grid[i])
        {
            free_grid(grid, height);
            return(NULL);
        }
    }
    return(grid);
}

void fill_grid(char **grid, char *str, int height, int width)
{
    int k = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            grid[i][j] = str[k];
            k++;
        }
        grid[i][width] = '\0';// end the row as a proper C string
        if(str[k] == '\n')
            k++;//skip and move to next row
    }
}

int flood_fill(char**grid, int height, int width, int i, int j)
{
    if(i < 0 || i >= height || j < 0 || j >= width)
        return(0);
    if(grid[i][j] != 'X')
        return(0);
    grid[i][j] = '*';
    int count = 1;
    count += flood_fill(grid, height, width, i + 1, j);
    count += flood_fill(grid, height, width, i - 1, j);
    count += flood_fill(grid, height, width, i, j + 1);
    count += flood_fill(grid, height, width, i, j - 1);
    return(count);
}

int find_max_island(char **grid, int height, int width)
{
    int max_island = 0;
    int size = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(grid[i][j] == 'X')
            size = flood_fill(grid, height, width, i, j);
            if(size > max_island)
                max_island = size;
        }
    }
    return(max_island);
}

void ft_putnbr(int n)
{
    char c;
    if(n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        write(1, "No input\n", 10);

        return(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        return(1);
    char *str = read_file(fd);
    {
        if(!str)
        {
            close(fd);
            write(1, "cannot read file\n", 18);
            return(1);
        }
    }
    int height = count_height(str);
    int width = count_wid(str);
    if (validate_map(str, height, width) == -1)
    {
        free(str);
        close(fd);
        write(1, "Map Error\n", 10);
        return(1);
    }
    char **grid = make_grid(str, height, width);
    if(!grid)
    {
        free(str);
        close(fd);
        write(1, "Map Error\n", 10);
        return(1);
    }
    fill_grid(grid, str, height, width);
    int max_island = find_max_island(grid, height, width);
    ft_putnbr(max_island);
    // printf("%s", str);
    // printf("%d\n", height);
    // printf("%d\n", width);
    write(1, "\n", 1);
    free(str);
    close(fd);
    free_grid(grid, height);
    return(0);     
}


//int open(const char *pathname, int flags, mode_t mode);
// pathname → path of the file
// flags → how you want to open it (read/write, create, etc.)
// mode → file permissions (used only if creating a new file)
// returns → a file descriptor (integer ≥ 0) on success, -1 on error

// Common Flags
// O_RDONLY → open for reading only
// O_WRONLY → open for writing only
// O_RDWR → read and write
// O_CREAT → create file if it doesn’t exist
// O_TRUNC → truncate file to zero length
// O_APPEND → append at the end

// int fstat(int fd, struct stat *str);
// fd → file descriptor (from open() or pipe())
// str → pointer to struct stat where file info will be stored
// returns → 0 on success, -1 on error


// ssize_t read(int fd, void *str, size_t count);
// fd → file descriptor (from open())
// str → buffer where the data will be stored
// count → number of bytes to read
// returns → number of bytes actually read, 0 if end of file, -1 on error
