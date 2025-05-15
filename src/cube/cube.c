/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:50:58 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/15 16:39:21 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_settings_args.h>
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
#include <parse_mandatory.h>
#include <parse_map_utils.h>

t_cube	*cube_cube_init(int argc, char **argv)
{
	t_cube			*cube;
	t_parser_config	*parser_config;

	printf("0... Checking program arguments\n");
	check_args(argc, argv);

	parser_config = init_parser_config(argv[1]);
	if (!parser_config)
	{
		printf("Error\nFailed to initialize parser_config\n");
		exit(EXIT_FAILURE);
	}
	printf("1... Initialized parser_config\n");

	parse(parser_config);
	printf("2... Parsing completed\n");

	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (NULL);
	cube->mlx_handler = mlx_mlx_handler_init();
	printf("2... Initialized mlx_handler\n");

	cube->cube_settings = settings_cube_init(settings_map_config_init(parser_config->map_config->map,
			parser_config->map_config->width, parser_config->map_config->height),
	settings_tex_config_init(parser_config->textures_paths, cube->mlx_handler, parser_config->ceiling_color, parser_config->floor_color));
	printf("3... Initialized cube_settings\n");
	
	cube->entities = entities_entities_init(entities_entities_config_init(cube->cube_settings));
	printf("4... Initialized entities\n");
	
	cube->map = map_map_init(cube->cube_settings->map_config);
	cube->runtime_handler = runtime_runtime_handler_init();
	cube->input_handler = input_handler_init();
	cube->dda_data = dda_init();
	cube->audio_system = audio_system_init();
	free_parser_config(parser_config, NULL, NULL);
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
