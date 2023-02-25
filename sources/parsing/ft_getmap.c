/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:16:10 by makacem           #+#    #+#             */
/*   Updated: 2023/02/25 14:53:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

int	ft_getnbrof_lines(char *file_name);
char **ft_getmap2d_table(int nbrof_lines, char *file_name);

char	**ft_getmap2d(char *file_name)
{
	char	**map2d;
	int		nbrof_lines;

	nbrof_lines = ft_getnbrof_lines(file_name);
	map2d = ft_getmap2d_table(nbrof_lines, file_name);
	return (map2d);
}

int	ft_getnbrof_lines(char *file_name)
{
	int		fd;
	char	*line;
	int		nbrof_lines;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (-1);
	}
	nbrof_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && (ft_strncmp(" ", line, 1) == 0 || ft_strncmp("1", line, 1) == 0))
		{
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd);
				nbrof_lines++;
			}
			close(fd);
			return(nbrof_lines);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
    return(nbrof_lines);
}

char **ft_getmap2d_table(int nbrof_lines, char *file_name)
{
	int		fd;
	char	**map;
	char	**temp;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (NULL);
	}
	temp = (char **)malloc(sizeof(char *) * (nbrof_lines + 1));
	if (temp == NULL)
		return (NULL);
	map = temp;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && (ft_strncmp(" ", line, 1) == 0 || ft_strncmp("1", line, 1) == 0))
		{
			while (line != NULL)
			{
				*temp = line;
				temp++;
				line = get_next_line(fd);
				
			}
			*temp = NULL;
			close(fd);
			return(map);
		}
		free(line);
		line = get_next_line(fd);
	}
	*temp = NULL;
	close(fd);
	return (map);
}
