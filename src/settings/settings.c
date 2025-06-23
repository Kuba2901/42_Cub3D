/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:36 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/23 18:01:07 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_settings.h>
#include <cube_settings_textures.h>

t_cube_settings	*settings_cube_init(
	t_map_config *map_config, t_tex_config *tex_config)
{
	t_cube_settings	*cube_settings;
	t_bool			valid;

	valid = CUBE_TRUE;
	cube_settings = malloc(sizeof(t_cube_settings));
	if (!cube_settings)
		return (NULL);
	cube_settings->map_config = map_config;
	cube_settings->tex_config = tex_config;
	if (!map_config || !tex_config)
		valid = CUBE_FALSE;
	cube_settings->valid = valid;
	return (cube_settings);
}

void	settings_cube_free(t_cube_settings *cube_settings)
{
	if (!cube_settings)
		return ;
	settings_map_config_free(cube_settings->map_config);
	settings_tex_config_free(cube_settings->tex_config);
	safe_free(cube_settings);
}
