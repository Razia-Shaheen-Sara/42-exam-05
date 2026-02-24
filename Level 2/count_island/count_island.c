/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_island.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/24 15:05:07 by rshaheen      #+#    #+#                 */
/*   Updated: 2026/02/24 15:29:19 by rshaheen      ########   odam.nl         */
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
			if (str[k] == 'X' || str[k] == '.' || str[k] == '\n')
				k++;
			else
				return (-1);
		}
		if (str[k] != '\n')//
			return (-1);
		k++;//go to the next line
	}
	return (0);
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
	int height = count_height(str);
	int width = count_width(str);
	if(validate_map(str, height, width)== -1)
	{
		write(1,"\n", 1);
		return(1);
	}
}
