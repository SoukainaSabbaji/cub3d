/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:50:04 by makacem           #+#    #+#             */
/*   Updated: 2023/02/16 14:11:11 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1

int	cnl(char	*str)
{
	int		i;

	i = 0;
	while (*str && *str != '\n')
	{
		str++;
		i++;
	}
	return (i + 1);
}

char	*return_null(char	*str)
{
	free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	int			read_retrun_value;
	static char	*temp_buffer;

	line = ft_calloc_gnl(1, sizeof(char));
	if (temp_buffer != NULL)
	{
		line = ft_strjoin_gnl(line, temp_buffer);
		temp_buffer = NULL;
	}
	while (!(ft_strchr_gnl(line, '\n')))
	{
		buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
		read_retrun_value = read(fd, buffer, BUFFER_SIZE);
		line = ft_strjoin_gnl(line, buffer);
		if (ft_strlen_gnl(line) == 0)
			return (return_null(line));
		if (read_retrun_value <= 0)
			return (line);
	}
	temp_buffer = ft_calloc_gnl(ft_strlen_gnl(line) - cnl(line) + 1, sizeof(char));
	ft_strlcpy_gnl(temp_buffer, line + cnl(line), ft_strlen_gnl(line + cnl(line)) + 1);
	*(line + cnl(line)) = '\0';
	return (line);
}
