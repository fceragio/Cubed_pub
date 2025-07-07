/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:32:20 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 14:33:10 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_list	*list_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	list_append(char *content, t_list **list)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		perror("list_append malloc\n");
		exit(1);
	}
	new->content = content;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		last = list_last(*list);
		last->next = new;
	}
}

int	list_len(t_list *list)
{
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

int	content_max_len(t_list *list)
{
	int	len;
	int	i;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (i >= len)
				len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}
