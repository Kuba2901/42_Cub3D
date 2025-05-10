/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:48:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_input_handler.h>
#include <cube.h>
#include <cube_entities.h>
#include <math.h>
#include <cube_controls.h>

void	handle_rotation_right(t_cube *cube, double r_speed)
{
	t_player	*player;
	t_vector	dir_vect;
	t_vector	camera_vect;

	player = cube->entities->player;
	dir_vect.dir_x = player->dir.dir_x * cos(-r_speed)
		- player->dir.dir_y * sin(-r_speed);
	dir_vect.dir_y = player->dir.dir_x * sin(-r_speed)
		+ player->dir.dir_y * cos(-r_speed);
	camera_vect.dir_x = player->camera.dir_x * cos(-r_speed)
		- player->camera.dir_y * sin(-r_speed);
	camera_vect.dir_y = player->camera.dir_x * sin(-r_speed)
		+ player->camera.dir_y * cos(-r_speed);
	player->dir = dir_vect;
	player->camera = camera_vect;
}

void	handle_rotation_left(t_cube *cube, double r_speed)
{
	t_player	*player;
	t_vector	dir_vect;
	t_vector	camera_vect;

	player = cube->entities->player;
	dir_vect.dir_x = player->dir.dir_x * cos(r_speed)
		- player->dir.dir_y * sin(r_speed);
	dir_vect.dir_y = player->dir.dir_x * sin(r_speed)
		+ player->dir.dir_y * cos(r_speed);
	camera_vect.dir_x = player->camera.dir_x * cos(r_speed)
		- player->camera.dir_y * sin(r_speed);
	camera_vect.dir_y = player->camera.dir_x * sin(r_speed)
		+ player->camera.dir_y * cos(r_speed);
	player->dir = dir_vect;
	player->camera = camera_vect;
}

void	handle_rotation(t_cube *cube, double r_speed)
{
	if (cube->input_handler->keys->right)
		handle_rotation_right(cube, r_speed);
	else if (cube->input_handler->keys->left)
		handle_rotation_left(cube, r_speed);
}
