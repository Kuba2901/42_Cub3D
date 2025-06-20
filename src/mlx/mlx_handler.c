/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:01:51 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/20 16:32:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_mlx_handler.h>
#include <stdlib.h>
#include <mlx.h>
#include <utils.h>

t_image_data	*mlx_img_image_data_init(t_mlx_handler *mlx_handler)
{
	t_image_data	*image_data;

	image_data = malloc(sizeof(t_image_data));
	if (!image_data)
		return (NULL);
	image_data->img = mlx_new_image(mlx_handler->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
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

void	mlx_img_image_data_free(t_mlx_handler *mlx_handler)
{
	if (mlx_handler && mlx_handler->mlx_img)
	{
		if (mlx_handler->mlx_img->img)
			mlx_destroy_image(mlx_handler->mlx, mlx_handler->mlx_img->img);
		free(mlx_handler->mlx_img);
		mlx_handler->mlx_img = NULL;
	}
}

t_mlx_handler	*mlx_mlx_handler_init( void )
{
	t_mlx_handler	*mlx_handler;

	mlx_handler = malloc(sizeof(t_mlx_handler));
	if (!mlx_handler)
		return (NULL);
	mlx_handler->mlx = mlx_init();
	mlx_handler->mlx_win = mlx_new_window(mlx_handler->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_TITLE);
	mlx_handler->mlx_img = mlx_img_image_data_init(mlx_handler);
	return (mlx_handler);
}

void	mlx_mlx_handler_free(t_mlx_handler **mlx_handler)
{
	if (mlx_handler && *mlx_handler)
	{
		mlx_img_image_data_free(*mlx_handler);
		if ((*mlx_handler)->mlx_win)
			mlx_destroy_window((*mlx_handler)->mlx, (*mlx_handler)->mlx_win);
		if ((*mlx_handler)->mlx)
		{
			mlx_destroy_display((*mlx_handler)->mlx);
			free((*mlx_handler)->mlx);
		}
		free(*mlx_handler);
		*mlx_handler = NULL;
	}
}
