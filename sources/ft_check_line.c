/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:52:07 by makacem           #+#    #+#             */
/*   Updated: 2023/02/19 18:53:20 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	ft_check_first_line(char **table)
{
	char	*line;

	line = *table;
	while (*line != '\n' && *line != '\0')
	{
		if (*line != '1' && *line != ' ')
		{
			printf("Error: Invalid map.\n");
			exit(0);
		}
		line++;
	}
}

void	ft_check_last_line(char **table)
{
	char *line;

	while (*(table + 1) != NULL)
		table++;
	line = *table;
	while (*line != '\n' && *line != '\0')
	{
		if (*line != '1' && *line != ' ')
		{
			printf("Error: Invalid map.\n");
			exit(0);
		}
		line++;
	}
}

void	ft_check_top_down(char **table)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (table[i] != NULL)
	{
		while (table[i][j] != '\0')
		{
			if (table[i][j] == '0'
				&& ((table[i - 1][j] != '1' && table[i - 1][j] != '0'
				&& table[i - 1][j] != 'N' && table[i - 1][j] != 'S'
				&& table[i - 1][j] != 'E' && table[i - 1][j] != 'W')
				|| (table[i + 1][j] != '1' && table[i + 1][j] != '0'
				&& table[i + 1][j] != 'N' && table[i + 1][j] != 'S'
				&& table[i + 1][j] != 'E' && table[i + 1][j] != 'W')))
			{
				printf("Error: Invalid map.\n");
				exit(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_check_left_right(char **table)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (table[i] != NULL)
	{
		while (table[i][j] != '\0')
		{
			if (table[i][j] == '0'
				&& ((table[i][j - 1] != '1' && table[i][j - 1] != '0'
				&& table[i][j - 1] != 'N' && table[i][j - 1] != 'S'
				&& table[i][j - 1] != 'E' && table[i][j - 1] != 'W')
				|| (table[i][j + 1] != '1' && table[i][j + 1] != '0'
				&& table[i][j + 1] != 'N' && table[i][j + 1] != 'S'
				&& table[i][j + 1] != 'E' && table[i][j + 1] != 'W')))
			{
				printf("Error: Invalid map.\n");
				exit(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
