/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:15:13 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/11 15:17:37 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"


void ft_putstr_fd(const char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
    {
        write(fd, &s[i], 1);
        i++;
    }
}

void ft_error(void)
{
    ft_putstr_fd(mlx_strerror(mlx_errno), 2);
    exit(EXIT_FAILURE);
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

