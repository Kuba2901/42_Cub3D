/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_settings_animated_sprites.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:13:32 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/23 21:44:56 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_SETTINGS_ANIMATED_SPRITES_H
# define CUBE_SETTINGS_ANIMATED_SPRITES_H

// Enemy
# define A_E_I_F_0 "assets/textures/biohazard/xpm/enemies/idle_0.xpm"
# define A_E_I_F_1 "assets/textures/biohazard/xpm/enemies/idle_1.xpm"
# define A_E_I_F_2 "assets/textures/biohazard/xpm/enemies/idle_2.xpm"
# define A_E_I_F_3 "assets/textures/biohazard/xpm/enemies/idle_3.xpm"
# define A_E_I_F_4 "assets/textures/biohazard/xpm/enemies/idle_4.xpm"
# define A_E_I_F_5 "assets/textures/biohazard/xpm/enemies/idle_5.xpm"
# define A_E_I_F_6 "assets/textures/biohazard/xpm/enemies/idle_6.xpm"
# define A_E_F_C 7

// Exit
# define A_EX_I_F_0 "./assets/textures/biohazard/xpm/exit/exit_0.xpm"
# define A_E_O_F_0 "./assets/textures/biohazard/xpm/exit/open/exit_0.xpm"
# define A_E_O_F_1 "./assets/textures/biohazard/xpm/exit/open/exit_1.xpm"
# define A_E_O_F_2 "./assets/textures/biohazard/xpm/exit/open/exit_2.xpm"
# define A_E_O_F_3 "./assets/textures/biohazard/xpm/exit/open/exit_3.xpm"
# define A_E_O_F_4 "./assets/textures/biohazard/xpm/exit/open/exit_4.xpm"
# define A_E_O_F_5 "./assets/textures/biohazard/xpm/exit/open/exit_5.xpm"
# define A_E_I_F_C 1
# define A_E_O_F_C 6

# include <stdlib.h>

typedef struct s_animated_frames
{
	size_t	**frames;
	int		frames_count;
}	t_animated_frames;

typedef struct s_mlx_handler	t_mlx_handler;

t_animated_frames	*settings_enemy_frames_init(t_mlx_handler *mlx_handler);
t_animated_frames	*settings_exit_idle_frames_init(t_mlx_handler *mlx_handler);
t_animated_frames	*settings_exit_open_frames_init(t_mlx_handler *mlx_handler);

#endif