/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:57:01 by makacem           #+#    #+#             */
/*   Updated: 2023/02/19 18:57:59 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

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
	while(*(line + 1) != NULL)
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
