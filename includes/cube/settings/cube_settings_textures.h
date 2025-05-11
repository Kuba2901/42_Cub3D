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
	unsigned char	a;
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

# define TEXTURE_TYPES_COUNT 6

typedef struct s_animated_frames t_animated_frames;

typedef struct	s_tex_config
{
	size_t				**textures;
	t_animated_frames	*enemy_frames;
	t_animated_frames	*exit_idle_frames;
	t_animated_frames	*exit_open_frames;
}	t_tex_config;

typedef struct s_mlx_handler	t_mlx_handler;

t_tex_config	*settings_tex_config_init(const char **paths, t_mlx_handler *mlx_handler);
void			settings_tex_config_set_tex_all(t_tex_config *config, 
	t_mlx_handler *mlx_handler, const char **paths);
void			settings_tex_config_free(t_tex_config *tex_config);
size_t			*settings_tex_get_texels(const char *path, t_mlx_handler *mlx_handler);

#endif