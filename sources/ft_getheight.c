/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:20:03 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:20:30 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int	ft_getheight(char **map)
{
	int		height;

	height = 0;
	while (*map != '\0')
	{
		height++;
		map++;
	}
	return (height);
}
