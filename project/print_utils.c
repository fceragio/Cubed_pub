/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:11:26 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 02:04:51 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

void	print_str(char *str)
{
	int		i;
	char	c;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		if (write(1, &c, 1) == -1)
		{
			exit(WR_ERR);
		}
		i++;
	}
}

void	print_error(char *str)
{
	int		i;
	char	c;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		if (write(2, &c, 1) == -1)
		{
			exit(WR_ERR);
		}
		i++;
	}
}

void	manage_critical_error(char *msg, int stat)
{
	perror(msg);
	exit(stat);
}
