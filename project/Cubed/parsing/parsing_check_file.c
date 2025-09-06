/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:34:41 by federico          #+#    #+#             */
/*   Updated: 2025/09/01 19:37:12 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

bool	check_file_name(char *file_path)
{
	int	i;

	if (file_path == NULL || str_len(file_path) < str_len("x.cub"))
	{
		print_error("Error\nInvalid file name: ");
		print_error(file_path);
		print_error("\n");
		return (FAILURE);
	}
	i = str_len(file_path) - 1;
	while (i > 0 && (file_path[i] == ' ' || file_path[i] == '\t'))
		i--;
	if (file_path[i] != 'b' || file_path[i - 1] != 'u'
		|| file_path[i - 2] != 'c' || file_path[i - 3] != '.')
	{
		print_error("Error\nInvalid file name: ");
		print_error(file_path);
		print_error("\n");
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
		print_error("Error\ncouldn't open the file\n");
		return (FAILURE);
	}
	check = read(fd, check_buffer, 0);
	if (check == -1)
	{
		close(fd);
		print_error("Error\ncouldn't read from the file\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

bool	cub_file_is_ok(int argc, char *file_path)
{
	if (argc != 2)
	{
		print_error("Error\nwrong number of arguments\n");
		return (FAILURE);
	}
	if (check_file_name(file_path) == FAILURE)
		return (FAILURE);
	if (check_file_access(file_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
