/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_line_utils1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:59:09 by federico          #+#    #+#             */
/*   Updated: 2025/09/12 16:01:58 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_line_no(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->no_flag == true)
	{
		print_err("Error\nMore lines contain north_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->no_flag = true;
	blueprint->no = line;
	return (SUCCESS);
}

int	assign_line_so(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->so_flag == true)
	{
		print_err("Error\nMore lines contain south_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->so_flag = true;
	blueprint->so = line;
	return (SUCCESS);
}

int	assign_line_we(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->we_flag == true)
	{
		print_err("Error\nMore lines contain west_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->we_flag = true;
	blueprint->we = line;
	return (SUCCESS);
}

int	assign_line_ea(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->ea_flag == true)
	{
		print_err("Error\nMore lines contain east_texture path\n");
		free(line);
		return (FAILURE);
	}
	blueprint->ea_flag = true;
	blueprint->ea = line;
	return (SUCCESS);
}
