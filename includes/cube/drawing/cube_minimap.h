#ifndef CUBE_MINIMAP_H
# define CUBE_MINIMAP_H

// Minimap constants
#define MINIMAP_SIZE 200              
#define MINIMAP_CELL_SIZE 8           
#define MINIMAP_PLAYER_SIZE 4         
#define MINIMAP_ENEMY_SIZE (MINIMAP_PLAYER_SIZE - 1)
#define MINIMAP_MARGIN 10             
#define MINIMAP_BACKGROUND_COLOR 0x222222
#define MINIMAP_WALL_COLOR 0x888888
#define MM_PLAYER_COLOR 0xFF0000
#define MINIMAP_FLOOR_COLOR 0x333333
#define MINIMAP_BORDER_COLOR 0xAAAAAA

typedef struct	s_cube	t_cube;
typedef struct	s_player	t_player;

typedef struct	s_bresenham_data
{
	int				dir_length;
	int				dir_end_x;
	int				dir_end_y;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				x;
	int				y;
}	t_bresenham_data;

typedef struct	s_minimap_data
{
	int					map_x;
	int					map_y;
	int					screen_x;
	int					screen_y;
	int 				minimap_pos_x;
	int 				minimap_pos_y;
	int 				player_pos_x;
	int					player_pos_y;
	t_player			*player;
	t_image_data		*img;
	int					map_center_x;
	int					map_center_y;
	int					map_radius;
	t_cube				*cube;
	t_bresenham_data	bd;
}	t_minimap_data;

void	draw_minimap(t_cube *cube);
void	minimap_draw_cells(t_minimap_data *mmd);
void	minimap_bresenham_data_init(t_minimap_data *mmd);
void	minimap_draw_direction_line(t_minimap_data *mmd);
void	minimap_draw_player(t_minimap_data *mmd);
void	minimap_draw_enemies(t_minimap_data *mmd);

#endif
