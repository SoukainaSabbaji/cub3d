/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:50:04 by makacem           #+#    #+#             */
/*   Updated: 2023/03/12 12:44:59 by ssabbaji         ###   ########.fr       */
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
	static char	*tmp_buf;

	line = cllc_gnl(1, sizeof(char));
	if (tmp_buf != NULL)
	{
		line = ft_strjoin_gnl(line, tmp_buf);
		tmp_buf = NULL;
	}
	while (!(ft_strchr_gnl(line, '\n')))
	{
		buffer = cllc_gnl(BUFFER_SIZE + 1, sizeof(char));
		read_retrun_value = read(fd, buffer, BUFFER_SIZE);
		line = ft_strjoin_gnl(line, buffer);
		if (strlen_2(line) == 0)
			return (return_null(line));
		if (read_retrun_value <= 0)
			return (line);
	}
	tmp_buf = cllc_gnl(strlen_2(line) - cnl(line) + 1, sizeof(char));
	strlcpy_2(tmp_buf, line + cnl(line), strlen_2(line + cnl(line)) + 1);
	*(line + cnl(line)) = '\0';
	return (line);
}
