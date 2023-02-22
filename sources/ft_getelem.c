/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getelem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:52:53 by makacem           #+#    #+#             */
/*   Updated: 2023/02/22 20:34:48 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

t_elem	ft_getelem(char *map_filename)
{
	t_elem	elem;

	elem.north = ft_getpath(map_filename, "NO");
	if (elem.north == NULL)
		printf("Error: north texture not found\n");
	elem.south = ft_getpath(map_filename, "SO");
	if (elem.south == NULL)
		printf("Error: south texture not found\n");
	elem.west = ft_getpath(map_filename, "WE");
	if (elem.west == NULL)
		printf("Error: west texture not found\n");
	elem.east = ft_getpath(map_filename, "EA");
	if (elem.east == NULL)
		printf("Error: east texture not found\n");
	elem.floor = ft_getrgb(map_filename, "F");
	if (elem.floor.r == -1 || elem.floor.g == -1 || elem.floor.b == -1)
		printf("Error: invalid floor rgb\n");
	elem.ceiling = ft_getrgb(map_filename, "C");
	if (elem.ceiling.r == -1 || elem.ceiling.g == -1 || elem.ceiling.b == -1)
		printf("Error: invalid ceiling rgb\n");
	elem.map = ft_getmap2d(map_filename);
	ft_check_map2d(elem.map);
	return (elem);
}
