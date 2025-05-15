/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:01:25 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 17:01:56 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	free_parser_map_config(t_map_parse *map_config)
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
		close(map_config->fd);
	map_config->fd = -1;
	free(map_config);
}

void	free_parser_textures_and_colors(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	if (parser_config->textures_paths)
	{
		while (++i < TEXTURE_TYPES_COUNT_MANDATORY)
			safe_free(parser_config->textures_paths[i]);
		free(parser_config->textures_paths);
	}
	if (parser_config->ceiling_color)
		free(parser_config->ceiling_color);
	if (parser_config->floor_color)
		free(parser_config->floor_color);
}

void	free_parser_config(t_parser_config *parser_config, char *line, \
	char *error)
{
	safe_free(line);
	if (!parser_config)
		return ;
	if (parser_config->map_config)
		free_parser_map_config(parser_config->map_config);
	if (parser_config->textures_paths || \
		parser_config->floor_color || \
		parser_config->ceiling_color)
		free_parser_textures_and_colors(parser_config);
	free(parser_config);
	if (error)
	{
		ft_putstr_fd(error, 2);
		exit(EXIT_FAILURE);
	}
	return ;
}
