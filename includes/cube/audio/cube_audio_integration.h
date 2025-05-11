/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_audio_integration.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:55:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:11:11 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_AUDIO_INTEGRATION_H
# define CUBE_AUDIO_INTEGRATION_H

# include <utils.h>

typedef struct s_cube	t_cube;

void	audio_update_player_movement(t_cube *cube);
void	audio_handle_collectible(t_cube *cube);
void	audio_handle_elevator(t_cube *cube, t_bool is_opening);
void	audio_integration_update(t_cube *cube);
void	audio_integration_handle_exit(t_cube *cube);

#endif