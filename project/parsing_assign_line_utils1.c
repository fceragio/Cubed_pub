/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_line_utils1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:59:09 by federico          #+#    #+#             */
/*   Updated: 2025/07/09 02:09:07 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	assign_line_no(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->No_flag == true)
	{
		print_error("Error\nMore lines contain north_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->No_flag = true;
	blueprint->No = line;
	return (SUCCESS);
}

int	assign_line_so(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->So_flag == true)
	{
		print_error("Error\nMore lines contain south_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->So_flag = true;
	blueprint->So = line;
	return (SUCCESS);
}

int	assign_line_we(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->We_flag == true)
	{
		print_error("Error\nMore lines contain west_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->We_flag = true;
	blueprint->We = line;
	return (SUCCESS);
}

int	assign_line_ea(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->Ea_flag == true)
	{
		print_error("Error\nMore lines contain east_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->Ea_flag = true;
	blueprint->Ea = line;
	return (SUCCESS);
}
