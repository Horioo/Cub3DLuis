/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:23:44 by ajorge-p          #+#    #+#             */
/*   Updated: 2025/02/08 22:57:05 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void verify_number5(t_cube *cube, int count, char *line, int fd, char **color)
{
	int i;
	int j;

	i = 0;
	while(color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (count > 1 && j == (int)ft_strlen(color[i]) - 1 && ft_isdigit(color[i][j]))
			{
				if (color[i][j - 1] == ' ')
				{
					close(fd);
					free(line);
					free_color(color);
					print_error(cube, "Error: Spaces in number\n");
				}
			}
			j++;
		}
		i++;
	}
}

void verify_number4(t_cube *cube, int count, char *line, int fd, char **color)
{
	int i;
	int j;

	i = 0;
	while(color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (count > 1 && j == 0 && ft_isdigit(color[i][j]))
			{
				if (color[i][j + 1] == ' ')
				{
					close(fd);
					free(line);
					free_color(color);
					print_error(cube, "Error: Spaces in number\n");
				}
			}
			j++;
		}
		i++;
	}
}

void verify_number3(t_cube *cube, int count, char *line, int fd, char **color)
{
	int i;
	int j;

	i = 0;
	while(color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (count > 1 && ft_isdigit(color[i][j]))
			{
				if (j - 1 >= 0 && j + 1 <= (int)ft_strlen(color[i]) && color[i][j - 1] == ' ' && color[i][j + 1] == ' ')
				{
					close(fd);
					free(line);
					free_color(color);
					print_error(cube, "Error: Spaces in number\n");
				}
			}
			j++;
		}
		i++;
	}
}

void verify_number2(t_cube *cube, char *line, int fd)
{
    int i = 0;
	int j;
	char **color;
	int count = 0;

	color = ft_split(line + 2, ',');
	while (color[i])
	{
		j = 0;
		while(color[i][j])
		{
			if (ft_isdigit(color[i][j]))
				count++;
			j++;
		}
		verify_number3(cube, count, line, fd, color);
		verify_number4(cube, count, line, fd, color);
		verify_number5(cube, count, line, fd, color);
		i++;
	}
	free_color(color);
}

void verify_number(t_cube *cube, char *file)
{
    int fd;
    char *line;
	
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        if (line[0] == 'C' || line[0] == 'F')
            verify_number2(cube, line, fd);
        free(line);
    }
    close(fd);
}
