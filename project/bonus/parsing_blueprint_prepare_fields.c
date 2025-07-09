/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_prepare_fields.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:48:01 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 15:38:24 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	blueprint_prepare_fields(t_map_blueprint *blueprint)
{
	blueprint->no = keep_only_second_string(blueprint->no);
	blueprint->so = keep_only_second_string(blueprint->so);
	blueprint->we = keep_only_second_string(blueprint->we);
	blueprint->ea = keep_only_second_string(blueprint->ea);
	blueprint->split_c = split_second_string_commas(blueprint->c);
	blueprint->split_f = split_second_string_commas(blueprint->f);
}

int	trimmed_len(char *to_trim)
{
	int	i;
	int	len;

	if (to_trim == NULL)
		return (-1);
	i = 0;
	len = 0;
	while (to_trim[i] == ' ' || to_trim[i] == '\t')
		i++;
	while (to_trim[i] && to_trim[i] != ' ' && to_trim[i] != '\t')
		i++;
	while (to_trim[i] == ' ' || to_trim[i] == '\t')
		i++;
	while (to_trim[i] && to_trim[i] != ' ' && to_trim[i] != '\t'
		&& to_trim[i] != '\n')
	{
		len++;
		i++;
	}
	return (len);
}

void	copy_only_second_string(char *to_copy, char *buffer)
{
	int	i;
	int	j;

	if (to_copy == NULL)
		return ;
	i = 0;
	j = 0;
	while (to_copy[i] == ' ' || to_copy[i] == '\t')
		i++;
	while (to_copy[i] && to_copy[i] != ' ' && to_copy[i] != '\t')
		i++;
	while (to_copy[i] == ' ' || to_copy[i] == '\t')
		i++;
	while (to_copy[i] && to_copy[i] != ' ' && to_copy[i] != '\t'
		&& to_copy[i] != '\n')
	{
		buffer[j] = to_copy[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*keep_only_second_string(char *to_trim)
{
	int		len;
	char	*result;

	if (to_trim == NULL)
		return (NULL);
	len = trimmed_len(to_trim);
	if (len <= 0)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
	{
		perror("keep_only_second_string malloc");
		exit(1);
	}
	copy_only_second_string(to_trim, result);
	free(to_trim);
	return (result);
}
