/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_blueprint_gnl1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:50:14 by federico          #+#    #+#             */
/*   Updated: 2025/07/08 02:09:36 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	create_list_till_newl(t_list **list, int fd)
{
	char	*buffer;
	size_t	chars;

	while (!new_line(*list))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		chars = read(fd, buffer, BUFFER_SIZE);
		if (chars == 0)
		{
			free(buffer);
			return ;
		}
		buffer[chars] = '\0';
		add_node(list, buffer);
	}
}

char	*concatenate_lines(t_list	*list)
{
	size_t	total_len;
	char	*next_line;

	if (list == NULL)
		return (NULL);
	total_len = chars_to_newl(list);
	if (total_len <= 0)
		return (NULL);
	next_line = malloc(sizeof(char) * (total_len + 1));
	if (next_line == NULL)
		return (NULL);
	cat_nodes(list, next_line);
	return (next_line);
}

void	cat_nodes(t_list *list, char *next_line)
{
	size_t	i;
	size_t	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				next_line[j++] = '\n';
				next_line[j] = '\0';
				return ;
			}
			next_line[j++] = list->content[i++];
		}
		list = list->next;
	}
	next_line[j] = '\0';
}

size_t	chars_to_newl(t_list *list)
{
	size_t	total_len;
	size_t	i;

	if (list == NULL)
		return (0);
	total_len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (++total_len);
			i++;
			total_len++;
		}
		list = list->next;
	}
	return (total_len);
}

void	clear_nextlines(int fd)
{
	char	*next_line;

	next_line = get_next_line(fd);
	while (next_line)
	{
		free(next_line);
		next_line = get_next_line(fd);
	}
}
