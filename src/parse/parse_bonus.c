/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:48:44 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/23 17:46:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>
#include <parse_map_utils.h>

void	parse_bonus_line(t_parser_config *parser_config, char *line)
{
	if (is_bonus_map_line(line))
		parse_bonus_map_line(parser_config, line);
	else if (!parser_config->map_config->parsing_map)
		parse_bonus_texture(parser_config, line);
	else
		free_parser_config(parser_config, line,
			"Error\nInvalid line after map started\n");
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
				free_parser_config(parser_config, line,
					"Error\nEmpty line after map parsing has started\n");
			free(line);
			line = get_next_line(parser_config->map_config->fd);
			continue ;
		}
		parse_bonus_line(parser_config, line);
		free(line);
		line = get_next_line(parser_config->map_config->fd);
	}
	realloc_map_with_max_width(parser_config);
	check_parsed_bonus_textures(parser_config);
	check_starting_pos_map(parser_config);
	check_map_walls(parser_config);
	check_exit(parser_config);
}
