/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:11:26 by federico          #+#    #+#             */
/*   Updated: 2025/07/04 17:48:10 by federico         ###   ########.fr       */
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
		write(1, &c, 1);
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
		write(2, &c, 1);
		i++;
	}
}
