/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:46:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 21:24:07 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	init_parser_map_config(t_parser_config *parser_config, char *filename)
{
	parser_config->map_config = (t_map_parse *)malloc(sizeof(t_map_parse));
	if (!parser_config->map_config)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for map_config\n");
	parser_config->map_config->fd = open(filename, O_RDONLY);
	if (parser_config->map_config->fd < 0)
		free_parser_config(parser_config, NULL, "Error\nFailed to open file\n");
	parser_config->map_config->parsing_map = 0;
	parser_config->map_config->height = 0;
	parser_config->map_config->width = 0;
	parser_config->map_config->map = NULL;
}

void	init_parser_textures_and_colors(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	parser_config->textures_paths = (char **)malloc(sizeof(char *) * \
										TEXTURE_TYPES_COUNT_MANDATORY);
	if (!parser_config->textures_paths)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for textures_config\n");
	while (++i < TEXTURE_TYPES_COUNT_MANDATORY)
		parser_config->textures_paths[i] = NULL;
	parser_config->ceiling_color = parser_color_create(parser_config);
	if (!parser_config->ceiling_color)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for ceiling_color\n");
	parser_config->floor_color = parser_color_create(parser_config);
	if (!parser_config->floor_color)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for floor_color\n");
}

t_parser_config	*init_parser_config(char *filename)
{
	t_parser_config	*parser_config;

	parser_config = (t_parser_config *)malloc(sizeof(t_parser_config));
	if (!parser_config)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for parser_config\n");
	init_parser_map_config(parser_config, filename);
	init_parser_textures_and_colors(parser_config);
	return (parser_config);
}
