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









int	spawns_ok(char **char_map)
{
	return (1);
}
int	map_is_closed(char **char_map)
{
	return (1);
}

int	blueprint_map_ok(char **char_map)
{
	if (spawns_ok(char_map) == FAILURE)
	{
		print_error("Error\nWrong number of spwan points in the map\n");
		return (FAILURE);
	}
	if (map_is_closed(char_map) == FAILURE)
	{
		print_error("Error\nMap is not properly closed by walls\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

char	**create_char_map(t_list *map_list)
{
	return (NULL);
}


int	blueprint_ok(t_map_blueprint *blueprint)
{
	if (blueprint->No_flag == false || blueprint->So_flag == false
		|| blueprint->We_flag == false || blueprint->Ea_flag == false
		|| blueprint->C_flag == false || blueprint->F_flag == false)
	{
		print_error("Error\nThe file didn't contai all the fields required\n");
		return (FAILURE);
	}
	blueprint->char_map = create_char_map(blueprint->map_list);
	if (blueprint_map_ok(blueprint->char_map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_map	*blueprint_to_map(t_map_blueprint *blueprint)
{
	return (NULL);
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
	blueprint->char_map = NULL;
	blueprint->char_map_len = 0;
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

void	clear_char_map(char **char_map)
{
	int	i;

	if (char_map == NULL)
		return ;
	i = 0;
	while (char_map[i])
	{
		free(char_map[i]);
		i++;
	}
	free(char_map);
}

void	clear_blueprint(t_map_blueprint **blueprint)
{
	printf("clearing blueprint\n");
	t_list	*temp;

	if ((*blueprint) == NULL)
		return ;
	printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", (*blueprint)->No, (*blueprint)->So, (*blueprint)->We, (*blueprint)->Ea, (*blueprint)->C, (*blueprint)->F);
	free((*blueprint)->No);
	free((*blueprint)->So);
	free((*blueprint)->We);
	free((*blueprint)->Ea);
	free((*blueprint)->C);
	free((*blueprint)->F);
	while((*blueprint)->map_list)
	{
		temp = (*blueprint)->map_list->next;
		printf("%s\n", (*blueprint)->map_list->content);
		free((*blueprint)->map_list->content);
		free((*blueprint)->map_list);
		(*blueprint)->map_list = temp;
	}
	clear_char_map((*blueprint)->char_map);
	free(*blueprint);
	(*blueprint) = NULL;
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
	printf("blueprint created\n");
	return (create_map(&map_blueprint));
}







t_list	*list_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	list_append(char *content, t_list **list)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		perror("list_append malloc\n");
		exit(1);
	}
	new->content = content;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		last = list_last(*list);
		last->next = new;
	}
}

int	list_len(t_list *list)
{
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
