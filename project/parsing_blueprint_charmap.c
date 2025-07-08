/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_charmap.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:02:58 by federico          #+#    #+#             */
/*   Updated: 2025/07/08 17:14:24 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	create_char_map(t_map_blueprint *blueprint)
{
	//keep an eye on this -1 it may cause problems
	blueprint->x_len = content_max_len(blueprint->map_list) - 1;
	blueprint->y_len = list_len(blueprint->map_list);
	if (blueprint->x_len == 0 || blueprint->y_len == 0)
	{
		print_error("Error\nMap is insufficient\n");
		return ;
	}
	malloc_char_map(blueprint);
	set_char_map(blueprint);
}

void	zero_char_map(t_map_blueprint *blueprint)
{
	int	i;
	int	j;

	if (blueprint == NULL)
		return ;
	i = 0;
	while (blueprint->char_map[i])
	{
		j = 0;
		while (j <= blueprint->x_len)
		{
			blueprint->char_map[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	malloc_char_map(t_map_blueprint *blueprint)
{
	int	i;

	blueprint->char_map = malloc(sizeof(char *) * (blueprint->y_len + 1));
	if (blueprint == NULL || blueprint->char_map == NULL)
	{
		perror("malloc_char_map");
		exit(1);
	}
	i = 0;
	while (i < blueprint->y_len)
	{
		blueprint->char_map[i] = malloc(sizeof(char) * (blueprint->x_len + 1));
		if (blueprint->char_map[i] == NULL)
		{
			perror("malloc_char_map");
			exit(1);
		}
		i++;
	}
	blueprint->char_map[i] = NULL;
	zero_char_map(blueprint);
}

void	set_char_map(t_map_blueprint *blueprint)
{
	t_list	*temp;
	int		i;
	int		j;

	if (blueprint == NULL || blueprint->char_map == NULL)
		return ;
	temp = blueprint->map_list;
	i = 0;
	while (blueprint->char_map[i])
	{
		j = 0;
		while (temp->content[j])
		{
			if (temp->content[j] == '\n'
				|| temp->content[j] == '\0')
				break ;
			if (temp->content[j] != ' ')
				blueprint->char_map[i][j] = temp->content[j];
			j++;
		}
		i++;
		temp = temp->next;
	}
}
