/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:50:58 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 19:38:24 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_settings.h>
#include <cube_entities.h>
#include <cube_input_handler.h>
#include <cube_mlx_handler.h>
#include <cube_runtime.h>
#include <cube_dda.h>
#include <cube_audio.h>
#include <stdio.h>
#include <cube_drawing.h>
#include <cube_audio_integration.h>

t_cube	*cube_cube_init(char **map, int width, int height,
	const char **tex_paths)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (NULL);
	cube->mlx_handler = mlx_mlx_handler_init();
	cube->cube_settings = settings_cube_init(
			settings_map_config_init(map, width, height),
			settings_tex_config_init(tex_paths, cube->mlx_handler));
	cube->entities = entities_entities_init(
			entities_entities_config_init(cube->cube_settings));
	cube->map = map_map_init(cube->cube_settings->map_config);
	cube->runtime_handler = runtime_runtime_handler_init();
	cube->input_handler = input_handler_init();
	cube->dda_data = dda_init();
	cube->audio_system = audio_system_init();
	return (cube);
}

void	cube_cube_free(t_cube *cube)
{
	if (cube->runtime_handler->display_credits)
	{
		audio_integration_handle_exit(cube);
		credits_display(cube);
	}
	cube->runtime_handler->running = CUBE_FALSE;
	map_map_free(cube->map);
	input_handler_free(cube->input_handler);
	entities_entities_free(cube->entities);
	settings_cube_free(cube->cube_settings);
	if (cube->audio_system)
		audio_system_shutdown(cube->audio_system);
	mlx_mlx_handler_free(cube->mlx_handler);
	runtime_runtime_handler_free(cube->runtime_handler);
	dda_free(cube->dda_data);
	safe_free(cube);
	exit(EXIT_SUCCESS);
}
