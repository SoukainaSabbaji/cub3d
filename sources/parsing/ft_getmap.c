/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:16:10 by makacem           #+#    #+#             */
/*   Updated: 2023/03/11 21:02:18 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

int		ft_getnbrof_lines(char *file_name);
char	**ft_getmap2d_table(int nbrof_lines, char *file_name);

char	**ft_getmap2d(char *file_name)
{
	char	**map2d;
	int		nbrof_lines;

	nbrof_lines = ft_getnbrof_lines(file_name);
	map2d = ft_getmap2d_table(nbrof_lines, file_name);
	if (*map2d == NULL)
	{
		free(map2d);
		return (NULL);
	}
	return (map2d);
}

int	ft_getfile_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (-1);
	}
	return (fd);
}

int	ft_getnbrof_lines(char *file_name)
{
	int		fd;
	char	*line;
	int		nbrof_lines;

	fd = ft_getfile_fd(file_name);
	nbrof_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && (ft_strncmp(" ", line, 1) == 0
				|| ft_strncmp("1", line, 1) == 0))
		{
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd);
				nbrof_lines++;
			}
			return (close(fd), nbrof_lines);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nbrof_lines);
}

int	ft_find_line(char *line)
{
	if (line && (ft_strncmp(" ", line, 1) == 0
			|| ft_strncmp("1", line, 1) == 0))
		return (1);
	else
		return (0);
}

char	**ft_getmap2d_table(int nbrof_lines, char *file_name)
{
	int		fd;
	char	**map;
	char	**temp;
	char	*line;

	fd = open(file_name, O_RDONLY);
	temp = (char **)malloc(sizeof(char *) * (nbrof_lines + 1));
	map = temp;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_find_line(line) == 1)
		{
			while (line != NULL)
			{
				*temp = line;
				temp++;
				line = get_next_line(fd);
			}
			return (*temp = NULL, close(fd), map);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (*temp = NULL, temp);
}
