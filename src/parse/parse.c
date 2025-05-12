/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:48:44 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/12 10:44:29 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

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
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && \
			line[i] != 'Q' && line[i] != 'X')
		{
			if ((line[i] == '\n'|| line[i] == '\0') && valid_char == 1)
				continue;
			return (0);
		}
		else if (line[i] != ' ' && line[i] != '\t')
			valid_char = 1;
	}
	return (1);
}

char	*replace_tabs(char *line)
{
	int		i;
	int		j;
	int		k;
	int		spaces;
	char	*new_line;

	i = -1;
	spaces = 0;
	while (line[++i])
	{
		if (line[i] == '\t')
			spaces += TAB_WIDTH - 1;
	}
	if (line[i - 1] != '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + spaces));
	if (!new_line)
		return (NULL);
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
		{
			k = -1;
			while (++k < TAB_WIDTH)
				new_line[++j] = ' ';
		}
		else if (line[i] == '\n')
		{
			new_line[++j] = '\0';
			printf("j: %d\n", j);
			return (new_line);
		}
		else
			new_line[++j] = line[i];
	}
	new_line[++j] = '\0';
	return (new_line);
}

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

void	parse_map_line(t_parser_config *parser_config, char *line)
{
	if (!parser_config->map_config->parsing_map)
	{
		parser_config->map_config->map = (char **)malloc(sizeof(char *) * 1);
		if (!parser_config->map_config->map)
		{
			free(line);
			free_parser_config(parser_config, "Error\nMemory allocation failed for map\n");
		}
		parser_config->map_config->parsing_map = 1;
		parser_config->map_config->height = 1;
	}
	parser_config->map_config->map = realloc_map(parser_config->map_config->map, parser_config->map_config->height);
	if (!parser_config->map_config->map)
	{
		free(line);
		free_parser_config(parser_config, "Error\nMemory allocation failed for new_map\n");
	}
	parser_config->map_config->map[parser_config->map_config->height - 1] = replace_tabs(line);
	if (!parser_config->map_config->map[parser_config->map_config->height - 1])
	{
		free(line);
		free_parser_config(parser_config, "Error\nMemory allocation failed for new_line\n");
	}
	if (parser_config->map_config->height < ft_strlen(parser_config->map_config->map[parser_config->map_config->height - 1]))
		parser_config->map_config->width = ft_strlen(parser_config->map_config->map[parser_config->map_config->height - 1]);
	parser_config->map_config->height++;
}

void	parse_and_check_texture(t_parser_config *parser_config, t_tex_type tex_type, char *line)
{
	parser_config->textures_paths[tex_type] = ft_strdup(line);
	if (!parser_config->textures_paths[tex_type])
	{
		free(line);
		free_parser_config(parser_config, "Error\nMemory allocation failed for texture path\n");
	}
}

void	parse_texture(t_parser_config *parser_config, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strncmp(line, "NO", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_NORTH, line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_SOUTH, line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_WEST, line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_EAST, line);
	else if (ft_strncmp(line, "FL", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_FLOOR, line);
	else if (ft_strncmp(line, "CE", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_CEILING, line);
	else if (ft_strncmp(line, "XX", 2) == 0)
		parse_and_check_texture(parser_config, TEX_TYPE_ENEMY, line);
	else
	{
		free(line);
		free_parser_config(parser_config, "Error\nInvalid texture or colour line\n");
	}
}

void	parse_line(t_parser_config *parser_config, char *line)
{
	if (is_map_line(line))
		parse_map_line(parser_config, line);
	else if (!parser_config->map_config->parsing_map)
		parse_texture(parser_config, line);
	else
	{
		free(line);
		free_parser_config(parser_config, "Error\nInvalid line after map started\n");
	}
}

void	parse(t_parser_config *parser_config)
{
	char	*line;

	line = get_next_line(parser_config->map_config->fd);
	if (!line)
		free_parser_config(parser_config, "Error\nEmpty file\n");
	while (line != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (parser_config->map_config->parsing_map == 1)
			{
				free(line);
				free_parser_config(parser_config, "Error\nEmpty line in map\n");
			}
			free(line);
			line = get_next_line(parser_config->map_config->fd);
			continue;
		}
		parse_line(parser_config, line);
		free(line);
		line = get_next_line(parser_config->map_config->fd);
	}
	parser_config->map_config->height--;
}
