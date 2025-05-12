/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_drawing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:15:05 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 12:02:30 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_DRAWING_H
# define CUBE_DRAWING_H

# define DRAW_CEILING_COLOR 0xFF87CEEB
# define DRAW_BLACK_COLOR 0x000000
# define DRAW_WHITE_COLOR 0xFFFFFF
# define DRAW_RED_COLOR 0xFF0000
# define CREDITS_PATH "./assets/credits.txt"
# define CREDITS_CHAR_WIDTH 6
# define CREDITS_LINE_HEIGHT 30

typedef struct s_draw_horizontal_data
{
	float			ray_dir_x0;
	float			ray_dir_y0;
	float			ray_dir_x1;
	float			ray_dir_y1;
	int				pos_rel_to_horizon;
	float			pos_vertical_z;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				cell_x;
	int				cell_y;
	int				texture_x;
	int				texture_y;
	unsigned int	color;
}	t_draw_horizontal_data;

typedef struct s_draw_vertical_slice_data
{
	int		y;
	double	step;
	double	wall_top;
	double	wall_bottom;
	int		tex_type;
	int		tex_x;
	double	tex_pos;
	int		column_x;
}	t_draw_vertical_slice_data;

typedef struct s_cube		t_cube;
typedef struct s_image_data	t_image_data;

void						draw_render_scene(t_cube *cube);
void						draw_my_mlx_pixel_put(t_image_data *data, int x,
								int y, int color);
void						credits_display(t_cube *cube);
void						draw_render_clear_screen(t_cube *cube);
t_draw_vertical_slice_data	draw_prep_vertical_slice_data(
								t_cube *cube, int column_x);
t_draw_horizontal_data		draw_prep_get_draw_horizontal_data(
								t_cube *cube, int y);
void						draw_prep_dda(t_cube *cube);
void						draw_textured_vertical_slice(
								int column_x, t_cube *cube);
void						credits_lines_free(char **lines);
char						**credits_lines_load(void);;
void						draw_textured(t_draw_vertical_slice_data *data,
								t_cube *cube, int y);
void						draw_render_floor_and_ceiling(t_cube *cube);

// Intro
void						intro_display(t_cube *cube);

#endif