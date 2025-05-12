/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:49:42 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/12 16:31:39 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define TAB_WIDTH 4

#include <stdio.h>
#include <libft.h>
#include <cube_settings_textures.h>
#include <cube_settings_map.h>

typedef struct s_map_parse
{
	int			fd;
	int			parsing_map;
	size_t		height;
	size_t		width;
	char		**map;
}	t_map_parse;

typedef struct s_parser_config
{
	t_map_parse	*map_config;
	char		**textures_paths;
	// t_textures_parse	*textures_config;
}	t_parser_config;

// init.c
void			init_parser_map_config(t_parser_config *parser_config, char *filename);
void			init_parser_textures_paths(t_parser_config *parser_config);
t_parser_config	*init_parser_config(char *filename);
void	free_parser_map_config(t_map_parse *map_config);
void			free_parser_config(t_parser_config *parser_config, char *error);

// parse.c
int		is_map_line(char *line);
char	*replace_tabs(char* line);
char	**realloc_map(char **map, size_t new_size);
void	parse_map_line(t_parser_config *parser_config, char *line);
void	parse_and_check_texture(t_parser_config *parser_config, t_tex_type texture_type, char *line);
void	parse_texture(t_parser_config *parser_config, char *line);
void	parse_line(t_parser_config *parser_config, char *line);
void	parse(t_parser_config *parser_config);

#endif