#include <unistd.h>
#include <fcntl.h> //for open
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

char* read_file(int fd)
{
    struct stat info;
    if(fstat(fd,  info) < 0)
        return (NULL);
    char* str = malloc(info.st_size + 1);
    if (!str)
        return (NULL);
    ssize_t bytes_read = read(fd, str, info.st_size);
    close(fd);//always close after reading
    if(bytes_read <= 0)
    {
        free(str);
        return (NULL);
    }
    str[bytes_read] = '\0';
    return (str);
}
int count_rows(char* str)
{
    int rows = 0;
    for (int i = 0; str[i]!= 0; i++)
    {
        if(str[i] == '\n')
            rows++;
    }
    return (rows);
}

int count_col(char* str)
{
    int i = 0;
    while(str[i]!= 0 && str[i]!= '\n')
    i++;
    return(i);
}
char** make_grid(int row, int col)
{
    char**grid = (char**)malloc(row * sizeof(char*));
    if (!grid)
        return (NULL);
    for (int i = 0; i < row; i++)
    {
        grid[i] = (char*)malloc(col + 1);//Each row gets cols + 1 for null terminator
        if (!grid[i])
        {  
            for(int j = 0; j < i; j++)
                free(grid[j]);
            free(grid);
            return(NULL);
        }

    }
    return (grid);
}



int flood_fill(char** grid, int row, int col, int i, int j)
{
    if(i < 0 || i >= row || j < 0 || j >= col)//bound check
        return (0);
    if(grid[i][j] != 'X')//make sure to process only given char
        return (0);
    grid[i][j] = '*';//mark
    int count = 1;
    count += flood_fill(grid, row, col, i + 1, j); //down
    count += flood_fill(grid, row, col, i - 1, j); //up
    count += flood_fill(grid, row, col, i, j - 1); //left
    count += flood_fill(grid, row, col, i, j + 1); //right
    return(count);

}

int execute_li(char**grid, int row, int col)
{
    int max_island = 0;
    int size = 0;
    for (int i = 0; i < row; i++) //nested
    {
        for(int j = 0; j < col; j++)
        {
            if(grid[i][j] == 'X')// run flood fill from this cell and update maximum island size
            {
                size = flood_fill(grid, row, col, i, j);
                if(size > max_island)//check biggest and update
                    max_island = size;
            }       
        }
    }
    return (max_island);
}

void ft_putnbr(int n)
{
    char c;
    if(n > 9)
        ft_putnbr(n/10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}
int main(int argc, char**argv)
{
    if (argc!= 2)
    {
        write(1, "No input file\n", 14);
        return(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        write(1, "cannot open file\n", 17);
        return(1);
    }
    char* str = read_file(fd);
    if(!str)
    {
        close(fd);
        write(1, "cannot open file\n", 17);
        return(1);
    }
    int rows = count_rows(str);
    int colm = count_col(str);
    char** grid = make_grid(rows, colm);
    if (!grid)
    {
        write(1, "Map error\n", 10);
        return (1);
    }
    if(fill_grid() < 0)
    {
        free(str);
        free_grid()
        write(1, "Map error\n", 10);
        return (1);
    }
    
    // int largest_island = execute_li(grid, rows, colm);
    // ft_putnbr(largest_island);
    // write(1, "\n", 1);
    free(str);
    close(fd);
    return (0);
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

// int fstat(int fd, struct stat *buf);
// fd → file descriptor (from open() or pipe())
// buf → pointer to struct stat where file info will be stored
// returns → 0 on success, -1 on error


// ssize_t read(int fd, void *buf, size_t count);
// fd → file descriptor (from open())
// buf → buffer where the data will be stored
// count → number of bytes to read
// returns → number of bytes actually read, 0 if end of file, -1 on error