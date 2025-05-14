#ifndef CUBE_SETTINGS_TEXTURES_H
# define CUBE_SETTINGS_TEXTURES_H

# define TEXTURE_SIZE 512
# include <stdlib.h>

typedef struct s_image_data	t_image_data;

typedef struct	s_tex_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_tex_color;

typedef struct	s_single_tex_load_data
{
	t_image_data	*img;
	t_tex_color		color;
	int				src_pos;
	int				dst_pos;
}	t_single_tex_load_data;

typedef enum	s_tex_type
{
	TEX_TYPE_NORTH,
	TEX_TYPE_EAST,
	TEX_TYPE_SOUTH,
	TEX_TYPE_WEST,
	TEX_TYPE_FLOOR,
	TEX_TYPE_CEILING,
	TEX_TYPE_EXIT,
}	t_tex_type;

# if CUBE_BONUS
#  define TEXTURE_TYPES_COUNT 6
# else
# define TEXTURE_TYPES_COUNT 4
# endif 

typedef struct s_animated_frames t_animated_frames;

typedef struct	s_tex_config
{
	size_t				**textures;
	t_animated_frames	*enemy_frames;
	t_animated_frames	*exit_idle_frames;
	t_animated_frames	*exit_open_frames;

	t_tex_color			floor_color;
	t_tex_color			ceiling_color;
}	t_tex_config;

typedef struct s_mlx_handler	t_mlx_handler;
typedef struct s_color			t_color;

t_tex_config	*settings_tex_config_init(char **paths, t_mlx_handler *mlx_handler, t_color *ceil_color, t_color *floor_color);
void			settings_tex_config_set_tex_all(t_tex_config *config, 
	t_mlx_handler *mlx_handler, char **paths);
void			settings_tex_config_free(t_tex_config *tex_config);
size_t			*settings_tex_get_texels(char *path, t_mlx_handler *mlx_handler);
t_tex_color		settings_color_init(t_color *clr);

#endif