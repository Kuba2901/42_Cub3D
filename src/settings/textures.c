/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:03 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/23 18:00:53 by jnenczak         ###   ########.fr       */
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
#include <parse_mandatory.h>
#include <cube_animations.h>
#include <cube_settings_textures.h>

t_tex_config	*settings_tex_config_init(char **paths,
	t_mlx_handler *mlx_handler,
	t_color	*ceil_color,
	t_color *floor_color)
{
	t_tex_config	*tex_config;

	tex_config = malloc(sizeof(t_tex_config));
	if (!tex_config)
		return (NULL);
	tex_config->textures = malloc(sizeof(size_t *) * (TEXTURE_TYPES_COUNT));
	if (!tex_config->textures)
	{
		safe_free(tex_config);
		return (NULL);
	}
	tex_config->enemy_frames = settings_enemy_frames_init(mlx_handler);
	tex_config->exit_idle_frames = settings_exit_idle_frames_init(mlx_handler);
	tex_config->exit_open_frames = settings_exit_open_frames_init(mlx_handler);
	tex_config->ceiling_color = settings_color_init(ceil_color);
	tex_config->floor_color = settings_color_init(floor_color);
	settings_tex_config_set_tex_all(tex_config, mlx_handler, paths);
	return (tex_config);
}

static t_image_data	*settings_tex_get_image(
	char *path, t_mlx_handler *mlx_handler)
{
	t_image_data	*img;
	int				img_width;
	int				img_height;

	img = malloc(sizeof(t_image_data));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx_handler->mlx, path, &img_width,
			&img_height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		free(img);
		return (NULL);
	}
	return (img);
}

static void	settings_tex_load_pixels(t_single_tex_load_data *tex_data,
	size_t *texels)
{
	int	y;
	int	x;

	y = -1;
	while (++y < TEXTURE_SIZE)
	{
		x = -1;
		while (++x < TEXTURE_SIZE)
		{
			tex_data->src_pos = y * tex_data->img->line_length + x
				* (tex_data->img->bits_per_pixel / 8);
			tex_data->dst_pos = y * TEXTURE_SIZE + x;
			tex_data->color.b = tex_data->img->addr[tex_data->src_pos];
			tex_data->color.g = tex_data->img->addr[tex_data->src_pos + 1];
			tex_data->color.r = tex_data->img->addr[tex_data->src_pos + 2];
			texels[tex_data->dst_pos] = (tex_data->color.r << 16)
				| (tex_data->color.g << 8) | tex_data->color.b;
		}
	}
}

size_t	*settings_tex_get_texels(char *path, t_mlx_handler *mlx_handler)
{
	t_image_data			*img;
	size_t					*texels;
	t_single_tex_load_data	tex_data;

	img = settings_tex_get_image(path, mlx_handler);
	if (!img)
		return (NULL);
	texels = malloc(sizeof(size_t) * (TEXTURE_SIZE * TEXTURE_SIZE));
	if (!texels)
	{
		mlx_destroy_image(mlx_handler->mlx, img);
		free(img);
		return (NULL);
	}
	tex_data.img = img;
	settings_tex_load_pixels(&tex_data, texels);
	mlx_destroy_image(mlx_handler->mlx, tex_data.img->img);
	free(tex_data.img);
	return (texels);
}

size_t	*settings_tex_config_set_tex(t_tex_config *config, t_tex_type tex_type,
	t_mlx_handler *mlx_handler, char *path)
{
	if (!config)
		return (NULL);
	config->textures[tex_type] = settings_tex_get_texels(path + 3, mlx_handler);
	return (config->textures[tex_type]);
}
