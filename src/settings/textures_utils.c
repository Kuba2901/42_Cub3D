/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:03 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/23 18:08:34 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_mlx_handler.h>
#include <stdlib.h>
#include <mlx.h>
#include <cube_settings.h>
#include <utils.h>
#include <libft.h>
#include <cube_mlx_handler.h>
#include <cube_settings_animated_sprites.h>
#include <cube_settings_textures.h>
#include <parse_mandatory.h>

t_tex_type	settings_tex_get_tex_type(char *path)
{
	if (!path || !ft_strlen(path))
		return (TEX_TYPE_NORTH);
	if (!ft_strncmp(path, "NO", 2))
		return (TEX_TYPE_NORTH);
	if (!ft_strncmp(path, "SO", 2))
		return (TEX_TYPE_SOUTH);
	if (!ft_strncmp(path, "WE", 2))
		return (TEX_TYPE_WEST);
	if (!ft_strncmp(path, "EA", 2))
		return (TEX_TYPE_EAST);
	if (!ft_strncmp(path, "FL", 2))
		return (TEX_TYPE_FLOOR);
	if (!ft_strncmp(path, "CE", 2))
		return (TEX_TYPE_CEILING);
	if (!ft_strncmp(path, "EX", 2))
		return (TEX_TYPE_EXIT);
	return (TEX_TYPE_NORTH);
}

void	settings_tex_config_set_tex_all(t_tex_config *config,
	t_mlx_handler *mlx_handler, char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = -1;
	while (++i < TEXTURE_TYPES_COUNT)
		config->textures[i] = NULL;
	i = -1;
	while (++i < TEXTURE_TYPES_COUNT)
	{
		settings_tex_config_set_tex(config,
			settings_tex_get_tex_type(paths[i]), mlx_handler, paths[i]);
	}
}

t_tex_color	settings_color_init(t_color *clr)
{
	t_tex_color	color;

	if (!clr)
	{
		color.r = 0;
		color.g = 0;
		color.b = 0;
		return (color);
	}
	color.r = clr->r;
	color.g = clr->g;
	color.b = clr->b;
	return (color);
}
