/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_line_utils1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:56:47 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 16:07:58 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_N_line(char *line)
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

int	check_S_line(char *line)
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

int	check_W_line(char *line)
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

int	check_E_line(char *line)
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
