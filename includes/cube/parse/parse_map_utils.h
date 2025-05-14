/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:08 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/13 15:16:08 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# define TAB_WIDTH 4

#include <stdio.h>
#include <libft.h>

// parse_map_utils.h
int		get_new_line_lenght(char *line);
void	put_spaces(char *new_line, int *j);
char	*replace_tabs(char *line);
char	**realloc_map(char **map, size_t new_size);


#endif