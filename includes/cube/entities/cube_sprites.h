/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sprites.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:32:48 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_SPRITES_H
# define CUBE_SPRITES_H

# include <cube_entities.h>
# include <cube.h>

typedef struct s_sprite_data
{
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_data;

typedef struct s_sprite_tex_data
{
	int				tex_x;
	int				tex_y;
	size_t			*tex;
	unsigned int	color;
}	t_sprite_tex_data;

/* sprites.c */
void				sprites_draw(t_cube *cube);

/* sprites_position.c */
double				sprite_get_distance(t_enemy *enemy, t_player *player);
void				sprite_calculate_position(t_enemy *sprite, t_player *player,
						t_sprite_data *data);
void				sprite_calculate_dimensions(t_sprite_data *data);

/* sprites_render.c */
t_sprite_tex_data	sprite_init_tex_data(t_sprite_data *data,
						t_enemy *sprite, int stripe);
void				sprite_draw_stripe(t_cube *cube, t_enemy *sprite,
						t_sprite_data *data, int stripe);
void				sprite_process(t_cube *cube, t_enemy *sprite,
						t_sprite_data *data);

/* sprites_utils.c */
void				sprite_sort(int *order, double *dist, int amount);

#endif