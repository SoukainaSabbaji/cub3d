/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:06:17 by makacem           #+#    #+#             */
/*   Updated: 2023/03/11 13:32:04 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

void	ft_nbrof_args(int nbr_of_args);

void	ft_check_input(int nbr_of_args, char **args)
{
	char	*file_name;
	int		fd_file_name;

	ft_nbrof_args(nbr_of_args);
	file_name = args[1];
	if (ft_strchr(file_name, '.') == 0)
	{
		printf("Error: invalid argument\n");
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(".cub", ft_strchr(file_name, '.'), 5) != 0)
	{
		printf("Error: invalid file extension\n");
		exit (EXIT_FAILURE);
	}
	fd_file_name = open(file_name, O_RDONLY);
	if (fd_file_name == -1)
	{
		printf("Error: file not found\n");
		exit (EXIT_FAILURE);
	}
	close(fd_file_name);
}

void	ft_nbrof_args(int nbr_of_args)
{
	if (nbr_of_args < 2)
	{
		printf("Error: invalid number of arguments\n");
		exit (EXIT_FAILURE);
	}
}
