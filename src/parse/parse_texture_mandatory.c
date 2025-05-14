/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mandatory_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:29:31 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/14 15:26:40 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>

void	parse_texture(t_parser_config *parser_config, \
						t_tex_type_mandatory tex_type, char *line)
{
	parser_config->textures_paths[tex_type] = ft_strdup(line);
	if (!parser_config->textures_paths[tex_type])
		free_parser_config(parser_config, line, \
			"Error\nMemory allocation failed for texture path\n");
}

void	parse_color(t_color *color, char *line)
{
	char	**split;
	int		i;

	i = 0;
	while (line[i] && ('0' > line[i] || line[i] > '9'))
		i++;
	split = ft_split(line + i, ',');
	if (!split)
		free_parser_config(color->parser_config, line, \
			"Error\nMemory allocation failed for color\n");
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL)
		free_parser_config(color->parser_config, line, \
			"Error\nInvalid color formatsdkfndkfn\n");
	if (ft_strlen(split[0]) > 3 || ft_strlen(split[1]) > 3 || \
		ft_strlen(split[2]) > 3)
		free_parser_config(color->parser_config, line, \
			"Error\nInvalid color format\n");
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	if (color->r < 0 || color->r > 255 || \
		color->g < 0 || color->g > 255 || \
		color->b < 0 || color->b > 255)
		free_parser_config(color->parser_config, line, \
			"Error\nInvalid color value\n");
}

void	parse_texture_or_color(t_parser_config *parser_config, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strncmp(line, "NO", 2) == 0)
		parse_texture(parser_config, TEX_NORTH, line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_texture(parser_config, TEX_SOUTH, line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_texture(parser_config, TEX_WEST, line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_texture(parser_config, TEX_EAST, line);
	else if (ft_strncmp(line, "F", 1) == 0)
		parse_color(parser_config->floor_color, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_color(parser_config->ceiling_color, line);
	else
		free_parser_config(parser_config, line, \
			"Error\nInvalid texture line\n");
}

void	check_parsed_mandatory_textures(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	while (++i < TEXTURE_TYPES_COUNT_MANDATORY)
	{
		if (parser_config->textures_paths[i] == NULL)
			free_parser_config(parser_config, NULL, \
				"Error\nMissing texture path\n");
	}
}
