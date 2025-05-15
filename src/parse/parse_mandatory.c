/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:27:02 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 16:41:32 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	parse_line(t_parser_config *parser_config, char *line)
{
	if (is_map_line(line))
		parse_map_line(parser_config, line);
	else if (!parser_config->map_config->parsing_map)
		parse_texture_or_color(parser_config, line);
	else
		free_parser_config(parser_config, line, \
			"Error\nInvalid line after map parsing has started\n");
}

void	parse(t_parser_config *parser_config)
{
	char	*line;

	line = get_next_line(parser_config->map_config->fd);
	if (!line)
		free_parser_config(parser_config, NULL, "Error\nEmpty file\n");
	while (line != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (parser_config->map_config->parsing_map == 1)
				free_parser_config(parser_config, line, \
					"Error\nEmpty line after map parsing has started\n");
			free(line);
			line = get_next_line(parser_config->map_config->fd);
			continue ;
		}
		parse_line(parser_config, line);
		free(line);
		line = get_next_line(parser_config->map_config->fd);
	}
	realloc_map_with_max_width(parser_config);
	check_parsed_mandatory_textures(parser_config);
	check_starting_pos_map(parser_config);
	check_map_walls(parser_config);
}
