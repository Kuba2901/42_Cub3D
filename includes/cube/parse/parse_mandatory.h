/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:27:42 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/14 14:54:14 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MANDATORY_H
# define PARSE_MANDATORY_H

# include <stdio.h>
# include <libft.h>
# include <utils.h>
# include <parse_map_utils.h>

typedef struct s_parser_config	t_parser_config;

typedef struct s_map_parse
{
	int			fd;
	int			parsing_map;
	size_t		height;
	size_t		width;
	char		**map;
}	t_map_parse;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	t_parser_config	*parser_config;
}	t_color;

typedef struct s_parser_config
{
	t_map_parse	*map_config;
	char		**textures_paths;
	t_color		*floor_color;
	t_color		*ceiling_color;
}	t_parser_config;

typedef enum	s_tex_type_mandatory
{
	TEX_NORTH,
	TEX_EAST,
	TEX_SOUTH,
	TEX_WEST,
} t_tex_type_mandatory;

# define TEXTURE_TYPES_COUNT_MANDATORY 4

// free_mandatory.c
void			free_parser_textures_and_colors(t_parser_config *parser_config);
void			free_parser_config(t_parser_config *parser_config, char *line, char *error);
void			free_parser_map_config(t_map_parse *map_config);

// init_mandatory.c
void			init_parser_map_config(t_parser_config *parser_config, char *filename);
void			init_parser_textures_and_colors(t_parser_config *parser_config);
t_parser_config	*init_parser_config(char *filename);

// parse_mandatory_map.c
int				is_map_line(char *line);
void			parse_map_line(t_parser_config *parser_config, char *line);

// parse_mandatory_texture.c
void			parse_texture(t_parser_config *parser_config, t_tex_type_mandatory tex_type, char *line);
void			parse_color(t_color *color, char *line);
void			parse_texture_or_color(t_parser_config *parser_config, char *line);
void			check_parsed_mandatory_textures(t_parser_config *parser_config);

// parse_mandatory.c
void			parse_line(t_parser_config *parser_config, char *line);
void			parse(t_parser_config *parser_config);

#endif