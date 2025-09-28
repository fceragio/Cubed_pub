/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_blueprint_ok.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:02:20 by federico          #+#    #+#             */
/*   Updated: 2025/09/12 16:01:58 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	blueprint_ok(t_map_blueprint *blueprint)
{
	if (blueprint->no_flag == false || blueprint->so_flag == false
		|| blueprint->we_flag == false || blueprint->ea_flag == false
		|| blueprint->c_flag == false || blueprint->f_flag == false)
	{
		print_err("Error\nThe file didn't contain all the fields required\n");
		return (FAILURE);
	}
	create_char_map(blueprint);
	if (blueprint_map_ok(blueprint) == FAILURE)
		return (FAILURE);
	blueprint_prepare_fields(blueprint);
	if (blueprint_f_c_colors(blueprint) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	blueprint_f_c_colors(t_map_blueprint *blueprint)
{
	int	i;

	i = 0;
	while (i < COLOR_VALUES)
	{
		blueprint->c_vals[i] = string_to_int(blueprint->split_c[i]);
		if (blueprint->c_vals[i] == -1)
		{
			print_err("Error\n");
			print_err(blueprint->split_c[i]);
			print_err(" is not a valid value for cealing color\n");
			return (FAILURE);
		}
		blueprint->f_vals[i] = string_to_int(blueprint->split_f[i]);
		if (blueprint->f_vals[i] == -1)
		{
			print_err("Error\n");
			print_err(blueprint->split_f[i]);
			print_err(" is not a valid value for floor color\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	string_to_int(char *str)
{
	int	i;
	int	result;

	if (str == NULL)
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	return (result);
}
