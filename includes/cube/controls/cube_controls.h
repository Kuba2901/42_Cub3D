/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_controls.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:45:18 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_CONTROLS_H
# define CUBE_CONTROLS_H

# include <cube.h>

/* controls.c */
void	input_handler_action(t_cube *cube);
void	mov_handler(t_cube *cube);

/* controls_movement.c */
void	handle_left_right(t_cube *cube, double move_speed);
void	handle_for_back(t_cube *cube, double move_speed);
t_bool	is_walkable(t_cube *cube, t_point pt);

/* controls_rotation.c */
void	handle_rotation_right(t_cube *cube, double r_speed);
void	handle_rotation_left(t_cube *cube, double r_speed);
void	handle_rotation(t_cube *cube, double r_speed);

/* controls_input.c */
int		input_handler_key_press(int key_code, t_cube *cube);
int		input_handler_key_release(int key_code, t_cube *cube);

/* controls_mouse.c */
int		input_handler_mouse_movement(int x, int y, t_cube *cube);

#endif