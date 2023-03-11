/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:57:01 by makacem           #+#    #+#             */
/*   Updated: 2023/03/11 21:28:32 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

void	ft_check_map2d(char **map2d)
{
	char	**table;

	table = map2d;
	ft_check_first_line(table);
	ft_check_last_line(table);
	ft_check_frst_lst_char(table);
	ft_check_top_down(table);
	ft_check_left_right(table);
	ft_check_player(table);
}

void	ft_check_frst_lst_char(char **table)
{
	char	**line;

	line = table;
	while (*(line + 1) != NULL)
	{
		if ((**line != '1' && **line != ' ')
			|| (*(*line + ft_strlen(*line) - 2) != '1'
				&& *(*line + ft_strlen(*line) - 2) != '0'))
		{
			printf("Error: Invalid map.\n");
			exit(0);
		}
		line++;
	}
}

char	*ft_lineof_ones(char *line, int len_long_line)
{
	char	*lineof_ones;
	int		lineof_ones_len;
	char	*temp;

	lineof_ones = NULL;
	lineof_ones_len = len_long_line - ft_strlen(line);
	lineof_ones = malloc(sizeof(char *) * (lineof_ones_len));
	*(lineof_ones + lineof_ones_len) = '\0';
	temp = lineof_ones;
	while (*temp != '\0')
	{
		*temp = '1';
		temp++;
	}
	return (lineof_ones);
}

void	ft_join_ones(char **old_map, int len_long_line, char *line)
{
	char	**new_map;
	char	*lineof_ones;

	new_map = old_map;
	while (*new_map != '\0')
	{	
		line = *new_map;
		lineof_ones = ft_lineof_ones(line, len_long_line);
		*new_map = ft_strjoin(line, lineof_ones);
		free(line);
		free(lineof_ones);
		new_map++;
	}
}

char	**ft_add_ones(char **old_map, int nbrof_lines)
{
	char	**new_map;
	int		len_long_line;
	char	*line;

	nbrof_lines = 0;
	len_long_line = 0;
	new_map = old_map;
	while (*new_map != '\0')
	{	
		line = *new_map;
		if (*(line + ft_strlen(line) - 1) == '\n')
			*(line + ft_strlen(line) - 1) = '\0';
		if ((int)ft_strlen(line) > len_long_line)
			len_long_line = ft_strlen(line);
		new_map++;
	}
	ft_join_ones(old_map, len_long_line, line);
	return (old_map);
}
