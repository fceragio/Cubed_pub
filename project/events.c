/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico <federico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:06 by federico          #+#    #+#             */
/*   Updated: 2025/06/29 01:20:00 by federico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	hook_handlers(t_program *program)
{
	mlx_hook(program->win, DestroyNotify, StructureNotifyMask, red_x_press_handling, program);
	mlx_hook(program->win, VisibilityNotify, VisibilityChangeMask, visibility_handling, program);
	mlx_hook(program->win, KeyPress, KeyPressMask, key_press_handling, program);
}

int	red_x_press_handling(t_program *program)
{
	program_close(program, SUCCESS);
	return (SUCCESS);
}

int	visibility_handling(t_program *program)
{
	(void)program;
	return (SUCCESS);
}

int	key_press_handling(int keysym, t_program *program)
{
	if (keysym == XK_Escape)
		program_close(program, SUCCESS);
	else if (keysym == XK_Left || keysym == XK_Right)
		turn_pov(keysym, program);
	else if (keysym == XK_w || keysym == XK_a
		|| keysym == XK_s || keysym == XK_d)
		move_pov(keysym, program);
	else
		return (FAILURE);
	return (SUCCESS);
}

void	move_pov(int keysym, t_program *program)
{
	if (keysym == XK_w)
		move_forward(program);
	else if (keysym == XK_s)
		move_backward(program);
	else if (keysym == XK_a)
		move_left(program);
	else if (keysym == XK_d)
		move_right(program);
	player_aim_init(program->player, program);
}

void	move_forward(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x + safe_cos(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y + safe_sin(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}
void	move_backward(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x - safe_cos(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y - safe_sin(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}
void	move_left(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x + safe_sin(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y - safe_cos(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}
void	move_right(t_program *program)
{
	double	angle;
	double	tmp_x;
	double	tmp_y;

	angle = program->player->angle;
	tmp_x = program->player->x - safe_sin(angle) * SPEED;
	if (not_wall(tmp_x, program->player->y, program))
		program->player->x = tmp_x;
	tmp_y = program->player->y + safe_cos(angle) * SPEED;
	if (not_wall(program->player->x, tmp_y, program))
		program->player->y = tmp_y;
}

void	turn_pov(int keysym, t_program *program)
{
	if (keysym == XK_Left)
		turn_left(program);
	else
		turn_right(program);
	player_aim_init(program->player, program);
}

void	turn_left(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp - M_PI / 16;
	if (program->player->angle < 0)
		program->player->angle += 2 * M_PI;
}

void	turn_right(t_program *program)
{
	double	temp;

	temp = program->player->angle;
	program->player->angle = temp + M_PI / 16;
	if (program->player->angle >= (2 * M_PI))
		program->player->angle = 0;
}

// ✅ Soluzione: gestione dello stato dei tasti manualmente

// Anziché reagire direttamente all’evento key_press, devi:

//     Registrare quali tasti sono premuti.

//     In loop_hook, muovere il personaggio ogni frame in base allo stato corrente dei tasti.

// 🔧 1. Aggiungi una struttura per i tasti

// Nel tuo t_program puoi aggiungere:

// typedef struct s_keys
// {
// 	bool	w;
// 	bool	a;
// 	bool	s;
// 	bool	d;
// 	bool	left;
// 	bool	right;
// }	t_keys;

// Poi nel tuo t_program:

// typedef struct s_program
// {
// 	// ...
// 	t_keys	keys;
// 	// ...
// }	t_program;

// 🎯 2. Gestisci key_press e key_release

// int	key_press(int keycode, t_program *program)
// {
// 	if (keycode == W_KEY)
// 		program->keys.w = true;
// 	else if (keycode == A_KEY)
// 		program->keys.a = true;
// 	else if (keycode == S_KEY)
// 		program->keys.s = true;
// 	else if (keycode == D_KEY)
// 		program->keys.d = true;
// 	else if (keycode == LEFT_KEY)
// 		program->keys.left = true;
// 	else if (keycode == RIGHT_KEY)
// 		program->keys.right = true;
// 	return (0);
// }

// int	key_release(int keycode, t_program *program)
// {
// 	if (keycode == W_KEY)
// 		program->keys.w = false;
// 	else if (keycode == A_KEY)
// 		program->keys.a = false;
// 	else if (keycode == S_KEY)
// 		program->keys.s = false;
// 	else if (keycode == D_KEY)
// 		program->keys.d = false;
// 	else if (keycode == LEFT_KEY)
// 		program->keys.left = false;
// 	else if (keycode == RIGHT_KEY)
// 		program->keys.right = false;
// 	return (0);
// }

// Non dimenticare di registrare gli hook nel tuo hook_handlers:

// mlx_hook(program->win, 2, 1L << 0, key_press, program);
// mlx_hook(program->win, 3, 1L << 1, key_release, program);

// 🚀 3. Muovi il personaggio in loop_hook

// Nel tuo loop_hook, dopo il controllo del timer FPS:

// void	update_player(t_program *program)
// {
// 	if (program->keys.w)
// 		move_forward(program->player);
// 	if (program->keys.s)
// 		move_backward(program->player);
// 	if (program->keys.a)
// 		strafe_left(program->player);
// 	if (program->keys.d)
// 		strafe_right(program->player);
// 	if (program->keys.left)
// 		rotate_left(program->player);
// 	if (program->keys.right)
// 		rotate_right(program->player);
// }

// Poi in loop_hook:

// if (total_us >= U_FPS)
// {
// 	update_player(program);
// 	render(program);
// 	// ...
// }
