/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcolors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:57:47 by makacem           #+#    #+#             */
/*   Updated: 2023/03/11 13:41:25 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

int		ft_getclr(char *str, int r_g_b);
int		ft_check_isdigit(char *str);
char	*ft_select_free(char *elem, char *str1, char *str2);

t_rgb	ft_getcolors(char *str)
{
	t_rgb	rgb;
	char	*rgbline;
	char	**arr;

	rgb = ft_rgberr();
	arr = ft_split(str, ' ');
	if (*(arr + 1) == NULL)
	{
		free(arr);
		free(*arr);
		return (rgb);
	}
	rgbline = *(arr + 1);
	free(*arr);
	free(arr);
	rgb.r = ft_getclr(rgbline, 'r');
	rgb.g = ft_getclr(rgbline, 'g');
	rgb.b = ft_getclr(rgbline, 'b');
	free(rgbline);
	return (rgb);
}

int	ft_getclr(char *str, int r_g_b)
{
	char	**arr;
	char	*elem;
	int		nbr;

	nbr = -1;
	arr = ft_split(str, ',');
	if (ft_2darrlen(arr) != 3)
	{
		ft_free2darr(arr);
		return (nbr);
	}
	if (r_g_b == 'r')
		elem = ft_select_free(*arr, *(arr + 1), *(arr + 2));
	if (r_g_b == 'g')
		elem = ft_select_free(*(arr + 1), *arr, *(arr + 2));
	if (r_g_b == 'b')
		elem = ft_select_free(*(arr + 2), *arr, *(arr + 1));
	if (ft_check_isdigit(elem) == 0)
		nbr = ft_atoi(elem);
	if (nbr < 0 || nbr > 255)
		nbr = -1;
	free(elem);
	free(arr);
	return (nbr);
}

int	ft_check_isdigit(char *str)
{
	while (*str != '\0' && *str != '\n')
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return (0);
}

char	*ft_select_free(char *elem, char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (elem);
}
