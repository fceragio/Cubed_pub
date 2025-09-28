/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:11:26 by federico          #+#    #+#             */
/*   Updated: 2025/09/21 17:37:14 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_len(char *str)
{
	int	len;

	if (str == NULL)
		return (-1);
	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) == -1)
			exit(WR_ERR);
		i++;
	}
}

void	print_str(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	print_err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

void	manage_critical_error(char *msg, int stat)
{
	perror(msg);
	exit(stat);
}
