/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkurose <kkurose@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:34:41 by federico          #+#    #+#             */
/*   Updated: 2025/09/12 16:01:58 by kkurose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_file_name(char *file_path)
{
	int	i;

	if (file_path == NULL || str_len(file_path) < str_len("x.cub"))
	{
		print_err("Error\nInvalid file name: ");
		print_err(file_path);
		print_err("\n");
		return (FAILURE);
	}
	i = str_len(file_path) - 1;
	while (i > 0 && (file_path[i] == ' ' || file_path[i] == '\t'))
		i--;
	if (file_path[i] != 'b' || file_path[i - 1] != 'u'
		|| file_path[i - 2] != 'c' || file_path[i - 3] != '.')
	{
		print_err("Error\nInvalid file name: ");
		print_err(file_path);
		print_err("\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

bool	check_file_access(char *file_path)
{
	int		fd;
	char	check_buffer[10];
	int		check;

	fd = open(file_path, O_RDONLY, 0);
	if (fd == -1)
	{
		print_err("Error\ncouldn't open the file\n");
		return (FAILURE);
	}
	check = read(fd, check_buffer, 0);
	if (check == -1)
	{
		close(fd);
		print_err("Error\ncouldn't read from the file\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

bool	cub_file_is_ok(int argc, char *file_path)
{
	if (argc != 2)
	{
		print_err("Error\nwrong number of arguments\n");
		return (FAILURE);
	}
	if (check_file_name(file_path) == FAILURE)
		return (FAILURE);
	if (check_file_access(file_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
