/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:24:23 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 19:10:16 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_map	*parsing(int argc, char *file_path)
{
	t_map_blueprint	*map_blueprint;
	int				fd;

	if (cub_file_is_ok(argc, file_path) == FAILURE)
		return (NULL);
	map_blueprint = malloc(sizeof(t_map_blueprint));
	if (map_blueprint == NULL)
	{
		perror("parsing malloc");
		exit(1);
	}
	fd = open(file_path, O_RDONLY, 0);
	create_map_blueprint(&map_blueprint, fd);
	close(fd);
	return (create_map(&map_blueprint));
}

t_map	*create_map(t_map_blueprint **blueprint)
{
	t_map	*map;

	if (*blueprint == NULL)
		return (NULL);
	if (blueprint_ok(*blueprint) == FAILURE)
	{
		clear_blueprint(blueprint);
		return (NULL);
	}
	map = blueprint_to_map(*blueprint);
	clear_blueprint(blueprint);
	return (map);
}

void	create_map_blueprint(t_map_blueprint **blueprint, int fd)
{
	char	*next_line;

	blueprint_init(*blueprint);
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (identify_line(next_line) == M_MAP)
			break ;
		if (assign_line(next_line, *blueprint) == FAILURE)
		{
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
	while (next_line)
	{
		if (assign_map_line(next_line, *blueprint) == FAILURE)
		{
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
}

int	blueprint_ok(t_map_blueprint *blueprint)
{
	if (blueprint->No_flag == false || blueprint->So_flag == false
		|| blueprint->We_flag == false || blueprint->Ea_flag == false
		|| blueprint->C_flag == false || blueprint->F_flag == false)
	{
		print_error("Error\nThe file didn't contain all the fields required\n");
		return (FAILURE);
	}
	create_char_map(blueprint);
	if (blueprint_map_ok(blueprint) == FAILURE)
		return (FAILURE);
	blueprint_prepare_fields(blueprint);
	return (SUCCESS);
}

t_map	*blueprint_to_map(t_map_blueprint *blueprint)
{
	
	return (NULL);
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
	while (to_trim[i] && to_trim[i] != ' ' && to_trim[i] != '\t' && to_trim[i] != '\n')
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
	while (to_copy[i] && to_copy[i] != ' ' && to_copy[i] != '\t' && to_copy[i] != '\n')
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


void	blueprint_prepare_fields(t_map_blueprint *blueprint)
{
	printf("preparing fields\n");
	blueprint->No = keep_only_second_string(blueprint->No);
	blueprint->So = keep_only_second_string(blueprint->So);
	blueprint->We = keep_only_second_string(blueprint->We);
	blueprint->Ea = keep_only_second_string(blueprint->Ea);
	blueprint->split_C = split_second_string_commas(blueprint->C);
	blueprint->split_F = split_second_string_commas(blueprint->F);
}
