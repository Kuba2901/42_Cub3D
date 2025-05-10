/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 22:27:34 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_mlx_handler.h>
#include <cube_drawing.h>
#include <cube_runtime.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>

int	credits_put_centered_text(t_cube *cube, int y, int color, char *string)
{
	int	text_width;
	int	x;

	text_width = 0;
	if (string)
		text_width = ft_strlen(string) * CREDITS_CHAR_WIDTH;
	x = (WINDOW_WIDTH - text_width) / 2;
	if (x < 0)
		x = 0;
	if (!string)
		return (0);
	string[ft_strlen(string) - 1] = ' ';
	return (mlx_string_put(cube->mlx_handler->mlx,
			cube->mlx_handler->mlx_win, x, y, color, string));
}

static void	credits_render_black_screen(t_cube *cube)
{
	t_mlx_handler	*mlx_handler;
	int				y;
	int				x;

	mlx_handler = cube->mlx_handler;
	draw_render_clear_screen(cube);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			draw_my_mlx_pixel_put(mlx_handler->mlx_img, x, y, DRAW_BLACK_COLOR);
	}
	mlx_put_image_to_window(cube->mlx_handler->mlx,
		cube->mlx_handler->mlx_win, cube->mlx_handler->mlx_img->img, 0, 0);
}

void	credits_display(t_cube *cube)
{
	int		y_pos;
	char	**lines;
	int		i;
	int		current_y;

	cube->runtime_handler->displaying_credits = TRUE;
	lines = credits_lines_load();
	y_pos = WINDOW_HEIGHT;
	while (y_pos + (CREDITS_LINE_HEIGHT * 2) > 0)
	{
		credits_render_black_screen(cube);
		i = 0;
		current_y = y_pos;
		while (lines[i])
		{
			credits_put_centered_text(cube, current_y,
				DRAW_WHITE_COLOR, lines[i]);
			current_y += CREDITS_LINE_HEIGHT;
			i++;
		}
		y_pos -= 2;
		mlx_do_sync(cube->mlx_handler->mlx);
		usleep(30000);
	}
	credits_lines_free(lines);
}
