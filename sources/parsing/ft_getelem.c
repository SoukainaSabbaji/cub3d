/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:52:53 by makacem           #+#    #+#             */
/*   Updated: 2023/02/23 12:01:26 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

t_map	*ft_getmap(char *map_filename)
{
	t_map	*elem;

	elem = malloc(sizeof(t_map));
	elem->n_texture = ft_getpath(map_filename, "NO");
	if (elem->n_texture == NULL)
		printf("Error: n_texture texture not found\n");
	elem->s_texture = ft_getpath(map_filename, "SO");
	if (elem->s_texture == NULL)
		printf("Error: s_texture texture not found\n");
	elem->w_texture = ft_getpath(map_filename, "WE");
	if (elem->w_texture == NULL)
		printf("Error: w_texture texture not found\n");
	elem->e_texture = ft_getpath(map_filename, "EA");
	if (elem->e_texture == NULL)
		printf("Error: e_texture texture not found\n");
	elem->floor = ft_getrgb(map_filename, "F");
	if (elem->floor.r == -1 || elem->floor.g == -1 || elem->floor.b == -1)
		printf("Error: invalid floor rgb\n");
	elem->ceiling = ft_getrgb(map_filename, "C");
	if (elem->ceiling.r == -1 || elem->ceiling.g == -1 || elem->ceiling.b == -1)
		printf("Error: invalid ceiling rgb\n");
	elem->map = ft_getmap2d(map_filename);
	if (elem->map == NULL)
		printf("Error: map not found\n");
	ft_check_map2d(elem->map);
	return (elem);
}