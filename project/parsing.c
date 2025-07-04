/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:24:23 by federico          #+#    #+#             */
/*   Updated: 2025/07/05 03:20:28 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

t_map	*create_map(t_map_blueprint *blueprint)
{
	printf("create map\n");
	if (blueprint == NULL)
		return (NULL);
	printf("createmap clearing blueprint\n");
	clear_blueprint(blueprint);
	return (NULL);
}





void	blueprint_init(t_map_blueprint *blueprint)
{
	blueprint->No_flag = false;
	blueprint->So_flag = false;
	blueprint->We_flag = false;
	blueprint->Ea_flag = false;
	blueprint->C_flag = false;
	blueprint->F_flag = false;
	blueprint->No = NULL;
	blueprint->So = NULL;
	blueprint->We = NULL;
	blueprint->Ea = NULL;
	blueprint->C = NULL;
	blueprint->F = NULL;
	blueprint->map_list = NULL;
}

int	check_N_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'O')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			return (M_NO);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}
int	check_S_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'O')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			return (M_SO);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}
int	check_W_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'E')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			return (M_WE);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}
int	check_E_line(char *line)
{
	int	i;

	i = 1;
	if (line[i] == 'A')
	{
		i++;
		if (line[i] == ' ' || line[i] == '\t')
			return (M_EA);
		else
			return (M_ERR);
	}
	else
		return (M_ERR);
}

int	identify_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (M_MAP);
	if (line[i] == '\n' || line[i] == '\0')
		return (M_SKIP);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (M_C);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (M_F);
	else if (line[i] == 'N')
		return (check_N_line(line + i));
	else if (line[i] == 'S')
		return (check_S_line(line + i));
	else if (line[i] == 'W')
		return (check_W_line(line + i));
	else if (line[i] == 'E')
		return (check_E_line(line + i));
	else
		return (M_ERR);
}

int	assign_line_NO(char *line, t_map_blueprint *blueprint)
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
int	assign_line_SO(char *line, t_map_blueprint *blueprint)
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
int	assign_line_WE(char *line, t_map_blueprint *blueprint)
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
int	assign_line_EA(char *line, t_map_blueprint *blueprint)
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
int	assign_line_C(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->C_flag == true)
	{
		print_error("Error\nMore lines contain cealing color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->C_flag = true;
	blueprint->C = line;
	return (SUCCESS);
}
int	assign_line_F(char *line, t_map_blueprint *blueprint)
{
	if (blueprint->F_flag == true)
	{
		print_error("Error\nMore lines contain floor color\n");
		free(line);
		return (FAILURE);
	}
	blueprint->F_flag = true;
	blueprint->F = line;
	return (SUCCESS);
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

int	assign_map_line(char *line, t_map_blueprint *blueprint)
{
	free(line);
	return (FAILURE);
}

void	clear_blueprint(t_map_blueprint *blueprint)
{
	printf("clearing blueprint\n");
	t_list	*temp;

	if (blueprint == NULL)
		return ;
	printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", blueprint->No, blueprint->So, blueprint->We, blueprint->Ea, blueprint->C, blueprint->F);
	free(blueprint->No);
	free(blueprint->So);
	free(blueprint->We);
	free(blueprint->Ea);
	free(blueprint->C);
	free(blueprint->F);
	while(blueprint->map_list)
	{
		temp = blueprint->map_list->next;
		free(blueprint->map_list->content);
		free(blueprint->map_list);
		blueprint->map_list = temp;
	}
	blueprint = NULL;
}

void	create_map_blueprint(t_map_blueprint *blueprint, int fd)
{
	char	*next_line;

	blueprint_init(blueprint);
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (identify_line(next_line) == M_MAP)
			break ;
		if (assign_line(next_line, blueprint) == FAILURE)
		{
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
	while (next_line)
	{
		if (assign_map_line(next_line, blueprint) == FAILURE)
		{
			clear_blueprint(blueprint);
			return ;
		}
		next_line = get_next_line(fd);
	}
}

t_map	*parsing(int argc, char *file_path)
{
	t_map_blueprint	map_blueprint;
	int				fd;

	if (cub_file_is_ok(argc, file_path) == FAILURE)
		return (NULL);
	fd = open(file_path, O_RDONLY, 0);
	create_map_blueprint(&map_blueprint, fd);
	close(fd);
	printf("blueprint created\n");
	return (create_map(&map_blueprint));
}
