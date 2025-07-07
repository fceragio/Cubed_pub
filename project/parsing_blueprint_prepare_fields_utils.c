/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_prepare_fields_utils.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:50:02 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 21:53:21 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	find_next_number(char *str, int start)
{
	if (str == NULL)
		return (0);
	while (str[start] && (str[start] < '0' || str[start] > '9'))
		start++;
	return (start);
}

int	measure_number(char *str, int start)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[start] && str[start] >= '0' && str[start] <= '9')
	{
		len++;
		start++;
	}
	return (len);
}

void	copy_number(char *to_copy, int *start, char *buffer)
{
	int	j;

	if (to_copy == NULL)
		return ;
	j = 0;
	while (to_copy[*start] && to_copy[*start] >= '0' && to_copy[*start] <= '9')
	{
		buffer[j] = to_copy[*start];
		(*start)++;
		j++;
	}
	buffer[j] = '\0';
}

char	**split_second_string_commas(char *to_split)
{
	int		len;
	int		i;
	int		book_mark;
	char	**result;

	result = malloc(sizeof(char *) * (COLOR_VALUES + 1));
	if (result == NULL)
	{
		perror("split_second_string_commas malloc");
		exit(1);
	}
	i = 0;
	book_mark = 0;
	while (i < COLOR_VALUES)
	{
		book_mark = find_next_number(to_split, book_mark);
		len = measure_number(to_split, book_mark);
		result[i] = malloc(sizeof(char) * (len + 1));
		if (result[i] == NULL)
		{
			//implement critical error to save 6 lines later
			perror("split_second_string_commas malloc");
			exit(1);
		}
		copy_number(to_split, &book_mark, result[i]);
		i++;
	}
	result[i] = (NULL);
	return (result);
}
