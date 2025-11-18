/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:44:41 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/23 17:53:27 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_settings_map.h>
#include <stdlib.h>
#include <utils.h>
#include <stdio.h>
#include <fcntl.h>
#include <libft.h>

static t_bool	settings_map_config_is_start(char c)
{
	return (c == 'E' || c == 'W' || c == 'S' || c == 'N');
}

void	settings_map_config_extract_basic_information(
	t_map_config *map_config)
{
	int				y;
	int				x;
	char			c;

	if (!map_config || !map_config->map)
		return ;
	y = -1;
	map_config->key_location.c = 0;
	while (++y < map_config->height)
	{
		x = -1;
		while (++x < map_config->width)
		{
			c = map_config->map[y][x];
			if (settings_map_config_is_start(c))
				map_config->start_location = map_point_init(x, y, c);
			else if (c == 'Q')
				map_config->exit_location = map_point_init(x, y, c);
		}
	}
}

void	settings_map_config_free(t_map_config *map_config)
{
	int	i;

	if (!map_config)
		return ;
	if (map_config->enemies_locations)
	{
		i = -1;
		while (map_config->enemies_locations[++i])
			safe_free(map_config->enemies_locations[i]);
		safe_free(map_config->enemies_locations);
	}
	safe_free(map_config);
}
