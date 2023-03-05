/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:53:47 by makacem           #+#    #+#             */
/*   Updated: 2023/02/24 13:23:12 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

void	ft_check_player(char **table)
{
	ft_check_nbrof_players(table);
	ft_check_player_position(table);
}

int	ft_count_nbrof_player(char **table)
{
	int i;
	int j;
	int nbr;

	i = 0;
	j = 0;
	nbr = 0;
	while (table[i] != NULL)
	{
		while (table[i][j] != '\0')
		{
			if (table[i][j] == 'N' || table[i][j] == 'S'
				|| table[i][j] == 'E' || table[i][j] == 'W')
				nbr++;
			j++;
		}
		j = 0;
		i++;
	}
	return (nbr);
}

void	ft_check_nbrof_players(char **table)
{
	int nbr;

	nbr = ft_count_nbrof_player(table);
	if (nbr == 0)
	{
		printf("Error: Invalid map: no player.\n");
		exit(0);
	}
	else if (nbr > 1)
	{
		printf("Error: Invalid map: more than one player.\n");
		exit(0);
	}
}

void	ft_check_player_position(char **table)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (table[i] != NULL)
	{
		while (table[i][j] != '\0')
		{
			if (((table[i][j] == 'N' || table[i][j] == 'S'|| table[i][j] == 'E' || table[i][j] == 'W')
				&& ((table[i - 1][j] != '1' && table[i - 1][j] != '0')
				|| (table[i + 1][j] != '1' && table[i + 1][j] != '0')))
				|| ((table[i][j] == 'N' || table[i][j] == 'S'|| table[i][j] == 'E' || table[i][j] == 'W')
				&& ((table[i][j - 1] != '1' && table[i][j - 1] != '0')
				|| (table[i][j + 1] != '1' && table[i][j + 1] != '0'))))
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