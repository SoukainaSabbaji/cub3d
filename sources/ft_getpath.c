/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:54:36 by makacem           #+#    #+#             */
/*   Updated: 2023/02/22 18:02:05 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

char	*ft_getname(char *str);

char	*ft_getpath(char	*file_name, char *direction)
{
	char	*path;
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && ft_strncmp(direction, line, 2) == 0)
		{
			path = ft_getname(line);
			free(line);
			close(fd);
			return (path);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}

char	*ft_getname(char *str)
{
	char	*path;
	char	**arr;

	arr = ft_split(str, ' ');
	path = *(arr + 1);
	free(*arr);
	free(arr);
	return (path);
}
