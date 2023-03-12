/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:54:36 by makacem           #+#    #+#             */
/*   Updated: 2023/03/12 12:26:48 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

char	*ft_getname(char *str);
void	ft_removenl(char *str);
int		ft_count_nbrof_elem(char *file_name, char *direction);

char	*ft_getpath(char *file_name, char *direction)
{
	char	*path;
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1 || ft_count_nbrof_elem(file_name, direction) != 1)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && ft_strncmp(direction, line, 3) == 0)
		{
			path = ft_getname(line);
			free(line);
			close(fd);
			ft_removenl(path);
			return (path);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), NULL);
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

void	ft_removenl(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\n')
			*str = '\0';
		str++;
	}
}

int	ft_count_nbrof_elem(char *file_name, char *direction)
{
	int		nbr;
	char	*line;
	int		fd;

	nbr = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && ft_strncmp(direction, line, 3) == 0)
			nbr++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), nbr);
}
