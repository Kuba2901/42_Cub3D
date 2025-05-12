/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:52:46 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 12:19:53 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_mlx_handler.h>
#include <cube.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

t_image_data	*intro_init(t_cube *cube)
{
	t_image_data	*image_data;
	t_mlx_handler	*mlx_handler;
	int				w;
	int				h;

	mlx_handler = cube->mlx_handler;
	image_data = malloc(sizeof(t_image_data));
	if (!image_data)
		return (NULL);
	image_data->img = mlx_xpm_file_to_image(mlx_handler->mlx,
			WINDOW_INTRO, &w, &h);
	if (!image_data->img)
	{
		free(image_data);
		return (NULL);
	}
	image_data->addr = mlx_get_data_addr(image_data->img,
			&image_data->bits_per_pixel, &image_data->line_length,
			&image_data->endian);
	return (image_data);
}

void	intro_display(t_cube *cube)
{
	t_mlx_handler	*mlx_handler;
	t_image_data	*image_data;

	mlx_handler = cube->mlx_handler;
	image_data = intro_init(cube);
	cube->mlx_handler->mlx_img = image_data;
	mlx_put_image_to_window(mlx_handler->mlx, mlx_handler->mlx_win,
		image_data->img, 0, 0);
}
