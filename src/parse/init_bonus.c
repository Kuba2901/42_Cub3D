/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:01:39 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 21:28:24 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	init_bonus_parser_map_config(t_parser_config *parser_config, \
										char *filename)
{
	parser_config->map_config = (t_map_parse *)malloc(sizeof(t_map_parse));
	if (!parser_config->map_config)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for map_config\n");
	parser_config->map_config->fd = open(filename, O_RDONLY);
	if (parser_config->map_config->fd < 0)
		free_parser_config(parser_config, NULL, \
			"Error\nFailed to open file\n");
	parser_config->map_config->parsing_map = 0;
	parser_config->map_config->height = 0;
	parser_config->map_config->width = 0;
	parser_config->map_config->map = NULL;
}

void	init_bonus_parser_textures_paths(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	parser_config->textures_paths = (char **)malloc(sizeof(char *) * \
										TEXTURE_TYPES_COUNT);
	if (!parser_config->textures_paths)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for textures_config\n");
	parser_config->ceiling_color = parser_color_create(parser_config);
	if (!parser_config->ceiling_color)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for ceiling_color\n");
	parser_config->floor_color = parser_color_create(parser_config);
	if (!parser_config->floor_color)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for floor_color\n");
	while (++i < TEXTURE_TYPES_COUNT)
		parser_config->textures_paths[i] = NULL;
}

t_parser_config	*init_parser_config(char *filename)
{
	t_parser_config	*parser_config;

	parser_config = (t_parser_config *)malloc(sizeof(t_parser_config));
	if (!parser_config)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for parser_config\n");
	init_bonus_parser_map_config(parser_config, filename);
	init_bonus_parser_textures_paths(parser_config);
	
	return (parser_config);
}

void	free_bonus_parser_map_config(t_map_parse *map_config)
{
	int	i;

	i = -1;
	if (map_config->map)
	{
		while (++i < (int)map_config->height)
			safe_free(map_config->map[i]);
		free(map_config->map);
	}
	if (map_config->fd > 0)
	{
		parse_free_static_buff(map_config->fd);
		close(map_config->fd);
	}
	map_config->fd = -1;
	free(map_config);
}

void	free_parser_config(t_parser_config *parser_config, \
									char *line, char *error)
{
	int	i;

	i = -1;
	safe_free(line);
	if (!parser_config)
		return ;
	if (error)
		parser_config->map_config->height -= 1;
	if (parser_config->map_config)
		free_bonus_parser_map_config(parser_config->map_config);
	if (parser_config->textures_paths)
	{
		i = -1;
		while (++i < TEXTURE_TYPES_COUNT)
			free(parser_config->textures_paths[i]);
		free(parser_config->textures_paths);
		if (parser_config->ceiling_color)
			free(parser_config->ceiling_color);
		if (parser_config->floor_color)
			free(parser_config->floor_color);
	}
	free(parser_config);
	if (error)
	{
		ft_putstr_fd(error, 2);
		exit(EXIT_FAILURE);
	}
	return ;
}
