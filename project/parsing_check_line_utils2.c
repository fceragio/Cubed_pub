/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_line_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:56:36 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 21:15:55 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	check_until_first_comma(int *i, char *line)
{
	if (line[*i] != ' ' && line[*i] != '\t')
		return (M_ERR);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '\n' || line[*i] == '\0' || line[*i] < '0' || line[*i] > '9')
		return (M_ERR);
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] != ',')
		return (M_ERR);
	printf("first comma %d\n", *i);
	return (SUCCESS);
}

static int	check_until_second_comma(int *i, char *line)
{
	if (check_until_first_comma(i, line) == M_ERR)
		return (M_ERR);
	(*i)++;
	printf("%d\n", *i);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '\n' || line[*i] == '\0' || line[*i] < '0' || line[*i] > '9')
		return (M_ERR);
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] != ',')
		return (M_ERR);
	printf("second comma %d\n", *i);
	return (SUCCESS);
}

int	check_C_line(char *line)
{
	int	i;

	i = 1;
	if (check_until_second_comma(&i, line) == M_ERR)
		return (M_ERR);
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0' || line[i] < '0' || line[i] > '9')
		return (M_ERR);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (M_ERR);
	printf("found C %d\n", i);
	return (M_C);
}

int	check_F_line(char *line)
{
	int	i;

	i = 1;
	if (check_until_second_comma(&i, line) == M_ERR)
		return (M_ERR);
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0' || line[i] < '0' || line[i] > '9')
		return (M_ERR);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (M_ERR);
	printf("found F %d\n", i);
	return (M_F);
}
