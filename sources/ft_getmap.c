/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:16:10 by makacem           #+#    #+#             */
/*   Updated: 2023/02/17 13:59:43 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int	ft_getnbrof_lines(char *file_name);
char **ft_getmap2d_table(int nbrof_lines, char *file_name);

char	**ft_getmap2d(char *file_name)
{
	char	**map2d;
	int		nbrof_lines;

	nbrof_lines = ft_getnbrof_lines(file_name);
	map2d = ft_getmap2d_table(nbrof_lines, file_name);
	// g_map = map;
	// mapFile = fopen(map_path, "r");
	//g_wall = fill_map_array(mapFile, map);
	return (map2d);
}

int	ft_getnbrof_lines(char *file_name)
{
	int	fd;
	char *line;
	int nbrof_lines;

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
		free(line);
		line = get_next_line(fd);
		nbrof_lines++;
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
		*temp = line;
		temp++;
		line = get_next_line(fd);
	}
	*temp = NULL;
	close(fd);
	return (map);
}
