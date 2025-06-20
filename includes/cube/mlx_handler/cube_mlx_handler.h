/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mlx_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:23:13 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/15 22:20:47 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_MLX_HANDLER_H
# define CUBE_MLX_HANDLER_H

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_TITLE "CUBE3D"

/* NORMINETTE ENFORCED BEHAVIOUR -> SHOULD BE WINDOW_WIDTH/HEIGHT  /  2 */
# define WINDOW_CENTER_X 640
# define WINDOW_CENTER_Y 360
# define FOV .66

# define WINDOW_INTRO "./assets/intro/intro.xpm"

typedef struct s_image_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image_data;

typedef struct s_mlx_handler
{
	void			*mlx;
	void			*mlx_win;
	t_image_data	*mlx_img;
}	t_mlx_handler;

t_mlx_handler	*mlx_mlx_handler_init( void );
void			mlx_mlx_handler_free(t_mlx_handler **mlx_handler);

#endif