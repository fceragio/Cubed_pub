/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_blueprint_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:44:58 by federico          #+#    #+#             */
/*   Updated: 2025/07/07 15:25:24 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	identify_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (M_SKIP);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (M_C);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (M_F);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (check_N_line(line + i));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (check_S_line(line + i));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (check_W_line(line + i));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (check_E_line(line + i));
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		return (M_MAP);
	else
		return (M_ERR);
}

int	assign_line(char *line, t_map_blueprint *blueprint)
{
	int	id;

	id = identify_line(line);
	if (id == M_ERR)
	{
		print_error("Error\nNon valid line found: ");
		print_error(line);
		print_error("\n");
		free(line);
		return (FAILURE);
	}
	else if (id == M_NO)
		return assign_line_NO(line, blueprint);
	else if (id == M_SO)
		return assign_line_SO(line, blueprint);
	else if (id == M_WE)
		return assign_line_WE(line, blueprint);
	else if (id == M_EA)
		return assign_line_EA(line, blueprint);
	else if (id == M_C)
		return assign_line_C(line, blueprint);
	else if (id == M_F)
		return assign_line_F(line, blueprint);
	free(line);
	return (SUCCESS);
}

int	check_map_line(char *line)
{
	int	flag;
	int	i;

	if (line == NULL)
		return (M_ERR);
	flag = M_ERR;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
		{
			if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
				flag = M_MAP;
			else
				return (M_ERR);
		}
			i++;
	}
	return (flag);
}

int	assign_map_line(char *line, t_map_blueprint *blueprint)
{
	if (check_map_line(line) == M_ERR)
	{
		print_error("Error\nInvalid line in the map: ");
		print_error(line);
		print_error("\n");
		free(line);
		return (FAILURE);
	}
	list_append(line, &blueprint->map_list);
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				check;

	next_line = NULL;
	check = read(fd, next_line, 0);
	if (fd < 0 || BUFFER_SIZE <= 0 || check < 0)
		return (NULL);
	create_list_till_newl(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = concatenate_lines(list);
	cleanup(&list);
	return (next_line);
}
