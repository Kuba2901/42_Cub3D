#ifndef CUBE_LIFECYCLE_H
# define CUBE_LIFECYCLE_H

typedef struct	s_cube	t_cube;

/* lifecycle.c */
int		lifecycle_on_destroy(t_cube *cube);
double	lifecycle_get_ticks(void);
int		lifecycle_game_loop(t_cube *cube);

/* lifecycle_animation.c */
void	lifecycle_animate_sprites(t_cube *cube);


#endif