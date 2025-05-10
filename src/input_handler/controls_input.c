/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:51:31 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_input_handler.h>
#include <cube.h>
#include <cube_entities.h>
#include <cube_runtime.h>
#include <cube_controls.h>

int	input_handler_key_press(int key_code, t_cube *cube)
{
	t_input_handler_keys	*keys;

	keys = cube->input_handler->keys;
	if (key_code == KEY_W)
		keys->w = 1;
	else if (key_code == KEY_A)
		keys->a = 1;
	else if (key_code == KEY_S)
		keys->s = 1;
	else if (key_code == KEY_D)
		keys->d = 1;
	else if (key_code == KEY_ARROW_LEFT)
		keys->left = 1;
	else if (key_code == KEY_ARROW_RIGHT)
		keys->right = 1;
	else if (key_code == KEY_ESC)
		keys->escape = 1;
	else if (key_code == KEY_E)
	{
		keys->e = 1;
	}
	return (0);
}

int	input_handler_key_release(int key_code, t_cube *cube)
{
	t_input_handler_keys	*keys;

	keys = cube->input_handler->keys;
	if (key_code == KEY_W)
		keys->w = 0;
	else if (key_code == KEY_A)
		keys->a = 0;
	else if (key_code == KEY_S)
		keys->s = 0;
	else if (key_code == KEY_D)
		keys->d = 0;
	else if (key_code == KEY_ARROW_LEFT)
		keys->left = 0;
	else if (key_code == KEY_ARROW_RIGHT)
		keys->right = 0;
	else if (key_code == KEY_E)
		keys->e = 0;
	return (0);
}
