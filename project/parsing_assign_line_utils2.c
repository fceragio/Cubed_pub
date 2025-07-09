/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_line_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:58:59 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 15:37:07 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	assign_line_c(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->c_flag == true)
	{
		print_error("Error\nMore lines contain cealing color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->c_flag = true;
	blueprint->c = line;
	return (SUCCESS);
}

int	assign_line_f(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->f_flag == true)
	{
		print_error("Error\nMore lines contain floor color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->f_flag = true;
	blueprint->f = line;
	return (SUCCESS);
}
