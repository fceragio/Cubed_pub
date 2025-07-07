/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_blueprint_gnl2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:50:35 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 15:17:52 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	add_node(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

int	new_line(t_list *list)
{
	size_t	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*find_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}


void	cleanup(t_list **list)
{
	t_list	*last_node;
	t_list	*new_node;
	char	*leftover;
	int		i;
	int		j;

	leftover = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	new_node = malloc(sizeof(t_list));
	if (leftover == NULL || new_node == NULL)
		return ;
	last_node = find_last(*list);
	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		leftover[j++] = last_node->content[i];
	leftover[j] = '\0';
	new_node->content = leftover;
	new_node->next = NULL;
	freeall_save_leftover(list, new_node, leftover);
}

void	freeall_save_leftover(t_list **list, t_list *new_list, char	*leftover)
{
	t_list	*spare;

	if (*list == NULL)
		return ;
	while (*list)
	{
		spare = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = spare;
	}
	*list = NULL;
	if (new_list->content[0])
		*list = new_list;
	else
	{
		free(leftover);
		free(new_list);
	}
}
