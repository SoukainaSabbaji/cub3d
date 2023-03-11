/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getrgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:55:38 by makacem           #+#    #+#             */
/*   Updated: 2023/03/11 14:33:30 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

t_rgb	ft_getrgb(char *file_name, char *f_c)
{
	t_rgb	rgb;
	char	*line;
	int		fd;

	rgb = ft_rgberr();
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (rgb);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line && ft_strncmp(f_c, line, 1) == 0)
		{
			rgb = ft_getcolors(line);
			free(line);
			close(fd);
			return (rgb);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), rgb);
}

t_rgb	ft_rgberr(void)
{
	t_rgb	rgb;

	rgb.r = -1;
	rgb.g = -1;
	rgb.b = -1;
	return (rgb);
}

int	ft_2darrlen(char **arr)
{
	int	len;

	len = 0;
	while (*arr != NULL)
	{
		arr++;
		len++;
	}
	return (len);
}

void	ft_free2darr(char **arr)
{
	char	**temp;

	temp = arr;
	while (*arr != NULL)
	{
		free(*arr);
		arr++;
	}
	free(temp);
}
