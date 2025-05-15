/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:43:00 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 16:59:59 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_map_utils.h>
#include <parse_mandatory.h>

char	**realloc_map(char **map, size_t new_size)
{
	char	**new_map;
	size_t	i;

	i = -1;
	new_map = (char **)malloc(sizeof(char *) * new_size);
	if (!new_map)
		return (NULL);
	while (++i < new_size - 1)
		new_map[i] = map[i];
	free(map);
	return (new_map);
}

void	free_new_map(t_parser_config *parser_config, char **new_map, int i)
{
	while (--i >= 0)
		free(new_map[i]);
	free(new_map);
	free_parser_config(parser_config, NULL, \
		"Error\nMemory allocation failed for new_line\n");
}

void	copy_and_pad_map_line(char *new_line, char *src_line, size_t width)
{
	int	j;

	j = -1;
	while (++j < (int)width)
	{
		if (j >= (int)ft_strlen(src_line))
			new_line[j] = ' ';
		else
			new_line[j] = src_line[j];
	}
	new_line[j] = '\0';
}

void	realloc_map_with_max_width(t_parser_config *parser_config)
{
	char	**new_map;
	int		i;

	i = -1;
	new_map = (char **)malloc(sizeof(char *) * \
		parser_config->map_config->height);
	if (!new_map)
		free_parser_config(parser_config, NULL, \
			"Error\nMemory allocation failed for new_map\n");
	while (++i < (int)parser_config->map_config->height)
	{
		new_map[i] = (char *)malloc(sizeof(char) * \
			(parser_config->map_config->width + 1));
		if (!new_map[i])
			free_new_map(parser_config, new_map, i);
		copy_and_pad_map_line(new_map[i], parser_config->map_config->map[i], \
			parser_config->map_config->width);
		free(parser_config->map_config->map[i]);
	}
	free(parser_config->map_config->map);
	parser_config->map_config->map = new_map;
}
