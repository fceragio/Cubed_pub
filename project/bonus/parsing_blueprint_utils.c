/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:39:38 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 18:56:38 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	blueprint_init(t_map_blueprint *blueprint)
{
	blueprint->no_flag = false;
	blueprint->so_flag = false;
	blueprint->we_flag = false;
	blueprint->ea_flag = false;
	blueprint->c_flag = false;
	blueprint->f_flag = false;
	blueprint->no = NULL;
	blueprint->so = NULL;
	blueprint->we = NULL;
	blueprint->ea = NULL;
	blueprint->c = NULL;
	blueprint->f = NULL;
	blueprint->split_c = NULL;
	blueprint->split_f = NULL;
	blueprint->map_list = NULL;
	blueprint->char_map = NULL;
	blueprint->x_len = 0;
	blueprint->y_len = 0;
}

void	clear_char_matrix(char **char_map)
{
	int	i;

	if (char_map == NULL)
		return ;
	i = 0;
	while (char_map[i])
	{
		free(char_map[i]);
		i++;
	}
	free(char_map);
}

void	clear_blueprint(t_map_blueprint **blueprint)
{
	t_list	*temp;

	if ((*blueprint) == NULL)
		return ;
	free((*blueprint)->no);
	free((*blueprint)->so);
	free((*blueprint)->we);
	free((*blueprint)->ea);
	free((*blueprint)->c);
	free((*blueprint)->f);
	while ((*blueprint)->map_list)
	{
		temp = (*blueprint)->map_list->next;
		free((*blueprint)->map_list->content);
		free((*blueprint)->map_list);
		(*blueprint)->map_list = temp;
	}
	clear_char_matrix((*blueprint)->char_map);
	clear_char_matrix((*blueprint)->split_c);
	clear_char_matrix((*blueprint)->split_f);
	free(*blueprint);
	(*blueprint) = NULL;
}
