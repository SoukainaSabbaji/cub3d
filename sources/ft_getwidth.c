/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getwidth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:18:52 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:19:43 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int	ft_getwidth(char **map)
{
	int		width;
	int		len;
	char	*line;

	width = 0;
	len = 0;
	while (*map != '\0')
	{
		line = *map;
		len = 0;
		while (*line != '\0' && *line != '\n')
		{
			len++;
			line++;
		}
		if (len > width)
			width = len;
		map++;
	}
	return (width);
}
