/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_lifecycle.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:21:21 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:21:30 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_LIFECYCLE_H
# define CUBE_LIFECYCLE_H

typedef struct s_cube	t_cube;

int		lifecycle_on_destroy(t_cube *cube);
double	lifecycle_get_ticks(void);
int		lifecycle_game_loop(t_cube *cube);
void	lifecycle_animate_sprites(t_cube *cube);

#endif