/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:08 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/20 15:48:25 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_UTILS_H
# define PARSE_MAP_UTILS_H

# define TAB_WIDTH 4

# include <stdio.h>
# include <libft.h>

typedef struct s_parser_config	t_parser_config;

// parse_map_utils.h
int		get_new_line_lenght(char *line);
void	put_spaces(char *new_line, int *j);
char	*replace_tabs(char *line);

// check_map_utils.c
void	check_starting_pos_map(t_parser_config *parser_config);
int		is_neighbour(char **map, int i, int j, char elem);
void	check_map_walls(t_parser_config *parser_config);
int		check_exit(t_parser_config *parser_config);

// realloc_map_utils.c
char	**realloc_map(char **map, size_t new_size);
void	free_new_map(t_parser_config *parser_config, char **new_map, int i);
void	copy_and_pad_map_line(char *new_line, char *src_line, size_t width);
void	realloc_map_with_max_width(t_parser_config *parser_config);

#endif