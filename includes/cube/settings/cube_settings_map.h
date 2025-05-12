/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_settings_map.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:41:08 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/09 16:41:10 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_SETTINGS_MAP_H
# define CUBE_SETTINGS_MAP_H

# include <cube_map.h>

typedef struct	s_map_config
{
	int		width;
	int		height;
	t_point	exit_location;
	t_point	start_location;
	t_point	key_location;
	t_point	**enemies_locations;
	int		enemies_count;
	int		fd;
	char	*filename;
	t_bool	parsing_map;
	char	**map;
}	t_map_config;

t_map_config	*settings_map_config_init(char **map, int width, int height);
void			settings_map_config_free(t_map_config *map_config);

#endif