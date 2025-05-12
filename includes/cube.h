/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:26:12 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 16:15:30 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

typedef struct s_cube_settings		t_cube_settings;
typedef struct s_map				t_map;
typedef struct s_entities			t_entities;
typedef struct s_mlx_handler		t_mlx_handler;
typedef struct s_runtime_handler	t_runtime_handler;
typedef struct s_input_handler		t_input_handler;
typedef struct s_dda_data			t_dda_data;
typedef struct	s_parser_config	t_parser_config;
typedef struct s_audio_system		t_audio_system;

# define CUBE_SECOND_IN_US 1000000

typedef struct s_cube
{
	t_cube_settings		*cube_settings;
	t_map				*map;
	t_entities			*entities;
	t_mlx_handler		*mlx_handler;
	t_runtime_handler	*runtime_handler;
	t_input_handler		*input_handler;
	t_dda_data			*dda_data;
	t_audio_system		*audio_system;
	t_parser_config		*parser_config;
}	t_cube;

t_cube	*cube_cube_init(int argc, char **argv);
void	cube_cube_free(t_cube *cube);

#endif
