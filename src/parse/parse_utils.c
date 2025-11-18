/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:17:13 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/20 16:55:04 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>

void	parse_free_static_buff(int fd)
{
	char	*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	init_parser_color(t_parser_config *parser_config,
	t_color *color)
{
	if (!color)
		return ;
	color->parser_config = parser_config;
	color->b = 0;
	color->g = 0;
	color->r = 0;
}

t_color	*parser_color_create(t_parser_config *parser_config)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	init_parser_color(parser_config, color);
	return (color);
}
