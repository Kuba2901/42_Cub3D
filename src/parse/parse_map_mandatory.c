/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mandatory_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:26:28 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/13 16:11:17 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_mandatory.h>

int	is_map_line(char *line)
{
	int	i;
	int	valid_char;

	i = -1;
	valid_char = 0;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && \
			line[i] != ' ' && line[i] != '\t' && \
			line[i] != 'N' && line[i] != 'S' && \
			line[i] != 'E' && line[i] != 'W')
		{
			if ((line[i] == '\n' || line[i] == '\0') && valid_char == 1)
				continue ;
			return (0);
		}
		else if (line[i] != ' ' && line[i] != '\t')
			valid_char = 1;
	}
	return (1);
}

void	parse_map_line(t_parser_config *pc, char *line)
{
	if (!pc->map_config->parsing_map)
	{
		pc->map_config->map = (char **)malloc(sizeof(char *) * 1);
		if (!pc->map_config->map)
			free_parser_config(pc, line, \
				"Error\nMemory allocation failed for map\n");
		pc->map_config->parsing_map = 1;
		pc->map_config->height = 1;
	}
	pc->map_config->map = realloc_map(pc->map_config->map, \
		pc->map_config->height);
	if (!pc->map_config->map)
		free_parser_config(pc, line, \
			"Error\nMemory allocation failed for new_map\n");
	pc->map_config->map[pc->map_config->height - 1] = replace_tabs(line);
	if (!pc->map_config->map[pc->map_config->height - 1])
		free_parser_config(pc, line, \
			"Error\nMemory allocation failed for new_line\n");
	if (pc->map_config->height < \
		ft_strlen(pc->map_config->map[pc->map_config->height - 1]))
		pc->map_config->width \
			= ft_strlen(pc->map_config->map[pc->map_config->height - 1]);
	pc->map_config->height++;
}
