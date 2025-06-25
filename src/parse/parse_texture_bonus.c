/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:35:16 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/25 12:16:56 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	parse_and_check_bonus_texture(t_parser_config *parser_config,
	t_tex_type tex_type, char *line)
{
	if (parser_config->textures_paths[tex_type])
		free_parser_config(parser_config, line,
			"Error\nTexture path already set\n");
	parser_config->textures_paths[tex_type] = ft_strdup(line);
	if (!parser_config->textures_paths[tex_type])
		free_parser_config(parser_config, line,
			"Error\nMemory allocation failed for texture path\n");
}

void	parse_bonus_texture(t_parser_config *parser_config, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strncmp(line, "NO", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_NORTH, line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_SOUTH, line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_WEST, line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_EAST, line);
	else if (ft_strncmp(line, "FL", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_FLOOR, line);
	else if (ft_strncmp(line, "CE", 2) == 0)
		parse_and_check_bonus_texture(parser_config, TEX_TYPE_CEILING, line);
	else
		free_parser_config(parser_config, line,
			"Error\nInvalid texture line\n");
}

void	check_parsed_bonus_textures(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	while (++i < TEXTURE_TYPES_COUNT)
	{
		if (parser_config->textures_paths[i] == NULL)
			free_parser_config(parser_config, NULL,
				"Error\nMissing texture path\n");
	}
}
