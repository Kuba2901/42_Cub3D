/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_entities.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:17:05 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:21:10 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_ENTITIES_H
# define CUBE_ENTITIES_H

# include <utils.h>
# include <cube_map.h>
# include <stdlib.h>
# include <cube_mlx_handler.h>

# define ENTITY_CENTRAL_OFFSET 0.5

typedef enum s_entity_type
{
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY,
	ENTITY_TYPE_EXIT
}	t_entity_type;

typedef struct s_location
{
	double	x;
	double	y;
}	t_location;

typedef struct s_animation_controller	t_animation_controller;
typedef struct s_animated_frames		t_animated_frames;
typedef struct s_cube_settings			t_cube_settings;
typedef struct s_cube					t_cube;

typedef struct s_entity
{
	t_location				current_location;
	int						hp;
	t_animation_controller	*controller;
}	t_entity;

typedef struct s_player
{
	t_entity	*base;
	t_vector	dir;
	t_vector	camera;
}	t_player;

typedef struct s_exit
{
	t_entity	*base;
	t_bool		unlocked;
}	t_exit;

typedef struct s_enemy
{
	t_entity	*base;
}	t_enemy;

typedef struct s_entities
{
	t_player	*player;
	t_enemy		**enemies;
	t_exit		*exit;
	double		buffer_z[WINDOW_WIDTH];
	int			*sprite_order;
	double		*sprite_distance;
}	t_entities;

typedef struct s_entities_config
{
	t_point				player_location;
	t_point				exit_location;
	t_point				**enemies_locations;
	t_animated_frames	*enemy_frames_ptr;
	t_animated_frames	*exit_idle_frames_ptr;
	t_animated_frames	*exit_open_frames_ptr;
	int					enemies_count;
}	t_entities_config;

t_entities			*entities_entities_init(t_entities_config config);
void				entities_entities_free(t_entities *entities);
t_entities_config	entities_entities_config_init(
						t_cube_settings *cube_settings);
void				sprites_draw(t_cube *cube);
void				entities_enemies_multiple_free(t_enemy **enemies);
t_enemy				**entities_enemies_multiple_init(t_point **enemy_locations,
						t_animated_frames *frames_ptr);
void				entities_enemy_free(t_enemy *enemy);
t_enemy				*entities_enemy_init(t_point pt,
						t_animated_frames *frames_ptr);
t_entity			*entities_entity_init(t_point pt, t_entity_type type,
						t_animated_frames *frames_ptr);
void				entities_entity_free(t_entity *entity);
void				entities_exit_free(t_exit *exit_entity);
t_exit				*entities_exit_init(t_point pt,
						t_animated_frames *idle_frames_ptr,
						t_animated_frames *open_frames_ptr);
void				entities_player_free(t_player *player);
t_player			*entities_player_init(t_point pt);
t_entities			*entities_allocate(void);
int					entities_init_exit(t_entities *entities,
						t_entities_config config);
int					entities_init_enemies(t_entities *entities,
						t_entities_config config);
int					entities_init_player(t_entities *entities,
						t_entities_config config);
int					entities_allocate_sprites(t_entities *entities,
						int num_enemies);

#endif