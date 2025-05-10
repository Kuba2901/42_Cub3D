#ifndef CUBE_SETTINGS_ANIMATED_SPRITE_H
# define CUBE_SETTINGS_ANIMATED_SPRITE_H

// Enemy
# define ANIM_ENEMY_IDLE_FRAME_0 "assets/textures/biohazard/xpm/enemies/idle_0.xpm"
# define ANIM_ENEMY_IDLE_FRAME_1 "assets/textures/biohazard/xpm/enemies/idle_1.xpm"
# define ANIM_ENEMY_IDLE_FRAME_2 "assets/textures/biohazard/xpm/enemies/idle_2.xpm"
# define ANIM_ENEMY_IDLE_FRAME_3 "assets/textures/biohazard/xpm/enemies/idle_3.xpm"
# define ANIM_ENEMY_IDLE_FRAME_4 "assets/textures/biohazard/xpm/enemies/idle_4.xpm"
# define ANIM_ENEMY_IDLE_FRAME_5 "assets/textures/biohazard/xpm/enemies/idle_5.xpm"
# define ANIM_ENEMY_IDLE_FRAME_6 "assets/textures/biohazard/xpm/enemies/idle_6.xpm"
# define ANIM_ENEMY_FRAMES_COUNT 7

// Exit
# define ANIM_EXIT_IDLE_FRAME_0 "./assets/textures/biohazard/xpm/exit/exit_0.xpm"

# define ANIM_EXIT_OPEN_FRAME_0 "./assets/textures/biohazard/xpm/exit/open/exit_0.xpm"
# define ANIM_EXIT_OPEN_FRAME_1 "./assets/textures/biohazard/xpm/exit/open/exit_1.xpm"
# define ANIM_EXIT_OPEN_FRAME_2 "./assets/textures/biohazard/xpm/exit/open/exit_2.xpm"
# define ANIM_EXIT_OPEN_FRAME_3 "./assets/textures/biohazard/xpm/exit/open/exit_3.xpm"
# define ANIM_EXIT_OPEN_FRAME_4 "./assets/textures/biohazard/xpm/exit/open/exit_4.xpm"
# define ANIM_EXIT_OPEN_FRAME_5 "./assets/textures/biohazard/xpm/exit/open/exit_5.xpm"

# define ANIM_EXIT_IDLE_FRAMES_COUNT 1
# define ANIM_EXIT_OPEN_FRAMES_COUNT 6

# include <stdlib.h>

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



typedef struct	s_animated_frames
{
	size_t	**frames;
	int		frames_count;
}	t_animated_frames;

typedef struct s_mlx_handler	t_mlx_handler;

t_animated_frames	*settings_enemy_frames_init(t_mlx_handler *mlx_handler);
t_animated_frames	*settings_exit_idle_frames_init(t_mlx_handler *mlx_handler);
t_animated_frames	*settings_exit_open_frames_init(t_mlx_handler *mlx_handler);

#endif