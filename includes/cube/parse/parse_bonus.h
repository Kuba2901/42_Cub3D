/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:49:42 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/14 15:31:48 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

#include <stdio.h>
#include <libft.h>
#include <parse_map_utils.h>
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
}	t_parser_config;

// init_bonus.c
void			init_bonus_parser_textures_paths(t_parser_config *parser_config);
void			init_bonus_parser_map_config(t_parser_config *parser_config, char *filename);
t_parser_config	*init_parser_config(char *filename);
void			free_bonus_parser_map_config(t_map_parse *map_config);
void			free_parser_config(t_parser_config *parser_config, char *line, char *error);

// parse_bonus_map.c
int				is_bonus_map_line(char *line);
void			parse_bonus_map_line(t_parser_config *parser_config, char *line);

// parse_bonus_texture.c
void			parse_and_check_bonus_texture(t_parser_config *parser_config, t_tex_type texture_type, char *line);
void			parse_bonus_texture(t_parser_config *parser_config, char *line);
void			check_parsed_bonus_textures(t_parser_config *parser_config);

// parse_bonus.c
void			parse_bonus_line(t_parser_config *parser_config, char *line);
void			parse(t_parser_config *parser_config);

#endif