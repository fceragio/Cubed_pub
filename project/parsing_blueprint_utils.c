/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:39:38 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 00:21:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	blueprint_init(t_map_blueprint *blueprint)
{
	blueprint->No_flag = false;
	blueprint->So_flag = false;
	blueprint->We_flag = false;
	blueprint->Ea_flag = false;
	blueprint->C_flag = false;
	blueprint->F_flag = false;
	blueprint->No = NULL;
	blueprint->So = NULL;
	blueprint->We = NULL;
	blueprint->Ea = NULL;
	blueprint->C = NULL;
	blueprint->F = NULL;
	blueprint->split_C = NULL;
	blueprint->split_F = NULL;
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
		printf("%s\n", char_map[i]);
		free(char_map[i]);
		i++;
	}
	free(char_map);
	printf("\n");
}

void	clear_blueprint(t_map_blueprint **blueprint)
{
	printf("\nclearing blueprint\n");
	t_list	*temp;

	if ((*blueprint) == NULL)
		return ;
	printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", (*blueprint)->No, (*blueprint)->So, (*blueprint)->We, (*blueprint)->Ea, (*blueprint)->C, (*blueprint)->F);
	free((*blueprint)->No);
	free((*blueprint)->So);
	free((*blueprint)->We);
	free((*blueprint)->Ea);
	free((*blueprint)->C);
	free((*blueprint)->F);
	while((*blueprint)->map_list)
	{
		temp = (*blueprint)->map_list->next;
		printf("%s\n", (*blueprint)->map_list->content);
		free((*blueprint)->map_list->content);
		free((*blueprint)->map_list);
		(*blueprint)->map_list = temp;
	}
	clear_char_matrix((*blueprint)->char_map);
	clear_char_matrix((*blueprint)->split_C);
	clear_char_matrix((*blueprint)->split_F);
	free(*blueprint);
	(*blueprint) = NULL;
}
