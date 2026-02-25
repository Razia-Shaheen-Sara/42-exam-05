/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_island.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 15:05:07 by rshaheen      #+#    #+#                 */
/*   Updated: 2026/02/25 15:09:23 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "count_island.h"

char *read_file(int fd)
{
	char *str = malloc(1025);
	if(str == NULL)
		return (NULL);
	int bytes_read = read(fd, str, 1024);
	if (bytes_read == -1)
	{
		free(str);
		return (NULL);
	}
	str[bytes_read] = '\0';
	return (str);
}

int count_height(char *str)
{
	int count = 0;
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	if(i > 0 && str[i - 1] != '\n')
		count++;
	return (count);
}
int count_width(char *str)
{
	int i = 0;
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

int validate_map(char *str, int height, int width)
{
	if(!str || str[0] == '\0' || height <= 0 || width <= 0)
		return (-1);
	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (str[k] != 'X' && str[k] != '.')
				return (-1);
			k++;
		}
		if (i < height - 1)//all lines except the last one
		{
			if (str[k] != '\n')//must end with newline
				return (-1);
			k++;//go to next line
		}
		else //last line
		{
			if (str[k] == '\n')//if last line has a newline, only one allowed
			{
				k++;//skip the newline
				if (str[k] != '\0')//after skipping newline, must end
					return (-1);
			}
			else if (str[k] != '\0')//if no newline, must end here
				return (-1);
		}
	}
	return (0);
}
void free_grid(char **grid, int height)
{
	if (grid)
	{
		for (int i = 0; i < height; i++)
		{
			if (grid[i])
				free(grid[i]);
		}
		free(grid);
	}
}

char **make_grid(char *str, int height, int width)
{
	char **grid = (char **)malloc(height * sizeof(char *));
	if (!grid)
		return (NULL);
	for (int i = 0; i < height; i++)
	{
		grid[i] = (char *)malloc((width + 1) * sizeof(char)); // +1 for null terminator
		if (!grid[i])
		{
			free_grid(grid, i);
			return (NULL);
		}
	}
	return (grid);
}

void fill_grid(char **grid, char *str, int height, int width)
{
	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			grid[i][j] = str[k];
			k++;
		}
		grid[i][width] = '\0'; // end the row as a proper C string
		if (str[k] == '\n')
			k++; // skip and move to next row
	}
}

void flood_fill(char **grid, int height, int width, int i, int j, char id)
{
	if (i < 0 || i >= height || j < 0 || j >= width || grid[i][j] != 'X')
		return;
	grid[i][j] = id; // mark the cell with the island ID
	flood_fill(grid, height, width, i - 1, j, id); // up
	flood_fill(grid, height, width, i + 1, j, id); // down
	flood_fill(grid, height, width, i, j - 1, id); // left
	flood_fill(grid, height, width, i, j + 1, id); // right
}

void mark_island(char **grid, int height, int width)
{
	char id = '1';
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j] == 'X')
			{
				flood_fill(grid, height, width, i, j, id);
				id++;
			}
		}
	}
}

void print_grid(char **grid, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			write(1, &grid[i][j], 1);
		}
		write(1, "\n", 1);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1,"\n", 1);
		return(1);
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1,"\n", 1);
		return(1);
	}
	char *str = read_file(fd);
	if(str == NULL)
	{
		write(1,"\n", 1);
		return(1);
	}
	//printf("%s\n", str);
	int height = count_height(str);
	int width = count_width(str);
	// printf("%d\n", height);
	// printf("%d\n", width);
	if(validate_map(str, height, width)== -1)
	{
		free(str);
		close(fd);
		write(1,"\n", 1);
		return(1);
	}
	//printf("%s\n", str);//check if str is still valid after validation
	char **grid = make_grid(str, height, width);
	if(!grid)
	{
		free(str);
		close(fd);
		write(1,"\n", 1);
		return(1);
	}
	fill_grid(grid, str, height, width);
	//print_grid(grid, height, width);
	mark_island(grid, height, width);
	print_grid(grid, height, width);
	free_grid(grid, height);
	free(str);
	close(fd);
	
}
