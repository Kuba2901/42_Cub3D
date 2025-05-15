/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:01:51 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/15 22:45:13 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_mlx_handler.h>
#include <stdlib.h>
#include <mlx.h>
#include <utils.h>

t_image_data	*mlx_img_image_data_init(t_mlx_handler *mlx_handler)
{
	t_image_data	*image_data;

	(void)mlx_handler;
	image_data = malloc(sizeof(t_image_data));
	if (!image_data)
		return (NULL);
	image_data->img = NULL;
	image_data->addr = NULL;
	image_data->bits_per_pixel = 0;
	image_data->endian = 0;
	return (image_data);
}

void	mlx_img_image_data_free(t_mlx_handler *mlx_handler)
{
	mlx_destroy_image(mlx_handler->mlx, mlx_handler->mlx_img->img);
	free(mlx_handler->mlx_img);
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

void	mlx_mlx_handler_free(t_mlx_handler *mlx_handler)
{
	mlx_img_image_data_free(mlx_handler);
	mlx_destroy_window(mlx_handler->mlx, mlx_handler->mlx_win);
	mlx_destroy_display(mlx_handler->mlx);
	free(mlx_handler->mlx);
	free(mlx_handler);
}
