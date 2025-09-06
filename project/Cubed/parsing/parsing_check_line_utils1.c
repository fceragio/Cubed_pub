/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_line_utils1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:56:47 by federico          #+#    #+#             */
/*   Updated: 2025/09/01 19:37:10 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	check_n_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'O')
	{
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			return (M_ERR);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_ERR);
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_NO);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}

int	check_s_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'O')
	{
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			return (M_ERR);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_ERR);
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_SO);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}

int	check_w_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'E')
	{
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			return (M_ERR);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_ERR);
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_WE);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}

int	check_e_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'A')
	{
		i++;
		if (line[i] != ' ' && line[i] != '\t')
			return (M_ERR);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_ERR);
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (M_EA);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}
